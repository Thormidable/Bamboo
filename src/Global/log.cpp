
#include "../WTBamboo.h"

#ifdef USE_LOGGING


shared_ptr<dwLog> spGlobalLogger;

void registerGlobalLogger(shared_ptr<dwLog> spLogger) {
    spGlobalLogger=spLogger;
}

shared_ptr<dwLog> getGlobalLogger() {
    return spGlobalLogger;
}

#endif
