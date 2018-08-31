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
    bool connectToDatabase();
    bool findInDatabase(const QString &md5, const QString &sha1, const QString &sha256);
    bool findInDatabase(const QString &data);
};

#endif // DATABASE_H
