#ifndef CEXCEPTION_H
#define CEXCEPTION_H

#include "iexception.h"

class CException : public IException
{
public:
    CException(QString Message, int Id);

    virtual void printErrorID();
    virtual void printMessage();


protected:
    QString Message;
    int ErrorID;
    friend QDebug &operator<<(QDebug &d, const CException &Exp);

};


#endif // CEXCEPTION_H
