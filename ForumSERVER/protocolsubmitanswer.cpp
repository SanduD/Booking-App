#include "protocolsubmitanswer.h"


ProtocolSubmitAnswer::ProtocolSubmitAnswer(QString Username,QString Question, QString Answer)
{
    this->Username=Username;
    this->Answer=Answer;
    this->Question=Question;
}

void  ProtocolSubmitAnswer::createMessage()
{
    QSqlQuery query;
    //Answer.resize(Answer.size()-2);

    query.prepare("declare @Id1 as int;declare @Id2 as int;select @Id1=C.IdUser from Credentials C where Username='"+Username+"'; select @Id2=Q.IdQuestion from Questions Q where Q.Text='"+Question+"';insert into FORUM.dbo.Answers (IdUser,IdQuestion,Text,Reputation) values (@Id1,@Id2,:Answer,0)") ;
    query.bindValue(":Answer",Answer);

    if(query.exec())
        Message="6|1";
    else
        Message="6|0";
}

void ProtocolSubmitAnswer::writeOnSocket(QTcpSocket* socket,DataBase db)
{
    db.getDataBase().open();
    this->createMessage();
    db.getDataBase().close();
    socket->write(Message);
}
