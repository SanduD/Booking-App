#ifndef PROTOCOLSUBMITQUESTION_H
#define PROTOCOLSUBMITQUESTION_H

#include "cprotocol.h"

class ProtocolSubmitQuestion : public CProtocol
{
public:
    ProtocolSubmitQuestion(QString Username,QString TopicName, QString Question);
    virtual void writeOnSocket(QTcpSocket* socket,DataBase db);
    virtual void createMessage();

private:
    QString Username;
    QString TopicName;
    QString Question;
};

#endif // PROTOCOLSUBMITQUESTION_H
