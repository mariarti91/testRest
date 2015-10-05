#ifndef MYHTTPSERVER_H
#define MYHTTPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QNetworkAccessManager>

class MyHttpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyHttpServer(QObject *parent = 0);

signals:

public slots:
    void slotNewConnectionHandler();
//    void slotReadDataHandler();
//    void slotDisconnectedHandler();

private:
    QTcpServer m_pServer;
    QNetworkAccessManager* m_pQnam;
};

#endif // MYHTTPSERVER_H
