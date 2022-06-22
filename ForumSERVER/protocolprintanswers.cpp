#include "protocolprintanswers.h"

ProtocolPrintAnswers::ProtocolPrintAnswers(QString Question,QString Order)
{
    this->Question=Question;
    this->order=Order;
}

void ProtocolPrintAnswers::createMessage()
{
    Message="4|";
    QSqlQuery query,countQuery;
    //Question.resize(Question.size()-2);

    countQuery.prepare("select count(*) from Answers A inner join Questions Q on A.IdQuestion=Q.IdQuestion where Q.Text='"+Question+"'");
    countQuery.exec();

    if(order=="0")
        query.prepare("select C.Username,A.Text, A.Reputation from Answers A join Questions Q on Q.IdQuestion=A.IdQuestion join Credentials C on C.IdUser=A.IdUser where Q.Text='"+Question+"'");

    if(order=="1")
        query.prepare("select C.Username,A.Text, A.Reputation from Answers A join Questions Q on Q.IdQuestion=A.IdQuestion join Credentials C on C.IdUser=A.IdUser where Q.Text='"+Question+"' order by A.IdAnswer DESC");

    if(order=="2")
        query.prepare("select C.Username,A.Text, A.Reputation from Answers A join Questions Q on Q.IdQuestion=A.IdQuestion join Credentials C on C.IdUser=A.IdUser where Q.Text='"+Question+"' order by Reputation DESC");

    if(order=="3")
        query.prepare("select C.Username,A.Text, A.Reputation from Answers A join Questions Q on Q.IdQuestion=A.IdQuestion join Credentials C on C.IdUser=A.IdUser where Q.Text='"+Question+"' order by Reputation ASC");

    countQuery.next();
    query.exec();
    Message+=countQuery.value(0).toByteArray()+"|";
    while(query.next())
    {
        Message+=query.value(0).toByteArray()+"|"+query.value(1).toByteArray()+"|"+query.value(2).toByteArray()+"|";
    }

 }

void ProtocolPrintAnswers::writeOnSocket(QTcpSocket* socket,DataBase db)
{
    db.getDataBase().open();
    this->createMessage();
    db.getDataBase().close();
    socket->write(Message);
}
