#include "MyHttpServer.h"

#include <QDebug>
#include <QTcpSocket>
#include <QDateTime>

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
    QTcpSocket* sock = m_pServer.nextPendingConnection();;
    connect(sock, SIGNAL(readyRead()), this, SLOT(slotReadDataHandler()));
    connect(sock, SIGNAL(disconnected()), this, SLOT(slotDisconnectedHandler()));
}
//-------------------------------------------------------------------------------------

void MyHttpServer::slotReadDataHandler()
{
    QTcpSocket* sock = qobject_cast<QTcpSocket*>(sender());
    qDebug() << sock->readAll();

    QString responce = "HTTP/1.1 200 OK\r\n\r\n%1";
    sock->write(responce.arg(QTime::currentTime().toString()).toLatin1());
    sock->disconnectFromHost();
}
//-------------------------------------------------------------------------------------

void MyHttpServer::slotDisconnectedHandler()
{
    QTcpSocket* sock = qobject_cast<QTcpSocket*>(sender());
    sock->close();
    sock->deleteLater();
}
//-------------------------------------------------------------------------------------
