#ifndef PROTOCOLDISLIKEANSWER_H
#define PROTOCOLDISLIKEANSWER_H

#include "cprotocol.h"

class ProtocolDislikeAnswer : public CProtocol
{
public:
    ProtocolDislikeAnswer(QString Username,QString Text);
    virtual void writeOnSocket(QTcpSocket* socket,DataBase db);
    virtual void createMessage();

private:
    QString Text;
    QString Username;
};

#endif // PROTOCOLDISLIKEANSWER_H
