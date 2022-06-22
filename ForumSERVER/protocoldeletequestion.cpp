#include "protocoldeletequestion.h"

ProtocolDeleteQuestion::ProtocolDeleteQuestion(QString OldQuestion)
{
    this->Question=OldQuestion;
}

bool searchQuestion(QString Question)
{
    QSqlQuery query;
    query.prepare("select * from Questions where Text='"+Question+"'");
    query.exec();

    while(query.next())
    {
        return true;
    }
    return false;

}
void ProtocolDeleteQuestion::createMessage()
{

    QSqlQuery query;

   // Question.resize(Question.size()-2);

    if(searchAnswerOrQuestion("Questions",Question)==true)
    {
        query.prepare("declare @IdQ int;select @IdQ=IdQuestion from Questions where Text='"+Question+"'; declare @IdAns int; select @IdAns=IdAnswer from Answers  where IdQuestion=@IdQ; delete from AnswersReputation where IdAnswer=@IdAns;delete from Answers where IdQuestion=@IdQ;delete from Questions where IdQuestion=@IdQ");
        query.exec();
        Message="9|1";
    }
    else
        Message="9|0";
}

void ProtocolDeleteQuestion::writeOnSocket(QTcpSocket* socket,DataBase db)
{
    db.getDataBase().open();
    this->createMessage();
    db.getDataBase().close();
    socket->write(Message);
}
