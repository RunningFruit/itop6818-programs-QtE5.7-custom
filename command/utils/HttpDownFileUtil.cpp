#include "HttpDownFileUtil.h"

HttpDownFileUtil::HttpDownFileUtil(QObject *parent) : QObject(parent)
{

}

void HttpDownFileUtil::downloadFromUrl(QString url_name){
    QDateTime datetime;
    QString timestr=datetime.currentDateTime().toString("yyyyMMddHHmmss");
    QString fileName = "/usr/local/pictures/" + timestr + ".jpg";//指定文件夹路径
    qDebug() << "file:" << fileName << endl;
    savePhotoFromUrl(url_name,fileName);
}


bool HttpDownFileUtil::savePhotoFromUrl(const QString &url, const QString &fileName)
{
    //构造请求
    QNetworkAccessManager manager;
    QNetworkRequest request;
    request.setUrl(url);
    // 发送请求
    QNetworkReply *reply = manager.get(request);
    //开启一个局部的事件循环，等待响应结束，退出
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    //判断是否出错
    if (reply->error() != QNetworkReply::NoError)
    {
        return false;
    }
    //SAVE FILE
    QFile f(fileName);
    if(!f.open(QIODevice::WriteOnly))
        return false;
    f.write(reply->readAll());
    f.close();
    delete reply;
    return true;
}
