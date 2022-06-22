#ifndef ICLIENT_H
#define ICLIENT_H

#include <QObject>
#include <iostream>
#include <string>
#include <QString>
#include <QTcpSocket>

class IClient : public QObject
{
    Q_OBJECT
public:
    explicit IClient(QObject *parent = nullptr);
    virtual QTcpSocket* getSocket() = 0;
    virtual QStringList getLastMsg() = 0;
    virtual void setUsername(QString user) = 0;
    virtual QString getUsername() = 0;

signals:

};

#endif // ICLIENT_H
