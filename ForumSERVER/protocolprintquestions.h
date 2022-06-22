#ifndef PROTOCOLPRINTQUESTIONS_H
#define PROTOCOLPRINTQUESTIONS_H

#include "cprotocol.h"

class ProtocolPrintQuestions : public CProtocol
{
public:
    ProtocolPrintQuestions(QString TopicName);
    virtual void writeOnSocket(QTcpSocket* socket,DataBase db);
    virtual void createMessage();

private:
    QString TopicName;
};

#endif // PROTOCOLPRINTQUESTIONS_H
