#pragma once

#include <QtCore/QCoreApplication>
#include <QCryptographicHash>


class Engine
{
public:
    bool init();
    bool lookup(QString hash);
    qint16 fileScan(QString path);
    QMap<QString, QString> hashes(QString path);
    QString fileHashGenerate(QString path, QCryptographicHash::Algorithm algorithm);

};
