#include "protocolregister.h"

ProtocolRegister::ProtocolRegister(QString UserName,QString Password,QString Email)
{
    this->Username=UserName;
    this->Password=Password;
    this->Email=Email;
}


bool searchUsername(QString Username)
{
    QSqlQuery query;
    query.prepare("select* from Credentials where Username='"+Username+"'");
    query.exec();
    while(query.next())
    {
        return true;
    }
    return false;

}
void ProtocolRegister::createMessage()
{

   // Email.resize(Email.size()-2);

    if(searchUsername(Username))
    {
        this->Message="2|0";
    }
    else
    {
        QSqlQuery query;
        query.prepare("INSERT INTO [FORUM].[dbo].[Credentials](Username,Password,Email)  values (:Username,:Password,:Email)") ;
        query.bindValue(":Username",Username);
        query.bindValue(":Password",Password);
        query.bindValue(":Email",Email);

        if(query.exec())
            this->Message="2|1";
        else
            this->Message="2|0";
    }
}

void ProtocolRegister::writeOnSocket(QTcpSocket* socket,DataBase db)
{
    db.getDataBase().open();
    createMessage();
    db.getDataBase().close();
    socket->write(Message);
}
