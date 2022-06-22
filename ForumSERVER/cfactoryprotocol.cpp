#include "cfactoryprotocol.h"
#include "protocollogin.h"
#include "protocolregister.h"
#include "protocolprintquestions.h"
#include "protocolprintanswers.h"
#include "protocolsubmitquestion.h"
#include "protocolsubmitanswer.h"
#include "protocoleditquestion.h"
#include "protocoleditanswer.h"
#include "protocoldeletequestion.h"
#include "protocoldeleteanswer.h"
#include "protocollikeanswer.h"
#include "protocoldislikeanswer.h"

CFactoryProtocol::CFactoryProtocol()
{

}

 IProtocol* CFactoryProtocol::createProtocol(QString Data,Protocol Name)
{
     QStringList dataList= QString(Data).split('|');
    if(Name==Login)
        return new ProtocolLogin(dataList.value(1),dataList.value(2));

    if(Name==Register)
        return new ProtocolRegister(dataList.value(1),dataList.value(2),dataList.value(3));

    if(Name==PrintQuestions)
        return new ProtocolPrintQuestions(dataList.value(1));

    if(Name==PrintAnswers)
        return new ProtocolPrintAnswers(dataList.value(1),dataList.value(2));

    if(Name==SubmitQuestion)
        return new ProtocolSubmitQuestion(dataList.value(1),dataList.value(2),dataList.value(3));

    if(Name==SubmitAnswer)
        return new ProtocolSubmitAnswer(dataList.value(1),dataList.value(2),dataList.value(3));

    if(Name==EditQuestion)
        return new ProtocolEditQuestion(dataList.value(1),dataList.value(2));

    if(Name==EditAnswer)
        return new ProtocolEditAnswer(dataList.value(1),dataList.value(2));

    if(Name==DeleteQuestion)
        return new ProtocolDeleteQuestion(dataList.value(1));

    if(Name==DeleteAnswer)
        return new ProtocolDeleteAnswer(dataList.value(1));

    if(Name==LikeAnswer)
        return new ProtocolLikeAnswer(dataList.value(1),dataList.value(2));

    if(Name==DislikeAnswer)
        return new ProtocolDislikeAnswer(dataList.value(1),dataList.value(2));





    return NULL;
        //socket->write(Protocol::LogIn(dataList.value(1),dataList.value(2)));

}
