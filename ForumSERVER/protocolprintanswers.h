#ifndef PROTOCOLPRINTANSWERS_H
#define PROTOCOLPRINTANSWERS_H

#include "cprotocol.h"

class ProtocolPrintAnswers : public CProtocol
{
public:
    ProtocolPrintAnswers(QString Question,QString Order);
    virtual void writeOnSocket(QTcpSocket* socket,DataBase db);
    virtual void createMessage();
private:
    QString Question;
    QString order;
};

#endif // PROTOCOLPRINTANSWERS_H
