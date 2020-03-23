#ifndef HTTPDOWNFILEUTIL_H
#define HTTPDOWNFILEUTIL_H

#include <QObject>
#include <QDateTime>
#include <QDebug>

#include <QEventLoop>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QObject>
#include <QUrl>

class HttpDownFileUtil : public QObject
{
    Q_OBJECT
public:
    explicit HttpDownFileUtil(QObject *parent = 0);

signals:

public:
    void downloadFromUrl(QString url_name);

private:
    bool savePhotoFromUrl(const QString &url, const QString &fileName);

};

#endif // HTTPDOWNFILEUTIL_H
