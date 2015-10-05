#ifndef MYHTTPCLIENT_H
#define MYHTTPCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class MyHttpClient : public QObject
{
    Q_OBJECT
public:
    explicit MyHttpClient(QObject *parent = 0);
    void doDownload(const QString& url);
    void doUpload(const QString& url, const QByteArray &data);

signals:

public slots:
    void slotReplyFinishedHandler(QNetworkReply*);

private:
    QNetworkAccessManager* m_pqnaManager;
};

#endif // MYHTTPCLIENT_H
