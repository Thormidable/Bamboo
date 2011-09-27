#include "../../WTDivWin.h"

cEventHandler *cEventHandler::mpInstance=0;

cEventHandler *cEventHandler::Instance()
{
 if(!mpInstance) mpInstance=new cEventHandler();
 return mpInstance;
}


