#include <QCoreApplication>
#include "server.h"
#include "cexception.h"
#include <QDir>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
     Server::getServer().StartServer();

//    try {
//        throw new CException("Test",2);
//    }
//    catch (IException* Exp)
//    {
//       // qDebug()<<Exp;
//    }



    return a.exec();
}
