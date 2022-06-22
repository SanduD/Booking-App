#include "protocoleditquestion.h"

ProtocolEditQuestion::ProtocolEditQuestion(QString OldQuestion,QString NewQuestion)
{
    this->OldQuestion=OldQuestion;
    this->NewQuestion=NewQuestion;
}


void ProtocolEditQuestion::createMessage()
{
    QSqlQuery query;


    //NewQuestion.resize(NewQuestion.size()-2);

    if(searchAnswerOrQuestion("Questions",OldQuestion)==true)
    {
        query.prepare("Update FORUM.dbo.Questions set Text=:NewQuestion where Text='"+OldQuestion+"'");
        query.bindValue(":NewQuestion",NewQuestion);
        query.exec();
        Message="7|1";
    }
    else
        Message="7|0";
}


void ProtocolEditQuestion::writeOnSocket(QTcpSocket* socket,DataBase db)
{
    db.getDataBase().open();
    this->createMessage();
    db.getDataBase().close();
    socket->write(Message);
}
