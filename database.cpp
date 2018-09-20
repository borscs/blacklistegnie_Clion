#include "database.h"

// constructor that call connectToDatabase()
// if it succeeded call an init() function
// init will run a query with some default data

bool Database::connectToDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString path = QDir::currentPath() + "/DatabaseDb.sqlite3";
    db.setDatabaseName(path);

   return db.open();
}

bool Database::findInDatabase(const QString &md5, const QString &sha1, const QString &sha256)
{
    QSqlQuery sqlQuery;
    sqlQuery.prepare("SELECT md5, sha1, sha256 FROM HAshes WHERE md5 = (:md5Var) OR sha1 = (:sha1Var) OR sha256 = (:sha256Var)");
    sqlQuery.bindValue(":md5Var", md5);
    sqlQuery.bindValue(":sha1Var", sha1);
    sqlQuery.bindValue(":sha256Var", sha256);

    if(sqlQuery.exec() && sqlQuery.next()) {
        return true;
    }

    return false;
}

bool Database::findInDatabase(const QString &hash) // call the param to hash
{
    QSqlQuery sqlQuery;

    switch (hash.length())
    {
        case 32:
            sqlQuery.prepare("SELECT md5 FROM hashTable WHERE md5 = (:md5Var)");
            sqlQuery.bindValue(":md5Var", hash);
            break;
        case 40:
            sqlQuery.prepare("SELECT sha1 FROM hashTable WHERE sha1 = (:sha1Var)");
            sqlQuery.bindValue(":sha1Var", hash);
            break;
        case 64:
            sqlQuery.prepare("SELECT sha256 FROM hashTable WHERE sha256 = (:sha256Var)");
            sqlQuery.bindValue(":sha256Var", hash);
            break;
    }

    if(sqlQuery.exec() && sqlQuery.next()) {
        return true;
    }

    return false;
}
