#include "database.h"

// if it succeeded call an init() function
// init will run a query with some default data

Database::Database()
{
	connectToDatabase();

}

bool Database::connectToDatabase()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	QString path = QDir::currentPath() + "/DatabaseDb.sqlite3";
	db.setDatabaseName(path);
	if (!db.open()) {
		qDebug() << "Faild to open database.";
	}
	else {
		return db.open();
	}

	return false;

}

bool Database::findInDatabase(const QString &md5, const QString &sha1, const QString &sha256)
{
	QSqlQuery sqlQuery;
	sqlQuery.prepare(
		"SELECT md5, sha1, sha256 FROM Hashes WHERE md5 = (:md5Var) OR sha1 = (:sha1Var) OR sha256 = (:sha256Var)");
	sqlQuery.bindValue(":md5Var", md5);
	sqlQuery.bindValue(":sha1Var", sha1);
	sqlQuery.bindValue(":sha256Var", sha256);

	if (sqlQuery.exec() && sqlQuery.next()) {
		return true;
	}

	return false;
}

bool Database::findInDatabase(const QString &hash) // call the param to hash
{
	QSqlQuery sqlQuery;

	switch (hash.length()) {
		case 32:
			sqlQuery.prepare("SELECT md5 FROM Hashes WHERE md5 = (:md5Var)");
			sqlQuery.bindValue(":md5Var", hash);
			break;
		case 40:
			sqlQuery.prepare("SELECT sha1 FROM Hashes WHERE sha1 = (:sha1Var)");
			sqlQuery.bindValue(":sha1Var", hash);
			break;
		case 64:
			sqlQuery.prepare("SELECT sha256 FROM Hashes WHERE sha256 = (:sha256Var)");
			sqlQuery.bindValue(":sha256Var", hash);
			break;
	}

	if (sqlQuery.exec() && sqlQuery.next()) {
		return true;
	}

	return false;
}
void
Database::addRecord(const QString &md5Path, const QString &sha1Path, const QString &sha265Path, const QString &name)
{
	QSqlQuery sqlQuery;

	sqlQuery
		.prepare("INSERT INTO Hashes (md5, sh1, sha256, Virus_Name) VALUES (:md5Path, :sh1Path, :sha256Path, :name)");
	sqlQuery.bindValue(":md5", md5Path);
	sqlQuery.bindValue(":sh1", sha1Path);
	sqlQuery.bindValue(":sh256", sha265Path);
	sqlQuery.exec();
//		if(sqlQuery.exec() && sqlQuery.next()){
//			qDebug()<<"good";
//		}else{
//			qDebug()<<"not good";
//		}

}
