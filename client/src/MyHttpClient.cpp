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

void MyHttpClient::doDownload(const QString &url)
{
    m_pqnaManager->get(QNetworkRequest(QUrl(url)));
}
//----------------------------------------------------------------------

void MyHttpClient::doUpload(const QString &url, const QByteArray& data)
{
    QUrl serviceUrl(url);

    QByteArray postData;

    QUrl param;
    QUrlQuery query;
    query.addQueryItem("data", QString(data.toBase64()));
    param.setQuery(query);

    postData = param.toEncoded(QUrl::RemoveFragment);

    m_pqnaManager->post(QNetworkRequest(serviceUrl), postData);
}
//----------------------------------------------------------------------
