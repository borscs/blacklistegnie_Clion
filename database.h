#pragma once

#include <QtSql/QtSql>
#include <QString>
#include <QDir>
#include <QVariant>

class Database
{
public:
	bool connectToDatabase();
	bool findInDatabase(const QString &md5, const QString &sha1, const QString &sha256);
	bool findInDatabase(const QString &hash);
};
