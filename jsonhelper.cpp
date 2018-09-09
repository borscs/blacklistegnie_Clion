#include "jsonhelper.h"
#include <QVariant>

QJsonArray JsonHelper::getQJsonArray() const
{
	return qJsonArray;
}

void JsonHelper::clearJSON()
{
	recordObject = QJsonObject();
}

void JsonHelper::addToJSON(QString tag, QString data)
{
	QVariant qvainat(data);
	recordObject.insert(tag, QJsonValue::fromVariant(qvainat));
}

void JsonHelper::createNode()
{
	QJsonObject item;
	item.insert("file", recordObject);
	qJsonArray.push_back(recordObject);
}

QJsonDocument JsonHelper::createJSON(QJsonArray array)
{
	QJsonObject jsonObject;
	jsonObject.insert("result", array);
	QJsonDocument jsonDocument(jsonObject);
	return jsonDocument;
}

QJsonDocument JsonHelper::createJSON()
{
	QJsonObject jsonObject;
	jsonObject.insert("result", recordObject);
	QJsonDocument jsonDocument(jsonObject);
	return jsonDocument;
}
