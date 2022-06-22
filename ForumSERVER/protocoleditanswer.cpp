#include "protocoleditanswer.h"

ProtocolEditAnswer::ProtocolEditAnswer(QString OldAnswer,QString NewAnswer)
{
    this->OldAnswer=OldAnswer;
    this->NewAnswer=NewAnswer;
}



void ProtocolEditAnswer::createMessage()
{
    QSqlQuery query;
    //NewAnswer.resize(NewAnswer.size()-2);

    if(searchAnswerOrQuestion("Answers",OldAnswer)==true)
    {
        query.prepare("Update FORUM.dbo.Answers set Text=:NewAnswer where Text='"+OldAnswer+"'");
        query.bindValue(":NewAnswer",NewAnswer);
        query.exec();
        Message="8|1";
    }
    else
        Message="8|0";
}


void ProtocolEditAnswer::writeOnSocket(QTcpSocket* socket,DataBase db)
{
    db.getDataBase().open();
    this->createMessage();
    db.getDataBase().close();
    socket->write(Message);
}
