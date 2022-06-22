#include "protocoldeleteanswer.h"


ProtocolDeleteAnswer::ProtocolDeleteAnswer(QString Answer)
{
    this->Answer=Answer;
}

void ProtocolDeleteAnswer::createMessage()
{

    QSqlQuery query;

    //Answer.resize(Answer.size()-2);

    if(searchAnswerOrQuestion("Answers",Answer)==true)
    {
        query.prepare("declare @IdA int;select @IdA=IdAnswer from Answers where Text='"+Answer+"'; delete from AnswersReputation where IdAnswer=@IdA;delete from Answers where IdAnswer=@IdA;");
        query.exec();
        Message="10|1";
    }
    else
        Message="10|0";
}


void ProtocolDeleteAnswer::writeOnSocket(QTcpSocket* socket,DataBase db)
{
    db.getDataBase().open();
    this->createMessage();
    db.getDataBase().close();
    socket->write(Message);
}
