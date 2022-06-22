#ifndef IEXCEPTION_H
#define IEXCEPTION_H

#include <QDebug>
class IException
{
public:
    IException();
    virtual void printErrorID()=0;
    virtual void printMessage()=0;
};

#endif // IEXCEPTION_H
