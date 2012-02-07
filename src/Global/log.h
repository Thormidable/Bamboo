#ifndef __LOG_H__
#define __LOG_H__

#define LOG_TRACE
#define USE_LOGGING

#define LOG_LEVEL_TRACE
#define LOG_LEVEL_FIXME
#define LOG_LEVEL_WARN
#define LOG_LEVEL_ERROR

#ifdef LOG_TRACE
	#define trace(x) cout << x << endl;
#else
	#define trace(x)
#endif



#ifdef USE_LOGGING



#include <string>
#include <ostream>
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>

#ifdef LOG_LEVEL_TRACE
	#define TRACE2(sys,x) \
		{stringstream dw_log_msg; dw_log_msg << "trace:" << __FILE__ << "." << __func__ <<  "." << __LINE__ << ":" << x;  \
		getGlobalLogger()->printToSource((sys),dw_log_msg.str());}
	#define TRACE(x) TRACE2(__scopeSource,x)
#else
	#define TRACE(sys,x)
#endif

#ifdef LOG_LEVEL_FIXME
	#define FIXME2(sys,x) \
		{stringstream dw_log_msg; dw_log_msg << "fixme:" << __FILE__ << "." << __func__ <<  "." << __LINE__ << ":" << x;  \
		getGlobalLogger()->printToSource((sys),dw_log_msg.str());}
	#define FIXME(x) FIXME2(__scopeSource,x)
#else
	#define FIXME(sys,x)
#endif

#ifdef LOG_LEVEL_WARN
	#define WARN2(sys,x) \
		{stringstream dw_log_msg; dw_log_msg << "WARN:" << __FILE__ << "." << __func__ <<  "." << __LINE__ << ":" << x;  \
		getGlobalLogger()->printToSource((sys),dw_log_msg.str());}
	#define WARN(x) WARN2(__scopeSource,x)
#else
	#define WARN(sys,x)
#endif

#ifdef LOG_LEVEL_ERROR
#define TRACEERROR2(sys,x) \
		{stringstream dw_log_msg; dw_log_msg << "ERROR:" << __FILE__ << "." << __func__ <<  "." << __LINE__ << ":" << x;  \
		getGlobalLogger()->printToSource((sys),dw_log_msg.str());}
	#define TRACEERROR(x) TRACEERROR2(__scopeSource,x)
#else
	#define TRACEERROR(x,sys)
#endif

#define LOGGING_INIT() registerGlobalLogger(shared_ptr<dwLog>(new dwLog()));

#define LOGGING_SET_SCOPE_SOURCE(x) string __scopeSource((x));

#define LOGGING_ADD_SOURCE(x) 	getGlobalLogger()->addSource((x));
#define LOGGING_ADD_SINK(x,f) 	getGlobalLogger()->addSink((x),stream_ptr(new ofstream((f))));
#define LOGGING_ADD_FILE(x,f) 	getGlobalLogger()->addSource((x));\
								getGlobalLogger()->addSink((x),stream_ptr(new ofstream((f))));\
								getGlobalLogger()->bindSourceToSink((x),(x));

class dwLog;

using namespace std;
using namespace boost;

typedef shared_ptr<ostream> stream_ptr;


void registerGlobalLogger(shared_ptr<dwLog> spLogger);
shared_ptr<dwLog> getGlobalLogger();


class dwLog {
public:
	dwLog() : globalLog("all.log") {

	}

	void addSink(string name,stream_ptr sink) {
		sinks[name]=sink;
	}

	void addSource(string name) {
		sources[name]=sinkList_ptr(new sinkList);
	}

	bool bindSourceToSink(const string& sourceName,const string& sinkName) {
		sinkMap::iterator sinkIter = sinks.find(sinkName);
		sourceMap::iterator sourceIter = sources.find(sourceName);

		if(sinkIter == sinks.end()) {
			cerr << "Unrecognized logging sink \"" << sinkName << "\"" << endl;
			return false;
		} else if (sourceIter == sources.end()) {
			cerr << "Unrecognized source \"" << sourceName << "\"" << endl;
			return false;
		} else {
			stream_ptr thisSink = sinkIter->second;
			sinkList_ptr thisSinkList = sourceIter->second;
			thisSinkList->push_back(thisSink);
			return true;
		}
	}

	bool printToSource(const string& sourceName,const string& msg) {
		//Print to the global log
		globalLog << msg << endl;
		if(strcmp(msg.c_str(),"all")==0) {
			//Things addressed to "all" need not go anywhere else
			return true;
		}

		sourceMap::iterator sourceIter = sources.find(sourceName);

		if(sourceIter == sources.end()) {
			cerr << "Cannot find logging source " << sourceName << " and so cannot write to it. The message was " << msg << endl;
			return false;
		}
		sinkList_ptr thisSinkList = sourceIter->second;

		for (sinkList::iterator i=thisSinkList->begin();i!=thisSinkList->end();i++) {
			**i << msg << endl;
		}
		return true;
	}

	stream_ptr getStream(string name) {
		sinkMap::iterator iter = sinks.find(name);
		if(iter != sinks.end()) {
			return iter->second;
		} else {
			cerr << "Unrecognized Output stream \"" << name << "\"" << endl;
			stream_ptr out(new ofstream("bad_ostream.log"));
			return out;
		}
	}


private:
	typedef vector<stream_ptr> sinkList;
	typedef shared_ptr<sinkList> sinkList_ptr;
	typedef map<string,sinkList_ptr> sourceMap;
	typedef map<string,stream_ptr> sinkMap;

	ofstream globalLog;
	sourceMap sources;
	sinkMap sinks;
};

#endif


#endif
