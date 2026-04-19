#include "singleapplication.h"
#include <QStandardPaths>

SingleApplication::SingleApplication(int &argc, char **argv, const QString &appKey)
    : QApplication(argc, argv)
    , m_lockFile(nullptr)
    , m_isRunning(false)
{
    // Lock dosyasını geçici dizine yaz
    QString lockPath = QDir::temp().absoluteFilePath(appKey + ".lock");
    m_lockFile = new QLockFile(lockPath);

    // 100ms içinde kilitlemeyi dene
    if (!m_lockFile->tryLock(100)) {
        m_isRunning = true; // Başka bir instance zaten çalışıyor
    }
}

SingleApplication::~SingleApplication()
{
    if (m_lockFile) {
        if (!m_isRunning) {
            m_lockFile->unlock();
        }
        delete m_lockFile;
    }
}

bool SingleApplication::isRunning() const
{
    return m_isRunning;
}
