#include "handler.h"
#include "utils.h"
#include "jsonfu.h"

#include <QtDebug>
#include <QFileInfo>

// global variables are not so welcommed put it in the class as a member variable


enum class returnValues { // enum class are also classes handle that way as normal classes
    Clear,
    Threat,
    Error = -1
};

Handler::Handler()
{
   engine.init();
}

void Handler::scan(QString path)
{
    switch (engine.fileScan(path)) {
        case static_cast<int>(returnValues::Clear):
            jsonfu.clearJSON();
            jsonfu.addToJSON("file_name", path);
            jsonfu.addToJSON("verdict", "No threat detected");
            jsonfu.createNode();
            utils.qStdOut() << jsonfu.createJSON().toJson(QJsonDocument::Indented);
            break;
        case static_cast<int>(returnValues::Threat):
            jsonfu.clearJSON();
            jsonfu.addToJSON("file_name", path);
            jsonfu.addToJSON("verdict", "blocked");
            jsonfu.createNode();
            utils.qStdOut() << jsonfu.createJSON().toJson(QJsonDocument::Indented);
            break;
        case static_cast<int>(returnValues::Error):
            jsonfu.clearJSON();
            jsonfu.addToJSON("file_name", path);
            jsonfu.addToJSON("error", "file not found!");
            jsonfu.createNode();
            utils.qStdOut() << jsonfu.createJSON().toJson(QJsonDocument::Indented);
            break;
        default:
            break;
    }
}

void Handler::lookup(QString hash)
{
    jsonfu.clearJSON();

    if(engine.lookup(hash))
    {
        jsonfu.addToJSON("hash", hash);
        jsonfu.addToJSON("verdict", "blocked");
        jsonfu.createNode();
    }
    else
    {
        jsonfu.addToJSON("hash", hash);
        jsonfu.addToJSON("verdict", "No threat detected");
        jsonfu.createNode();
    }

    utils.qStdOut() << jsonfu.createJSON().toJson(QJsonDocument::Indented);
}

void Handler::generate(QString path)
{
    jsonfu.clearJSON();
    jsonfu.addToJSON("file_name", path);
    jsonfu.addToJSON("md5", engine.fileHashGenerate(path, QCryptographicHash::Md5));
    jsonfu.addToJSON("sha1", engine.fileHashGenerate(path, QCryptographicHash::Sha1));
    jsonfu.addToJSON("sha256", engine.fileHashGenerate(path, QCryptographicHash::Sha256));
    jsonfu.createNode();
    utils.qStdOut() << jsonfu.createJSON().toJson(QJsonDocument::Indented);
}

bool Handler::scanFolder(QString path)
{
    if(!QFileInfo::exists(path)) {
        utils.qStdOut() << "Given folder not found!";
        return false;
    }

    QStringList results = utils.fileInFolder(path);
    jsonfu.clearJSON();

    for(auto &result : results)
    {
        switch (engine.fileScan(result))
        {
            case static_cast<int>(returnValues::Clear):
                jsonfu.addToJSON("file_name", result);
                jsonfu.addToJSON("verdict", "no threat detected");
                jsonfu.createNode();
                break;
            case static_cast<int>(returnValues::Threat):
                jsonfu.addToJSON("file_name", result);
                jsonfu.addToJSON("verdict", "blocked");
                jsonfu.createNode();
                break;
            case static_cast<int>(returnValues::Error):
                jsonfu.addToJSON("file_name", result);
                jsonfu.addToJSON("error", "file not found!");
                jsonfu.createNode();
                break;
            default:
                break;
        }
    }

    utils.qStdOut() << jsonfu.createJSON(jsonfu.getQJsonArray()).toJson(QJsonDocument::Indented);

    return false;
}
