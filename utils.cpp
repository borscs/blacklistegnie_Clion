#include "utils.h"

#include <QDirIterator>


QTextStream &Utils::qStdOut()
{
    static QTextStream textStream(stdout);
    return textStream;
}

QStringList Utils::fileInFolder(const QString &path)
{
    QStringList results;
    QDirIterator it(path);
    while(it.hasNext()) {
        it.next();
        if(QFileInfo(it.filePath()).isFile()) {
            results << it.filePath();
        }
    }

    return results;
}
