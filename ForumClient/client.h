#ifndef CLIENT_H
#define CLIENT_H
#include "iclient.h"


class Client : public IClient
{
    Q_OBJECT
private:
    QTcpSocket *socket;
    QStringList lastResponseMsg;
    QString username;
    QString topic_accesat;

public:
    explicit Client(QString ip, int port);
    QTcpSocket* getSocket();
    QStringList getLastMsg();
    void setUsername(QString user);
    QString getUsername();
    void setTopic(QString topic);
    QString getTopic();

signals:

public slots:
    void onReadyRead();

};

#endif // CLIENT_H
