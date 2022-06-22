#include "protocolprintquestions.h"

ProtocolPrintQuestions::ProtocolPrintQuestions(QString TopicName)
{
    this->TopicName=TopicName;
}

void ProtocolPrintQuestions::createMessage()
{
    this->Message="3|";
    QSqlQuery query,countQuery;

    //this->TopicName.resize(this->TopicName.size()-2);

    countQuery.prepare("select count(*) from Questions Q inner join Topics T on T.IdTopic=Q.IdTopic where T.Name='"+TopicName+"'");
    countQuery.exec();


    query.prepare("select C.Username,Q.Text from Questions Q inner join Topics T on T.IdTopic=Q.IdTopic inner join Credentials C on C.IdUser=Q.IdUser where T.Name='"+TopicName+"'");
    query.exec();
    countQuery.next();

    this->Message+=countQuery.value(0).toByteArray()+"|";
    while(query.next())
    {
        this->Message+=query.value(0).toByteArray()+"|"+query.value(1).toByteArray()+"|";

    }
}

void ProtocolPrintQuestions::writeOnSocket(QTcpSocket* socket,DataBase db)
{
    db.getDataBase().open();
    this->createMessage();
    db.getDataBase().close();
    socket->write(Message);
}
