#include "MyHttpClient.h"

#include <QUrl>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QDateTime>

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
    QUrl serviceUrl(url);

    QByteArray postData;

    QUrl param;
    QUrlQuery query;
    //query.addQueryItem("data", QString(data.toBase64()));
    query.addQueryItem("r", "api/sinc/post");
    query.addQueryItem("table", "gateway");
    param.setQuery(query);

    postData = param.toEncoded(QUrl::RemoveFragment);

    qDebug()  << postData;
    //m_pqnaManager->post(QNetworkRequest(serviceUrl), postData);
}
//----------------------------------------------------------------------
