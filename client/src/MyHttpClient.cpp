#include "MyHttpClient.h"

#include <QUrl>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QDateTime>
#include <QHttpPart>

MyHttpClient::MyHttpClient(QObject *parent) : QObject(parent)
{
    m_pqnaManager = new QNetworkAccessManager(this);
    connect(m_pqnaManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotReplyFinishedHandler(QNetworkReply*)));
}
//----------------------------------------------------------------------

void MyHttpClient::slotReplyFinishedHandler(QNetworkReply *reply)
{
    if(reply->error() != QNetworkReply::NoError)
    {
        qDebug() << " [!]ERROR: " << reply->errorString();
    }
    else
    {
        qDebug() << " [-]Reply:";
        qDebug() << " [|] " << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << " [|] " << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
        qDebug() << " [|] " << reply->readAll();
        qDebug() << " [-]END";
    }
    reply->deleteLater();
}
//----------------------------------------------------------------------

void MyHttpClient::doDownload(const QString &url, const QString& table)
{
    QUrl serviceUrl(url);
    QUrlQuery query;
    query.addQueryItem("r", "api/sync/get");
    query.addQueryItem("table", table);
    query.addQueryItem("access-token", "api_token");
    QUrl param;

    param.setQuery(query);
    QString request;
    request = param.toEncoded(QUrl::RemoveFragment);
    request = url + request;
//    qDebug() << request;
    m_pqnaManager->get(QNetworkRequest(request));
}
//----------------------------------------------------------------------

void MyHttpClient::doUpload(const QString &url, const QByteArray& data)
{
    QUrlQuery query;
    query.addQueryItem("r", "api/sync/post");
    query.addQueryItem("table", "measurement");
    query.addQueryItem("access-token", "api_token");
    QUrl param;
    param.setQuery(query);
    QString request;
    request = param.toEncoded(QUrl::RemoveFragment);
    request = url + request;

    qDebug() << request;

    QNetworkRequest req;
    req.setUrl(request);
    req.setHeader(QNetworkRequest::ContentLengthHeader, data.count());

    m_pqnaManager->post(req, data);
}
//----------------------------------------------------------------------

void MyHttpClient::doDelete(const QString &table, const QString &uid)
{
    QString url = QString("http://127.0.0.1:8080/%1/%2").arg(table).arg(uid);
    qDebug() << url;
    QNetworkRequest req(url);
    m_pqnaManager->deleteResource(req);
}
//----------------------------------------------------------------------

void MyHttpClient::doUpdate(const QString &table, const QString &uid, const QByteArray &data)
{
    QString url = QString("http://127.0.0.1:8080/%1/%2").arg(table).arg(uid);
    QNetworkRequest req;
    req.setUrl(url);
    req.setHeader(QNetworkRequest::ContentLengthHeader, data.count());

    m_pqnaManager->put(req, data);
}
//----------------------------------------------------------------------
