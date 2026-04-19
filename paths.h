#ifndef PATHS_H
#define PATHS_H

#include <QString>
#include <QCoreApplication>
#include <QDir>
#include <QStandardPaths>

QString appLocalDir();
QString appConfigDir();
QString tempDir();

#endif // PATHS_H
