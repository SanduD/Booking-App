#ifndef PROTOCOLEDITQUESTION_H
#define PROTOCOLEDITQUESTION_H

#include "cprotocol.h"

class ProtocolEditQuestion : public CProtocol
{
public:
    ProtocolEditQuestion(QString OldQuestion,QString NewQuestion);
    virtual void writeOnSocket(QTcpSocket* socket,DataBase db);
    virtual void createMessage();

private:
    QString OldQuestion;
    QString NewQuestion;
};

#endif // PROTOCOLEDITQUESTION_H
