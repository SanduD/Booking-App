#include "thread.h"
//#include "DataBase.h"

#include <QString>
#include "cfactoryprotocol.h"
#include "ProtocolList.h"

void Thread::run(){
    //thread starts here
    qDebug() << "Starting thread";
    socket = new QTcpSocket();
    if(!socket->setSocketDescriptor(this->socketDescriptor)){
        qDebug() << "There was a problem connecting";
        return;
    }

    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);

    qDebug() << socketDescriptor << " Client connected";

    DataBase::getInstance().ConnectDB();
   // db.ConnectDB();
    exec();
}


void Thread::readyRead()
{

    QByteArray Data = socket->readAll();

    QStringList dataList=QString(Data).split('|');

    if (dataList.value(0)=="1")
        CFactoryProtocol::createProtocol(Data,Login)->writeOnSocket(socket,DataBase::getInstance());

    if (dataList.value(0)=="2")
        CFactoryProtocol::createProtocol(Data,Register)->writeOnSocket(socket,DataBase::getInstance());

    if(dataList.value(0)=="3")
        CFactoryProtocol::createProtocol(Data,PrintQuestions)->writeOnSocket(socket,DataBase::getInstance());

    if(dataList.value(0)=="4")
        CFactoryProtocol::createProtocol(Data,PrintAnswers)->writeOnSocket(socket,DataBase::getInstance());


    if(dataList.value(0)=="5")
        CFactoryProtocol::createProtocol(Data,SubmitQuestion)->writeOnSocket(socket,DataBase::getInstance());


    if(dataList.value(0)=="6")
        CFactoryProtocol::createProtocol(Data,SubmitAnswer)->writeOnSocket(socket,DataBase::getInstance());

    if(dataList.value(0)=="7")
        CFactoryProtocol::createProtocol(Data,EditQuestion)->writeOnSocket(socket,DataBase::getInstance());

    if(dataList.value(0)=="8")
        CFactoryProtocol::createProtocol(Data,EditAnswer)->writeOnSocket(socket,DataBase::getInstance());

    if(dataList.value(0)=="9")
        CFactoryProtocol::createProtocol(Data,DeleteQuestion)->writeOnSocket(socket,DataBase::getInstance());

    if(dataList.value(0)=="10")
        CFactoryProtocol::createProtocol(Data,DeleteAnswer)->writeOnSocket(socket,DataBase::getInstance());

    if(dataList.value(0)=="11")
        CFactoryProtocol::createProtocol(Data,LikeAnswer)->writeOnSocket(socket,DataBase::getInstance());

    if(dataList.value(0)=="12")
        CFactoryProtocol::createProtocol(Data,DislikeAnswer)->writeOnSocket(socket,DataBase::getInstance());

}

void Thread::disconnected(){

    qDebug() << socketDescriptor << " Disconnected";
    socket->deleteLater();
   // Protocol::stopDatabase();
    exit(0);
}
