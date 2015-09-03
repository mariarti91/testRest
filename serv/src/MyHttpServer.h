#ifndef MYHTTPSERVER_H
#define MYHTTPSERVER_H

#include <QObject>
#include <QTcpServer>

class MyHttpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyHttpServer(QObject *parent = 0);

signals:

public slots:
    void slotNewConnectionHandler();
    void slotReadDataHandler();
    void slotDisconnectedHandler();

private:
    QTcpServer m_pServer;
};

#endif // MYHTTPSERVER_H
