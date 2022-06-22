#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
class DataBase
{
private:
    QSqlDatabase db;
    static DataBase *instance;
    DataBase();


public:
    static DataBase &getInstance();
    static void destroyDatabase();

    void ConnectDB();
    QSqlDatabase getDataBase(){return db;}
   // ~DataBase();
};

#endif // DATABASE_H
