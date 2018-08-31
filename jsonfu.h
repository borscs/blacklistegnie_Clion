#pragma once

#include <QJsonArray>
#include <QJsonDocument>
#include <QCoreApplication>
#include <QJsonObject>

class JsonFu // not so useful name JsonConverter
{
public:
    QJsonObject recordObject;
    QJsonArray qJsonArray;

public:
    void clearJSON();
    void addToJSON(QString tag, QString data); // const
    void createNode();
    QJsonDocument createJSON(QJsonArray array);
    QJsonDocument createJSON();
    QJsonArray getQJsonArray() const;
};
