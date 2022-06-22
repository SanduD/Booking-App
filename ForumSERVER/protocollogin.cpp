#include "protocollogin.h"
#include "iexception.h"

ProtocolLogin::ProtocolLogin(QString UserName,QString Password)
{
    this->Username=UserName;
    this->Password=Password;

}

bool searchUser(QString Username, QString Password)
{
    QSqlQuery query;
    query.prepare("select* from Credentials where Username='"+Username+"'and Password='"+Password+"'");
    query.exec();

    while(query.next())
    {
        return true;
    }
    return false;

}

void ProtocolLogin::createMessage()
{

    if(searchUser(this->Username,this->Password))
    {
        this->Message="1|1";
    }
    else
    {
        this->Message="1|0";
    }

}
void ProtocolLogin::writeOnSocket(QTcpSocket* socket,DataBase db)
{
    db.getDataBase().open();
     createMessage();
    db.getDataBase().close();
    socket->write(Message);
}
