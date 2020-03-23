#ifndef HTTPPOSTUTIL_H
#define HTTPPOSTUTIL_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QDebug>


class HttpPostUtil : public QObject
{
    Q_OBJECT
public:
    explicit HttpPostUtil(QObject *);
    explicit HttpPostUtil();
    ~HttpPostUtil();

signals:


public:
    void post(QString url,QString jsonData) ;
public slots:
    void requestFinished(QNetworkReply* reply);
};

#endif // HTTPPOSTUTIL_H
