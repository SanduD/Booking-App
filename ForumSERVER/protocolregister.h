#ifndef PROTOCOLREGISTER_H
#define PROTOCOLREGISTER_H

#include "cprotocol.h"

class ProtocolRegister : public CProtocol
{
public:
    ProtocolRegister(QString UserName,QString Password,QString Email);
    virtual void writeOnSocket(QTcpSocket* socket,DataBase db);
    virtual void createMessage();

private:
    QString Username;
    QString Password;
    QString Email;
};

#endif // PROTOCOLREGISTER_H
