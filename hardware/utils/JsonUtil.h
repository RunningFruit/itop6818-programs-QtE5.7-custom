#ifndef JSON_UTIL_H
#define JSON_UTIL_H

#include <QByteArray>
#include <QJsonObject>
#include <QString>
#include <QStringList>
#include <QJsonDocument>


class JsonUtil
{
public:
    explicit JsonUtil();
    ~JsonUtil();

public:

    QByteArray getJsonByteArray(QJsonObject obj);

    QString getJsonString(QJsonObject obj);

    QString getValueFromJson(QByteArray& byteArray, QStringList& ls);
};

#endif // JSON_UTIL_H
