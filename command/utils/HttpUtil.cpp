
#include "HttpUtil.h"

#include "common/common.h"


#define URL_UPLOAD QString("/upload/pic")

#define FILE_PATH QString("/upload/pic")


HttpUtil::HttpUtil(QObject *parent) : QObject(parent)
{

}
HttpUtil::~HttpUtil(){

}

void HttpUtil::upload(){

    QString path = FILE_PATH;

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/png"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QString("form-data; name=\"%1\"; filename=\"%2\"").arg("offline.png").arg(path));
    QFile *file = new QFile(path);
    file->open(QIODevice::ReadOnly);
    imagePart.setBodyDevice(file);
    imagePart.setBodyDevice(file);
    file->setParent(multiPart);
    multiPart->append(imagePart);

    QNetworkRequest request(QUrl(URL_HTTP+URL_UPLOAD));

    reply = m_networkAccessManager->post(request, multiPart);
    multiPart->setParent(reply);

    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(uploadError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(uploadProcess(qint64, qint64)));
    connect(reply, SIGNAL(finished()), this, SLOT(uploadFinished()));

}

void HttpUtil::uploadFinished(){
    QByteArray resultContent = reply->readAll();
    QTextCodec* pCodec = QTextCodec::codecForName("UTF-8");
    QString strResult = pCodec->toUnicode(resultContent);
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();//http返回码


    printf(strResult.toStdString().data());
    printf(QString("%1").arg(statusCode).toStdString().data());
}

void HttpUtil::uploadError(QNetworkReply::NetworkError code){
    qDebug() << code;
}

void HttpUtil::uploadProcess(qint64 bytesReceived, qint64 bytesTotal){
    qDebug() << bytesReceived << bytesTotal;
}


