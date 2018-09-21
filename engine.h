#pragma once

#include <QtCore/QCoreApplication>
#include <QCryptographicHash>

#include "database.h"
#include "utils.h"

class Engine
{
public:
	bool init();
	bool isFileBlacklisted(const QString &filePath);
	bool lookup(QString hash);
	qint16 fileScan(QString path);
	QMap<QString, QString> hashes(QString path);
	QString fileHashGenerate(QString path, QCryptographicHash::Algorithm algorithm);



private:
	Database database;
	Utils utils;
};