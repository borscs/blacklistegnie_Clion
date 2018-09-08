#pragma once

#include <QTextStream>
#include <QDirIterator>

namespace utils
{

enum class Verdict
{
	Clear,
	Threat,
	Error = -1
};

class Utils
{
public:

	QTextStream &qStdOut()
	{

		static QTextStream textStream(stdout);
		return textStream;
	};


	QStringList fileInFolder(const QString &path)
	{
		QStringList results;
		QDirIterator it(path);
		while (it.hasNext()) {
			it.next();
			if (QFileInfo(it.filePath()).isFile()) {
				results << it.filePath();
			}
		}

		return results;
	};
};

} // end of utils
