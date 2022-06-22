#include "protocolsubmitquestion.h"

ProtocolSubmitQuestion::ProtocolSubmitQuestion(QString Username,QString TopicName, QString Question)
{
    this->Username=Username;
    this->TopicName=TopicName;
    this->Question=Question;
}

void  ProtocolSubmitQuestion::createMessage()
{

    QSqlQuery query;

   // Question.resize(Question.size()-2);

    query.prepare("declare @Id1 as int;declare @Id2 as int;select @Id1=C.IdUser from Credentials C where Username='"+Username+"'; select @Id2=T.IdTopic from Topics T where T.Name='"+TopicName+"';insert into FORUM.dbo.Questions (IdUser,IdTopic,Text) values (@Id1,@Id2,:Question)") ;
    query.bindValue(":Question",Question);

    if(query.exec())
        Message="5|1";
    else
        Message="5|0";
}

void ProtocolSubmitQuestion::writeOnSocket(QTcpSocket* socket,DataBase db)
{
    db.getDataBase().open();
    this->createMessage();
    db.getDataBase().close();
    socket->write(Message);
}
