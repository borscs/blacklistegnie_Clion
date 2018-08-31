#pragma once

#include <QCoreApplication>
#include <QTextStream>

class Utils
{
public:

    QTextStream &qStdOut();
    QStringList fileInFolder(const QString &path);
};
