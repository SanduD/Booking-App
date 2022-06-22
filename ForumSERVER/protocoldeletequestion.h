#ifndef PROTOCOLDELETEQUESTION_H
#define PROTOCOLDELETEQUESTION_H

#include "cprotocol.h"

class ProtocolDeleteQuestion : public CProtocol
{
public:
    ProtocolDeleteQuestion(QString OldQuestion);
    virtual void writeOnSocket(QTcpSocket* socket,DataBase db);
    virtual void createMessage();

private:
    QString Question;

};

#endif // PROTOCOLDELETEQUESTION_H
