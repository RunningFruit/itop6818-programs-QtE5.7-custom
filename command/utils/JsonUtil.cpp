#include "JsonUtil.h"


JsonUtil::JsonUtil(){

}

JsonUtil::~JsonUtil(){

}

QJsonObject JsonUtil::stringToJson(QString jsonString)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toLocal8Bit().data());
    if(jsonDocument.isNull())
    {
        qDebug()<< "String NULL"<< jsonString.toLocal8Bit().data();
    }
    QJsonObject jsonObject = jsonDocument.object();
    return jsonObject;
}

QString JsonUtil::jsonToString(QJsonObject jsonObject)
{
    return QString(QJsonDocument(jsonObject).toJson());
}

QByteArray JsonUtil::getJsonByteArray(QJsonObject obj)
{
    if (obj.isEmpty()) {
        return "";
    }
    QJsonDocument document;
    document.setObject(obj);
    return document.toJson(QJsonDocument::Compact);
}

QString JsonUtil::getJsonString(QJsonObject obj)
{
    if (obj.isEmpty()) {
        return "";
    }
    QJsonDocument document;
    document.setObject(obj);
    QString str(document.toJson(QJsonDocument::Compact));
    return str;
}

//byteArray 源数据 ls 需要解析的字段在json中的路径
//例如
/*
student:{
 name:"lisi".
 id:"001",
};
*/

//需要获取id时，则应为 ls << "student" << "id";
//若需要获取的为list可将返回值改为QVariantList,
//在转换为QMap即可

QString JsonUtil::getValueFromJson(QByteArray& byteArray, QStringList& ls)
{
    Q_ASSERT(ls.count() == 0);
    QString value;
    QJsonParseError jsonError;

    //获取json文档对象
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);

    //校验是否转换正确
    if (!doucment.isNull() && jsonError.error == QJsonParseError::NoError) {

        //获取json对象
        QJsonObject jsonObj = doucment.object();
        //临时对象，用于存储每次遍历后的结果
        QJsonObject obj;

        //判断第一个是不是最后一个节点
        if (jsonObj.contains(ls[0])) {
            if (jsonObj[ls[0]].isObject()) {
                obj = jsonObj;
            }
            else {
                //如果只有一个节点直接返回
                return jsonObj.value(ls[0]).toString();
            }
        }

        //遍历获取节点
        foreach(auto index,ls)
        {
            if (obj[index].isObject()) {
                obj = obj[index].toObject();
            }
            //获取值
            value = obj.value(index).toString();
        }
    }
    return value;
}
