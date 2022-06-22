#ifndef PROTOCOLLIKEANSWER_H
#define PROTOCOLLIKEANSWER_H

#include "cprotocol.h"

class ProtocolLikeAnswer : public CProtocol
{
public:

    ProtocolLikeAnswer(QString Username,QString Text);
    virtual void writeOnSocket(QTcpSocket* socket,DataBase db);
    virtual void createMessage();

private:
    QString Text;
    QString Username;
};


#endif // PROTOCOLLIKEANSWER_H
