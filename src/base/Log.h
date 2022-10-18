#ifndef __LOG_H__
#define __LOG_H__

#define LOG_LEVEL_INFO  "INFO"
#define LOG_LEVEL_ERROR "ERROR"

void RecordLog(const char* path, const char* func, const char* file, const unsigned int line,
    const char* type, const char* format, ...);

/* 打印日志到文件中
Parameter:
    @path: IN
    @type: IN the level of log
    @format: IN */
#define LOGF(path, type, format, ...) RecordLog(path, __func__, __FILE__, __LINE__, type, format, ##__VA_ARGS__)

/* 打印日志到控制台
Parameter:
    @type: IN the level of log
    @format: IN */
#define LOGC(type, format, ...) RecordLog(NULL, __func__, __FILE__, __LINE__, type, format, ##__VA_ARGS__)

#endif