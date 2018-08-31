#pragma once

#include <QCoreApplication>
#include <QTextStream>


namespace  utils
{
    enum class Verdict {
        Clear,
        Threat,
        Error = -1
    };
}

class Utils
{
public:

    QTextStream &qStdOut();
    QStringList fileInFolder(const QString &path);
};
