#ifndef __WTCPARSER_H__
#define __WTCPARSER_H__

class cBracketData
{
public:
    char *Start;
    char *StringSafe;
    char *End;
    bool Pedantic;
//    char *StringEnd;

    uint32 Integers;
    uint32 UnsignedInts;
    uint32 Strings;
    uint32 Floats;

    cBracketData(char* lpStart,char *lpSafe){Start=lpStart;StringSafe=lpSafe;End=0;};
    cBracketData(){Start=0;StringSafe=0;End=0;};
    cBracketData &operator=(cBracketData &lpOther){Start=lpOther.Start; StringSafe=lpOther.StringSafe;End=lpOther.End; return *this;}
};

class cParserString
{
public:
    std::string msString;
    uint32 miStart;
    cParserString *operator=(cParserString *lpString){msString=lpString->msString; miStart=lpString->miStart; return this;};
    cParserString operator=(cParserString lpString){msString=lpString.msString; miStart=lpString.miStart; return *this;};
    std::string operator=(char *lpString){msString=lpString; return msString;};
    std::string operator=(std::string lpString){msString=lpString; return msString;};
    void Start(uint32 liStart){miStart=liStart;};
};

class cParserUInt
{
public:
    uint32 miUInt;
    uint32 miStart;
    uint32 operator=(uint32 liUInt){miUInt=liUInt; return miUInt;};
    void UInt(uint32 liUInt){miUInt=liUInt;};
    void Start(uint32 liStart){miStart=liStart;};
};

class cParserFloat
{
public:
    float miFloat;
    uint32 miStart;
    float operator=(float liFloat){miFloat=liFloat; return miFloat;};
    void Float(float liFloat){miFloat=liFloat;};
    void Start(float liStart){miStart=liStart;};
};

class cParserInt
{
public:
    int32 miInt;
    uint32 miStart;
    int32 operator=(int32 liInt){miInt=liInt; return miInt;};
    void Int(int32 liInt){miInt=liInt;};
    void Start(uint32 liStart){miStart=liStart;};
};

/**
 * \brief A class for parsing strings.
 * This class will take a string and a format. It will try to extract data from the string using the specified format.
 * It will return whether the string was of the correct format and give access to any data that was extracted.
 * Will extract data until the string is found to be out of format, then will exit. Each variable will keep extracting data until an invalid character is found.
 * I.E. "%u%u" is an invalid format string as the parser will not be able to determine the end of the first unsigned integer and will extract  all the data into the first variable. "%u %u" is acceptable as the cahracter ' ' is not a valid character for an unsigned integer.
 * To parse a string, use the function ParseString(char*,char*). It will clear all stored data and try to parse the string.
 * It supports: \n
 * Defined Characters.\n
 * Strings.\n
 * Variable Names.\n
 * Repeating Loops.\n
 * Repeating Characters. \n
 * Ignore until a character is reached.\n
 * Floats.\n
 * Integers.\n
 * Strings.\n
 * UnsignedInts.\n
 * \n
 * Parsing Format Strings:\n
 * All Parsing Format commands are identified by following a % character. The only character which does not meet this rule is a * character. If you wish to specify a * or % character precede them with a % character. (i.e. %% or %*). Pedantic Implies that this repeat must be found at least once for the string to be considered in format.\n
 * * : String of any characters. Will search for the next character in the parsing format. This will be interpreted as a specified character. It does not output any data.\n
 * %[ : Starts a pedantic repeat between this and the matching %].\n
 * %] : Closes the pedantic repeat on the top of the stack started by a %[.\n
 * %{ : Starts a non pedantic repeat between this and the matching %}.\n
 * %} : Closes the pedantic repeat on the top of the stack started by a %{.\n
 * %r : Will pedanticly repeat the next character.\n
 * %R : Will non-pedanticly repeat the next character.\n
 * %s : Will expect a string. This can contain any English alphabet character. must have at least a single character to be in format.\n
 * %S : Will expect a string enclosed in the symbols "". The "" symbols will be stripped when it is placed into the string container.\n
 * %f : Will expect a float value. Can begin with a - but not a +. Can contain up to a single decimal point. Must not contain any other non numeric characters. Needs at least a single Numeric character to be in format.\n
 * %i : Will expect an integer value. Can begin with a - but not a +. Must not contain any other non numeric characters. Needs at least a single Numeric character to be in format.\n
 * %v : Will expect a variable name. Stores data as a string. Must begin with an English alphabet character. Can contain any alpha-numeric characters. Needs at least a single character to be in format.\n
 * %u : Will expect an unsigned integer. Can only contain numeric characters. Needs at least a single character to be in format.\n
 * %z : Will ignore the rest of the string. Will not extract data. Will not use any open loops (as cannot guarantee starting at the correct point).\n
 * %! : Indicates that any cahracter can be accepted EXCEPT the character following the ! character.\n
 */

class cParser
{
    uint32 *mpUInts;
    int32 *mpInts;
    std::string *mpStrings;
    float *mpFloats;

    cLimitedListCursor<cParserInt> Integers;
    cLimitedListCursor<cParserUInt> UnsignedInts;
    cLimitedPointerListCursor<cParserString> StringList;
    cLimitedListCursor<cParserFloat> FloatVars;

    static cPushPopStack<cBracketData> BracketStack;

    static char *mpStart;
    static char *mcString;
    static char *mcFormat;
    static bool Error;
    static char *mcFileStart;

    bool JumpToEndOfLoop();

    void HandleString();
	void HandleBoundedString();
	void HandleNotCharacter();
    void HandleInteger();
    void HandleFree();
    void HandleEmpty();
    void HandleVariable();
    void HandleFloat();
    void HandleRepeat();
    void HandleUnsignedInt();
    void HandleMatch();
    void HandleNonPedanticRepeat();

public:
	/**
	 * \brief This is the function which will parse a string. It will try to extract data in the specified format.
	 * \return Will return true if lcString is in the correct format. Will return false if not.
	 * \param lcString The string with the data which should be parsed.
	 * \param lcFormat The format of the string.
	 * This class will clear all the currently stored data. This class will try to extract data from the string in the specified format. It will seperate the data by type into strings, floats, integers and unsigned integers.
	 */
    bool ParseString(char *lcString,char *lcFormat);
	/**
	 * \brief This is the same function as ParseString but will append the new data to the end of the currently stored data.
	 * \return Will return true if lcString is in the correct format. Will return false if not.
	 * \param lcString The string with the data which should be parsed.
	 * \param lcFormat The format of the string.
	 * This class will try to extract data from the string in the specified format. It will seperate the data by type into strings, floats, integers and unsigned integers.
	 */
	bool ParseStringAdd(char *lcString,char *lcFormat);
    cParser();
    ~cParser();

	/// This will return the Next int32 stored.
    int32 GetNextInt();
	/// This will return the Next uint32 stored.
    uint32 GetNextUInt();
	/// This will return the Next string stored.
    std::string GetNextString();
	/// This will return the Next float stored.
    float GetNextFloat();

	/// This will return the int32 at position liInt in the array.
    int32 GetInt(uint32 liInt);
	/// This will return the uint32 at position liInt in the array.
    uint32 GetUInt(uint32 liInt);
	/// This will return the string at position liInt in the array.
    std::string GetString(uint32 liInt);
	/// This will return the float at position liInt in the array.
    float GetFloat(uint32 liInt);

	/// This will return a pointer to the array of int32's.
    int32 *Ints();
	/// This will return a pointer to the array of uint32's.
    uint32 *UInts();
	/// This will return a pointer to the array of floats.
    float *Floats();
	/// This will return a pointer to the array of strings.
    std::string *Strings();
    void EndState(char *lpCurrent);

	/// This will return a the number of int32s in the array.
    int32 IntNumber();
	/// This will return a the number of floats in the array.
    int32 FloatNumber();
	/// This will return a the number of strings in the array.
    int32 StringNumber();
	/// This will return a the number of uint32s in the array.
    int32 UIntNumber();


    int32 GetStringStart(uint32 liString);
    int32 GetIntStart(uint32 liString);
    int32 GetFloatStart(uint32 liString);
    int32 GetUIntStart(uint32 liString);

    void GenIntArray();
    void GenUIntArray();
    void GenStringArray();
    void GenFloatArray();

};

#endif // WTCPARSER_H
