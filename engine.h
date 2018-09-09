#pragma once

#include <QCryptographicHash>

#include "database.h"

class Engine
{
public:
	bool init();
	bool lookup(QString hash);
	qint16 fileScan(QString path);
	QMap<QString, QString> hashes(QString path);
	QString fileHashGenerate(QString path, QCryptographicHash::Algorithm algorithm);

private:
	Database database;
};
