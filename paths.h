#ifndef PATHS_H
#define PATHS_H

#include <QString>
#include <QCoreApplication>
#include <QDir>
#include <QStandardPaths>

QString appLocalDir();
QString appConfigDir();
QString tempDir();
bool copyRecursively(const QString &srcPath, const QString &dstPath);
QString modulesPath();

#endif // PATHS_H
