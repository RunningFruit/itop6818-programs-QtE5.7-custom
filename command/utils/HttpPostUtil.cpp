#include "HttpPostUtil.h"

#include "common/common.h"

#define URL_UPLOAD "/upload/pic"

#define FILE_PATH "/upload/pic"


HttpPostUtil::HttpPostUtil(QObject *){

}

HttpPostUtil::HttpPostUtil(){

}

HttpPostUtil::~HttpPostUtil(){

}

void HttpPostUtil::post(QString url,QString jsonData) {
    QNetworkRequest request;
    QNetworkAccessManager* naManager = new QNetworkAccessManager(this);
    QMetaObject::Connection connRet = QObject::connect(naManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
    Q_ASSERT(connRet);

    request.setUrl(QUrl(url));

    QNetworkReply* reply = naManager->put(request, jsonData.toUtf8());
}

void HttpPostUtil::requestFinished(QNetworkReply* reply) {
    // 获取http状态码
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCode.isValid())
        qDebug() << "http状态码:" << statusCode.toInt();

    QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    if(reason.isValid())
        qDebug() << "reason=" << reason.toString();

    QNetworkReply::NetworkError err = reply->error();
    if(err != QNetworkReply::NoError) {
        qDebug() << "Failed: " << reply->errorString();
    }
    else {
        // 获取返回内容
        qDebug() << reply->readAll();
    }
}
