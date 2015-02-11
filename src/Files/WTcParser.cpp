
#include "../WTBamboo.h"

cPushPopStack<cBracketData> cParser::BracketStack;


//int8 cParser::miState=0;
char *cParser::mpStart=0;

cParser::cParser()
{
    mpUInts=0;
    mpInts=0;
    mpStrings=0;
    mpFloats=0;
};

cParser::~cParser()
{
    delete []mpUInts;
    delete []mpInts;
    delete []mpStrings;
    delete []mpFloats;
    mpUInts=0;
    mpInts=0;
    mpStrings=0;
    mpFloats=0;
};

void cParser::GenIntArray()
{
    if(!mpInts)
    {
        mpInts=new int32[IntNumber()];
        int32 liCount;
        for(liCount=0;liCount<IntNumber();++liCount)
        {
            mpInts[liCount]=GetInt(liCount);
        }
    }
}

void cParser::GenUIntArray()
{
    if(!mpUInts)
    {
        mpUInts=new uint32[UIntNumber()];
        int32 liCount;
        for(liCount=0;liCount<UIntNumber();++liCount)
        {
            mpUInts[liCount]=GetUInt(liCount);
        }
    }
}
void cParser::GenFloatArray()
{
    if(!mpFloats)
    {
        mpFloats=new float[FloatNumber()];
        int32 liCount;
        for(liCount=0;liCount<FloatNumber();++liCount)
        {
            mpFloats[liCount]=GetFloat(liCount);
        }
    }
}
void cParser::GenStringArray()
{
    if(!mpStrings)
    {
        mpStrings=new string[StringNumber()];
        int32 liCount;
        for(liCount=0;liCount<StringNumber();++liCount)
        {
            mpStrings[liCount]=GetString(liCount);
        }
    }
}


int32 *cParser::Ints(){ GenIntArray(); return mpInts;}
uint32 *cParser::UInts(){ GenUIntArray(); return mpUInts;}
float *cParser::Floats(){ GenFloatArray();return mpFloats;};
string *cParser::Strings(){ GenStringArray();return mpStrings;};

int32 cParser::GetNextInt(){return Integers.NextItem()->miInt;}
uint32 cParser::GetNextUInt(){return UnsignedInts.NextItem()->miUInt;}

string cParser::GetNextString(){return StringList.NextItem()->msString;}
float cParser::GetNextFloat(){return FloatVars.NextItem()->miFloat;};

int32 cParser::GetInt(uint32 liInt){ return Integers[liInt].miInt;};
uint32 cParser::GetUInt(uint32 liInt){ return UnsignedInts[liInt].miUInt;};
string cParser::GetString(uint32 liInt){return StringList[liInt]->msString;};
float cParser::GetFloat(uint32 liInt){return FloatVars[liInt].miFloat;};


char *cParser::mcString=0;
char *cParser::mcFormat=0;
bool cParser::Error=false;
char *cParser::mcFileStart=0;

bool cParser::ParseString(char *lcString,char *lcFormat)
{
    delete []mpUInts;
    delete []mpInts;
    delete []mpStrings;
    delete []mpFloats;
    mpUInts=0;
    mpInts=0;
    mpStrings=0;
    mpFloats=0;

	return ParseStringAdd(lcString,lcFormat);
};

bool cParser::ParseStringAdd(char *lcString,char *lcFormat)
{

	Integers.Init(5);
 	StringList.Init(5);
 	FloatVars.Init(5);
 	UnsignedInts.Init(5);

    mcFileStart=lcString;
    mcFormat=lcFormat;
    mcString=lcString;
 BracketStack.Clear();


 //BracketStack.Push(cBracketData(0,0));
 while(*mcString && *mcString!=0x0D && *mcString!=0x0A && *mcFormat)
 {
         if(*mcFormat=='*') {HandleEmpty();}
         else
         {
          if(*mcFormat=='%')
          {
             ++mcFormat;
                switch(*mcFormat)
                {
                    case '%' : {HandleMatch();} break;
                    case '*' : {HandleMatch();} break;
                case '[' :
            {
                BracketStack.Push(cBracketData(mcFormat,mcString));
                BracketStack.Last()->Pedantic=true;
                BracketStack.Last()->Integers=IntNumber();
                BracketStack.Last()->UnsignedInts=UIntNumber();
                BracketStack.Last()->Strings=StringNumber();
                BracketStack.Last()->Floats=FloatNumber();
            }break;
                case '{' :
            {
                BracketStack.Push(cBracketData(mcFormat,mcString));
                BracketStack.Last()->Pedantic=false;
                BracketStack.Last()->Integers=IntNumber();
                BracketStack.Last()->UnsignedInts=UIntNumber();
                BracketStack.Last()->Strings=StringNumber();
                BracketStack.Last()->Floats=FloatNumber();
            }break;
                    case '}' :{}
                    case ']' :
                            {
                                BracketStack.Last()->End=mcFormat;
                                mcFormat=BracketStack.Last()->Start;
                                BracketStack.Last()->StringSafe=mcString;
                                BracketStack.Last()->Integers=IntNumber();
                                BracketStack.Last()->UnsignedInts=UIntNumber();
                                BracketStack.Last()->Strings=StringNumber();
                                BracketStack.Last()->Floats=FloatNumber();

                            }break;
                    case 's' : {mpStart=mcString; HandleString();}break;
					case 'S' : {mpStart=mcString; HandleBoundedString();}break;
                    case 'f' : {mpStart=mcString; HandleFloat();}break;
                    case 'i' : {mpStart=mcString; HandleInteger();}break;
                    case 'v' : {mpStart=mcString; HandleVariable();}break;
                    case 'z' : {mpStart=mcString; HandleFree();}break;
                    case 'u' : {mpStart=mcString; HandleUnsignedInt();}break;
                    case 'r' : {mpStart=mcString; HandleRepeat();}break;
                    case 'R' : {mpStart=mcString; HandleNonPedanticRepeat();}break;
					case '!' : {mpStart=mcString; HandleNotCharacter();}break;
                    default : {HandleMatch();} break;
                }
           }
           else HandleMatch();
        }

     if(Error)
     {
         if(BracketStack.Last())
         {
            if(!JumpToEndOfLoop()) return 0;
         }
         else
         {
             return 0;
         }
     }

     if(!*mcString || *mcString==0x0A || *mcString==0x0D)
     {

         if(BracketStack.Last())
         {
             if(mcFormat[1]=='%' && (mcFormat[2]==']' || mcFormat[2]=='}')) {++mcFormat; break;}
            if(!JumpToEndOfLoop()) return 0;
         }
         else
         {
            if(*mcFormat) ++mcFormat;
             break;

         }
     }


     if(*mcFormat) ++mcFormat;
}

 if((!*mcString || *mcString==0x0D || *mcString==0x0A))
 {
     //Allow Empty Free Checks at the end of the string
     if(*mcFormat=='%' && mcFormat[1]=='z' && !mcFormat[2]) return 1;
     //Close off Loops
     do
     {
         if(*mcFormat=='%' && (mcFormat[1]==']' || mcFormat[1]=='}' || mcFormat[1]=='z')) mcFormat+=2;
         else
         {
			 if(*mcFormat=='%' && mcFormat[1]=='!') mcFormat+=3;
			else
			{
            	if(*mcFormat=='*') ++mcFormat;
            	else
                	if(*mcFormat==0) return 1;
                	else return 0;
			}
         }


     }while(1);

     if(!*mcFormat || (*mcFormat=='*' && !mcFormat[1])) return 1;
 }

 //if(miState==PARSE_STATE_EMPTY && (!*mcFormat || !mcFormat[1])) return 1;

 return 0;
}








void cParser::HandleNotCharacter()
{
 Error=false;
 ++mcFormat;
 if(*mcString==*mcFormat) Error=true;

}


void cParser::HandleString()
{
    bool lbStart=true;
    Error=false;
    do
    {
        if(!((*mcString>='A' && *mcString<='Z') || (*mcString>='a' && *mcString<='z')))
        {
            if(lbStart) {Error=true; return;}
            EndState(mcString);
//            ++mcFormat;
            return;
            //break;
        }
        lbStart=false;
        ++mcString;
    }while(*mcString && *mcString!=0x0A && *mcString!=0x0D);

//string New=mpStart;

cParserString *lcTemp=new cParserString;
lcTemp->msString=mpStart;
lcTemp->miStart=mpStart-mcFileStart;

StringList.Add(lcTemp);

}


void cParser::HandleBoundedString()
{
    Error=false;
	if(*mcString!='"') {Error=true; return;}
	++mcString;

	char *mpStart=mcString;

	while(*mcString && *mcString!='"')
	{
		++mcString;
	}
	if(!*mcString) {Error=true; return;}

	*mcString=0;
cParserString *lcTemp=new cParserString;
lcTemp->msString=mpStart;
lcTemp->miStart=mpStart-mcFileStart;

StringList.Add(lcTemp);

	*mcString='"';

}
void cParser::HandleInteger()
{
    bool lbStart=true;
    Error=false;
    do
       {
        if(*mcString=='-')
        {
            if(!lbStart) {Error=true; return;}
        }
        else
        {
            if(!(*mcString>='0' && *mcString<='9'))
            {
                if(lbStart) Error=true;
                else
                {
                    cParserInt lcTemp;
                    lcTemp=strtol(mpStart,0,10);
                    lcTemp.miStart=mpStart-mcFileStart;
                    Integers.Add(&lcTemp);
                }
                return;
            }
        }
        lbStart=false;
        ++mcString;
    }while(*mcString && *mcString!=0x0A && *mcString!=0x0D);
    cParserInt lcTemp;
    lcTemp=strtol(mpStart,0,10);
    lcTemp.miStart=mpStart-mcFileStart;
    Integers.Add(&lcTemp);
}

void cParser::HandleFree()
{
    bool lbStart=true;
    Error=false;
    while(*mcString && *mcString!=0x0A && *mcString!=0x0D && *mcString!=mcFormat[1])
    {

        lbStart=false;
        ++mcString;
    };
       if(!lbStart)
       {
           EndState(mcString);
       }
        return;

}

void cParser::HandleEmpty()
{
    Error=false;
   do
    {
        if(*mcString==mcFormat[1] || !*mcString) {return;}
        ++mcString;
    }while(*mcString && *mcString!=0x0A && *mcString!=0x0D);
}

void cParser::HandleVariable()
{
    bool lbStart=true;
    Error=false;
do
{
   if(lbStart && (*mcString>='0' && *mcString<='9')) {Error=true; return;}
   if(!((*mcString>='0' && *mcString<='9') ||
        (*mcString>='a' && *mcString<='z') ||
        (*mcString>='A' && *mcString<='Z') ||
        (*mcString=='_')))
   {
       if(lbStart) {Error=true; return;}
       EndState(mcString);
       return;
   }
   lbStart=false;
   ++mcString;
}while(*mcString && *mcString!=0x0A && *mcString!=0x0D);
    EndState(mcString);
}

void cParser::HandleFloat()
{
    bool lbOnce=false;
    bool lbStart=true;
    Error=false;
   do
   {
           if(*mcString=='.')
           {
            if(lbStart) {Error=true; return;}
            if(lbOnce) {return;}
            else lbOnce=true;
           }
        else
        {

           if(!(*mcString>='0' && *mcString<='9'))
           {
               if(lbStart)
               {
                   if(*mcString!='-')
                   {
                    Error=true;
                    return;
                   }
               }
               else
               {
                   cParserFloat lcTemp;
                   lcTemp=strtod(mpStart,0);
                   lcTemp.miStart=mpStart-mcFileStart;
                   FloatVars.Add(&lcTemp);return;
               }
           }
        }
           lbStart=false;
           ++mcString;
   }while(*mcString && *mcString!=0x0A && *mcString!=0x0D);
    cParserFloat lcTemp;
    lcTemp=strtod(mpStart,0);
    lcTemp.miStart=mpStart-mcFileStart;
    FloatVars.Add(&lcTemp);return;
}

void cParser::HandleMatch()
{
    Error=false;
 do
 {

    if(*mcFormat!=*mcString) {Error=true; return;}
    ++mcFormat;
    ++mcString;
    if(*mcFormat=='%' || *mcFormat=='*') {--mcFormat; return;}
    }while(*mcFormat && *mcString && *mcString!=0x0A && *mcString!=0x0D);

};


void cParser::HandleNonPedanticRepeat()
{
    Error=false;
    ++mcFormat;
    do
    {
         if(*mcFormat!=*mcString)
         {
            return;
         }
    ++mcString;
    }while(*mcString && *mcString!=0x0A && *mcString!=0x0D);
}

void cParser::HandleRepeat()
{
    bool lbStart=true;
    Error=false;
    ++mcFormat;
    do
    {
     if(*mcFormat!=*mcString)
     {
        if(lbStart) Error=true;
        return;
     }

    lbStart=false;
    ++mcString;
    }while(*mcString && *mcString!=0x0A && *mcString!=0x0D);
}

void cParser::HandleUnsignedInt()
{
    bool lbStart=true;
    Error=false;
do
{
    if(!(*mcString>='0' && *mcString<='9'))
    {
        if(lbStart){ Error=true;}
        else
        {
            cParserUInt lcTemp;
            lcTemp=strtoul(mpStart,0,10);
            lcTemp.miStart=mpStart-mcFileStart;
            UnsignedInts.Add(&lcTemp);
            return;
        }
    }
    lbStart=false;
    ++mcString;
}while(*mcString && *mcString!=0x0A && *mcString!=0x0D);

    cParserUInt lcTemp;
    lcTemp=strtoul(mpStart,0,10);
    lcTemp.miStart=mpStart-mcFileStart;
    UnsignedInts.Add(&lcTemp);
}

 void cParser::EndState(char *lpCurrent)
 {
    char Temp;
    Temp=lpCurrent[0];
     lpCurrent[0]=0;
     cParserString *lcTemp=new cParserString;
     lcTemp->msString=mpStart;
     lcTemp->miStart=mpStart-mcFileStart;
     StringList.Add(lcTemp);
     lpCurrent[0]=Temp;
 }


 int32 cParser::IntNumber(){return Integers.Items();};
 int32 cParser::FloatNumber(){return FloatVars.Items();};
 int32 cParser::StringNumber(){return StringList.Items();};
 int32 cParser::UIntNumber(){return UnsignedInts.Items();};

 bool cParser::JumpToEndOfLoop()
 {

 if(BracketStack.Last()->End)
 {
     mcFormat=BracketStack.Last()->End;
  }
 else
 {
     if(BracketStack.Last()->Pedantic==false)
     {
         while(*mcFormat!='}')
         {
             if(!*mcFormat) return 0;
             ++mcFormat;
         }
         //++mcFormat;
     }
     else return 0;
 }
 mcString=BracketStack.Last()->StringSafe;
 Integers.SetItems(BracketStack.Last()->Integers);
 UnsignedInts.SetItems(BracketStack.Last()->UnsignedInts);
 StringList.SetItems(BracketStack.Last()->Strings);
 FloatVars.SetItems(BracketStack.Last()->Floats);
 BracketStack.Pop();
 Error=false;

 return 1;
 };

 int32 cParser::GetStringStart(uint32 liString)
 {
     return StringList[liString]->miStart;
 };
 int32 cParser::GetIntStart(uint32 liString)
 {
     return Integers[liString].miStart;
 };
 int32 cParser::GetFloatStart(uint32 liString)
 {
     return FloatVars[liString].miStart;
 };
 int32 cParser::GetUIntStart(uint32 liString)
 {
     return UnsignedInts[liString].miStart;
 };
