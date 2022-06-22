#ifndef PROTOCOLDELETEANSWER_H
#define PROTOCOLDELETEANSWER_H

#include "cprotocol.h"

class ProtocolDeleteAnswer : public CProtocol
{
public:
    ProtocolDeleteAnswer(QString Answer);
    virtual void writeOnSocket(QTcpSocket* socket,DataBase db);
    virtual void createMessage();

private:
    QString Answer;

};

#endif // PROTOCOLDELETEANSWER_H
