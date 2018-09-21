#ifndef DATABASE_H
#define DATABASE_H

#include <QtCore/QCoreApplication>
#include <QtSql/QtSql>
#include <QString>
#include <QDir>
#include <QVariant>

class Database
{
public:

	Database();
	bool init();
	void addRecord(const QString &md5Path, const QString &sha1Path, const QString &sha265Path, const QString &name);
	bool connectToDatabase();
	bool findInDatabase(const QString &md5, const QString &sha1, const QString &sha256);
	bool findInDatabase(const QString &hash);
};

#endif // DATABASE_H
