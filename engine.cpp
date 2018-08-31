#include "engine.h"
#include "database.h"

Database database;

enum class returnValues {
    Clear,
    Threat,
    Error = -1
};

bool Engine::init()
{
    return database.connectToDatabase();
}


qint16 Engine::fileScan(QString path)
{
    if(!QFileInfo::exists(path))
    {
        return static_cast<qint16>(returnValues::Error);
    }

    if(database.findInDatabase(hashes(path)["md5"], hashes(path)["sha1"], hashes(path)["sha256"]))
    {
        return static_cast<qint16>(returnValues::Threat);
    }
    else
    {
        return static_cast<qint16>(returnValues::Clear);
    }

}




bool Engine::lookup(QString hash)
{
    return database.findInDatabase(hash);
}


QString Engine::fileHashGenerate(QString path, QCryptographicHash::Algorithm hashAlgoritm)
{
    QFile file(path);
    if(file.open(QFile::ReadOnly))
    {
        QCryptographicHash hash(hashAlgoritm);
        if(hash.addData(&file))
        {
            return hash.result().toHex();
        }
    }

    return QString();
}
QMap<QString, QString> Engine::hashes(QString path)
{
    QMap<QString, QString> qmap;
    qmap["md5"] = fileHashGenerate(path, QCryptographicHash::Md5);
    qmap["sha1"] = fileHashGenerate(path, QCryptographicHash::Sha1);
    qmap["sha256"] = fileHashGenerate(path, QCryptographicHash::Sha256);

    return qmap;
}
