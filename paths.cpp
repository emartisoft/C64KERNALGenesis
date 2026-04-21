#include "paths.h"

QString appLocalDir()
{
    return QCoreApplication::applicationDirPath();
}

QString appConfigDir()
{
    return QDir::cleanPath(QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + QDir::separator() + qApp->applicationName());
}

QString tempDir()
{
    return QStandardPaths::writableLocation(QStandardPaths::TempLocation) + QDir::separator();
}

bool copyRecursively(const QString &srcPath, const QString &dstPath)
{
    QDir srcDir(srcPath);

    if (!srcDir.exists())
        return false;

    QDir dstDir(dstPath);
    if (!dstDir.exists())
        dstDir.mkpath(".");

    for (QString fileName : srcDir.entryList(QDir::Files))
    {
        QString srcFile = srcPath + "/" + fileName;
        QString dstFile = dstPath + "/" + fileName;

        QFile::copy(srcFile, dstFile);
    }

    for (QString dirName : srcDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        QString srcSubDir = srcPath + "/" + dirName;
        QString dstSubDir = dstPath + "/" + dirName;

        copyRecursively(srcSubDir, dstSubDir);
    }

    return true;
}

QString modulesPath()
{
    const QString appName = QCoreApplication::applicationName();

#ifdef Q_OS_MACOS
    QString path = QStandardPaths::writableLocation(
        QStandardPaths::AppDataLocation
        );
    return QDir(path).filePath("modules");
#else
    return QDir(QCoreApplication::applicationDirPath()).filePath("modules");
#endif
}