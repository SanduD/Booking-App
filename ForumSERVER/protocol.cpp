#include "protocol.h"

Protocol::Protocol(QObject *parent)
    : QObject{parent}
{

}


bool searchAnswer(QString Answer)
{
    QSqlQuery query;
    query.prepare("select * from Answers where Text='"+Answer+"'");
    query.exec();

    while(query.next())
    {
        return true;
    }
    return false;

}



/*



QByteArray Protocol::DeleteAnswer(QString Answer)
{

    QByteArray Message;
    QSqlQuery query;

    db.getDataBase().open();
    Answer.resize(Answer.size()-2);

    if(searchAnswer(Answer)==true)
    {
        query.prepare("declare @IdA int;select @IdA=IdAnswer from Answers where Text='"+Answer+"'; delete from Answers where IdAnswer=@IdA;");
        query.exec();
        Message="10|1";
    }
    else
        Message="10|0";

    db.getDataBase().close();
    return Message;
}*/

