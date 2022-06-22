#ifndef PROTOCOLEDITANSWER_H
#define PROTOCOLEDITANSWER_H

#include "cprotocol.h"

class ProtocolEditAnswer : public CProtocol
{
public:
    ProtocolEditAnswer(QString OldAnswer,QString NewAnswer);
    virtual void writeOnSocket(QTcpSocket* socket,DataBase db);
    virtual void createMessage();

private:
    QString OldAnswer;
    QString NewAnswer;
};

#endif // PROTOCOLEDITANSWER_H
