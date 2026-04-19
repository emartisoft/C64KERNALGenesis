#ifndef SINGLEAPPLICATION_H
#define SINGLEAPPLICATION_H

#include <QApplication>
#include <QLockFile>
#include <QDir>
#include <QString>

class SingleApplication : public QApplication
{
    Q_OBJECT

public:
    SingleApplication(int &argc, char **argv, const QString &appKey);
    ~SingleApplication();

    bool isRunning() const;

private:
    QLockFile *m_lockFile;
    bool m_isRunning;
};

#endif // SINGLEAPPLICATION_H
