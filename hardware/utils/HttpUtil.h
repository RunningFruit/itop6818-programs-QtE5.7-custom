#ifndef HTTP_UTIL_H
#define HTTP_UTIL_H

#include <QObject>
#include <QHttpMultiPart>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QFileInfo>
#include <QEventLoop>
#include <QTextCodec>

class HttpUtil: public QObject
{
    Q_OBJECT
public:
    explicit HttpUtil(QObject *parent = 0);
    ~HttpUtil();

signals:


private slots:
    void uploadFinished();
    void uploadError(QNetworkReply::NetworkError code);
    void uploadProcess(qint64 bytesReceived, qint64 bytesTotal);

private:
    QNetworkAccessManager * m_networkAccessManager = NULL;

    void upload();

    QNetworkReply *reply;
};

#endif // HTTP_UTIL_H
