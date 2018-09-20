#include "handler.h"
#include "utils.h"
#include "jsonfu.h"

#include <QtDebug>
#include <QFileInfo>


engineHandler::engineHandler()
{
	engine.init();
}

void engineHandler::scan(QString path)
{
	switch (engine.fileScan(path)) {
		case static_cast<int>(utils::Verdict::Clear):
			jsonfu.clearJSON();
			jsonfu.addToJSON("file_name", path);
			jsonfu.addToJSON("verdict", "No threat detected");
			jsonfu.createNode();
			utils.qStdOut() << jsonfu.createJSON().toJson(QJsonDocument::Indented);
			break;
		case static_cast<int>(utils::Verdict::Threat):
			jsonfu.clearJSON();
			jsonfu.addToJSON("file_name", path);
			jsonfu.addToJSON("verdict", "blocked");
			jsonfu.createNode();
			utils.qStdOut() << jsonfu.createJSON().toJson(QJsonDocument::Indented);
			break;
		case static_cast<int>(utils::Verdict::Error):
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

void engineHandler::lookup(QString hash)
{
	jsonfu.clearJSON();

	if (engine.lookup(hash)) {
		jsonfu.addToJSON("hash", hash);
		jsonfu.addToJSON("verdict", "blocked");
		jsonfu.createNode();
	}
	else {
		jsonfu.addToJSON("hash", hash);
		jsonfu.addToJSON("verdict", "No threat detected");
		jsonfu.createNode();
	}

	utils.qStdOut() << jsonfu.createJSON().toJson(QJsonDocument::Indented);
}

void engineHandler::generate(QString path)
{
	jsonfu.clearJSON();
	jsonfu.addToJSON("file_name", path);
	jsonfu.addToJSON("md5", engine.fileHashGenerate(path, QCryptographicHash::Md5));
	jsonfu.addToJSON("sha1", engine.fileHashGenerate(path, QCryptographicHash::Sha1));
	jsonfu.addToJSON("sha256", engine.fileHashGenerate(path, QCryptographicHash::Sha256));
	jsonfu.createNode();
	utils.qStdOut() << jsonfu.createJSON().toJson(QJsonDocument::Indented);

	database.addRecord(jsonfu.recordObject.value("md5").toString(),
					   jsonfu.recordObject.value("sha1").toString(),
					   jsonfu.recordObject.value("sha256").toString(), 
					   path);
}

bool engineHandler::scanFolder(QString path)
{
	if (!QFileInfo::exists(path)) {
		utils.qStdOut() << "Given folder not found!";
		return false;
	}

	QStringList results = utils.fileInFolder(path);
	jsonfu.clearJSON();

	for (auto &result : results) {
		switch (engine.fileScan(result)) {
			case static_cast<int>(utils::Verdict::Clear):
				jsonfu.addToJSON("file_name", result);
				jsonfu.addToJSON("verdict", "no threat detected");
				jsonfu.createNode();
				break;
			case static_cast<int>(utils::Verdict::Threat):
				jsonfu.addToJSON("file_name", result);
				jsonfu.addToJSON("verdict", "blocked");
				jsonfu.createNode();
				break;
			case static_cast<int>(utils::Verdict::Error):
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
