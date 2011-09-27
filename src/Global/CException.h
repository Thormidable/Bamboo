#ifndef __CEXCEPTION_H_INCLUDED__
#define __CEXCEPTION_H_INCLUDED__

#include <string>

using namespace std;

class CException {
public:
	string message;
	CException(	const char* m) : message(m) { };
	CException( string& m ) : message(m) {  };
};


#endif // __CEXCEPTION_H_INCLUDED__
