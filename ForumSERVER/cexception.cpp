#include "cexception.h"

CException::CException(QString Message,int ID)
{
    this->Message=Message;
    this->ErrorID=ID;
}
void CException::printMessage()
{
    qDebug()<<this->Message<<" ";
}
void CException::printErrorID()
{
     qDebug()<<this->ErrorID<<" ";
}
QDebug &operator<<(QDebug &d, const CException &Exp)
{
    d<<"Programul a gasit o noua exceptie:\n"<<"ID:"<<Exp.ErrorID<<"\t Message:"<<Exp.Message;
    return d;
}
