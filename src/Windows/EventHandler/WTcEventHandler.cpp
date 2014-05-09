#include "stdafx.h"
#include "../../WTBamboo.h"

cEventHandler *cEventHandler::mpInstance=0;

cEventHandler *cEventHandler::Instance()
{
 if(!mpInstance) mpInstance=new cEventHandler();
 return mpInstance;
}

cKeyStore *cEventHandler::Keyboard(){return &Key;}

cMouse *cEventHandler::Mouse(){return &MouseDevice;};

