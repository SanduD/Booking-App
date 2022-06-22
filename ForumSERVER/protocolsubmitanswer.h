#ifndef PROTOCOLSUBMITANSWER_H
#define PROTOCOLSUBMITANSWER_H

#include "cprotocol.h"

class ProtocolSubmitAnswer : public CProtocol
{
public:
    ProtocolSubmitAnswer(QString Username,QString Question, QString Answer);
    virtual void writeOnSocket(QTcpSocket* socket,DataBase db);
    virtual void createMessage();

private:
    QString Username;
    QString Question;
    QString Answer;
};

#endif // PROTOCOLSUBMITANSWER_H
