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
    void doDownload(const QString& url, const QString& table);
    void doUpload(const QString& url, const QByteArray &data);
    void doDelete(const QString& table, const QString& uid);
    void doUpdate(const QString& table, const QString& uid, const QByteArray& data);

signals:

public slots:
    void slotReplyFinishedHandler(QNetworkReply*);

private:
    QNetworkAccessManager* m_pqnaManager;
};

#endif // MYHTTPCLIENT_H
