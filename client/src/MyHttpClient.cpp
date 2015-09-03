#include "MyHttpClient.h"

#include <QUrl>
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
