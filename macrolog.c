#include <stdlib.h>
#include "macrolog.h"
#include <stdarg.h>

FILE* logFile;

void init_logger(){
    //Create Log File
    logFile = fopen("logs/log.txt","w");
    fclose(logFile);
}

void log_event(char* event){
    logFile = fopen("logs/log.txt","a");
    fprintf(logFile,"%s\n",event);
    fclose(logFile);
}

void log_event_fmt(const char* fmt, ...){
    va_list args;
    va_start(args, fmt);

    logFile = fopen("logs/log.txt","a");
    vfprintf(logFile, fmt, args);
    fprintf(logFile,"\n");
    fclose(logFile);

    va_end(args);
}