#include "jsonfu.h"
#include <QVariant>

QJsonArray JsonFu::getQJsonArray() const
{
    return qJsonArray;
}

void JsonFu::clearJSON()
{
    recordObject = QJsonObject();
}

void JsonFu::addToJSON(QString tag, QString data)
{
    QVariant qvainat(data);
    recordObject.insert(tag,QJsonValue::fromVariant(qvainat));
}

void JsonFu::createNode()
{
    QJsonObject item;
    item.insert("file", recordObject);
    qJsonArray.push_back(recordObject);
}

QJsonDocument JsonFu::createJSON(QJsonArray array)
{
    QJsonObject jsonObject;
    jsonObject.insert("result", array);
    QJsonDocument jsonDocument(jsonObject);
    return jsonDocument;
}

QJsonDocument JsonFu::createJSON()
{
    QJsonObject jsonObject;
    jsonObject.insert("result", recordObject);
    QJsonDocument jsonDocument(jsonObject);
    return jsonDocument;
}
