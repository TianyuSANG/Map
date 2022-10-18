
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>

#include "Log.h"

void RecordLog(const char* path, const char* func, const char* file, const unsigned int line,
    const char* type, const char* format, ...)
{
    char timeStr[256];
    struct timeval tv;
    gettimeofday(&tv, NULL);
    sprintf(timeStr, "[s:%ld, ms:%ld]", tv.tv_sec, tv.tv_usec / 1000);

    va_list ap;
    va_start(ap, format);
    char fmtStr[2048];
    vsnprintf(fmtStr, sizeof(fmtStr), format, ap);
    va_end(ap);

    if (path) {
        FILE* log = fopen(path, "a");
        if (log != NULL) {
            fprintf(log, "[%s]%s[%s@%s:%d] %s\n", type, timeStr, func, file, line, fmtStr);
            fclose(log);
        } else {
            fprintf(stderr, "[%s]%s[%s@%s:%d] %s\n", type, timeStr, func, file, line, fmtStr);
        }
    } else {
        fprintf(stdout, "[%s]%s[%s@%s:%d] %s\n", type, timeStr, func, file, line, fmtStr);
    }
}