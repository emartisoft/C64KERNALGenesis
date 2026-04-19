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
