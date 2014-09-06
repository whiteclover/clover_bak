#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <cstdio.h>
#include <cstring.h>
#include <cstdlib.h>
#include "SingletonT.h"

enum LogLevel
{
    DEBUG = 0,
    INFO = 1,
    WARN = 2,
    ERROR = 3
}

static char *LEVELS[4] =
{
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR"
};


class Logger {

    public:
        Logger(const char * filepath=NULL);
        ~Logger();
        void Log(LogLevel level, int lineno, const char * funname, const char * fmt, ...);

        void SetLevel(LogLevel level) {_level=level};
        int SetIdent(const char * ident) const { memcpy(_ident, ident, strlen(ident));};


    private:

        LogLevel _level;
        char _log_dir[1024];
        char _ident[128];
        FILE * _file;
};


#define sLogger SingletonT< Logger >::Instance()

#define CLOVER_LOG(level, ...) sLogger.Log(level, __LINE__, __FUNCTION__, __VA_ARGS__)
#define CLOVER_DLOG(...) Logger.Log(DEBUG, __LINE__, __FUNCTION__, __VA_ARGS__)
#define CLOVER_ILOG(...) Logger.Log(INFO, __LINE__, __FUNCTION__, __VA_ARGS__)
#define CLOVER_WLOG(...) Logger.Log(WARN, __LINE__, __FUNCTION__, __VA_ARGS__)
#define CLOVER_ELOG(...) Logger.Log(ERROR, __LINE__, __FUNCTION__, __VA_ARGS__)

#endif // __LOGGER_H__