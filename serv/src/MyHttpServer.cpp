#include "MyHttpServer.h"

#include <QDebug>
#include <QTcpSocket>
#include <QDateTime>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>

MyHttpServer::MyHttpServer(QObject *parent) :
    QObject(parent), m_pServer(this)
{
    if(m_pServer.listen(QHostAddress::Any, 8080))
    {
        qDebug() << " [*]listening...";
        connect(&m_pServer, SIGNAL(newConnection()), this, SLOT(slotNewConnectionHandler()));
    }
    else
    {
        qDebug() << " [!]Error: " << m_pServer.errorString();
    }
}
//-------------------------------------------------------------------------------------

void MyHttpServer::slotNewConnectionHandler()
{
    qDebug() << " [ ]Have a new connection!";
    QTcpSocket* sock = m_pServer.nextPendingConnection();
    sock->waitForReadyRead();
    QByteArray request(sock->readAll());
    qDebug() << request;
    QStringList buf = QString(request).split(' ');

    if(buf.at(0) == "GET")
    {
        QString responce = "HTTP/1.1 200 OK\r\n\r\n%1";
        sock->write(responce.arg(QTime::currentTime().toString()).toLatin1());
        sock->waitForBytesWritten();
        sock->disconnectFromHost();
        sock->deleteLater();
        return;
    }

    if(buf.at(0) == "POST")
    {
	QString destUrl(buf.at(1));
        sock->waitForReadyRead();
        QByteArray data(sock->readAll());
        qDebug() << "put " << QString(data) << " into " << destUrl;
        QString responce = "HTTP/1.1 200 OK\r\n\r\n";
        sock->write(responce.toLatin1());
        sock->waitForBytesWritten();
        sock->disconnectFromHost();
        sock->deleteLater();

        //QByteArray payload;
        //payload.append(QString(data).split('=').at(1));
        //payload = QByteArray::fromBase64(QByteArray::fromPercentEncoding(payload));
        //qDebug() << payload;

        //QJsonDocument doc = QJsonDocument::fromJson(payload);
        //QJsonObject jObj = doc.object();
        //QString table = destUrl.split('/').at(2);
        //qDebug() << "table: " << table << " object: " << jObj;


        return;
    }

//    connect(sock, SIGNAL(readyRead()), this, SLOT(slotReadDataHandler()));
//    connect(sock, SIGNAL(disconnected()), this, SLOT(slotDisconnectedHandler()));
}
//-------------------------------------------------------------------------------------

//void MyHttpServer::slotReadDataHandler()
//{
//    QTcpSocket* sock = qobject_cast<QTcpSocket*>(sender());
//    disconnect(sock, SIGNAL(readyRead()), this, SLOT(slotReadDataHandler()));
//    QByteArray request(sock->readAll());
//    qDebug() << request;

//    QStringList buf = QString(request).split(' ');

//    if(buf.at(0) == "GET")
//    {
//        QString responce = "HTTP/1.1 200 OK\r\n\r\n%1";
//        sock->write(responce.arg(QTime::currentTime().toString()).toLatin1());
//        sock->disconnectFromHost();
//    }

//    if(buf.at(0) == "POST")
//    {
//        qDebug() << buf.at(1);
//        qDebug() << sock->readAll();
//    }
//    connect(sock, SIGNAL(readyRead()), this, SLOT(slotReadDataHandler()));
//}
////-------------------------------------------------------------------------------------

//void MyHttpServer::slotDisconnectedHandler()
//{
//    QTcpSocket* sock = qobject_cast<QTcpSocket*>(sender());
//    sock->close();
//    sock->deleteLater();
//}
////-------------------------------------------------------------------------------------
