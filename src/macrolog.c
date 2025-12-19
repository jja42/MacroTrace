#include <stdlib.h>
#include "macrolog.h"
#include <stdarg.h>

FILE* logFile;

void init_logger(){
    //Create Log File
    logFile = fopen("logs/log.txt","w");
    //close file
    fclose(logFile);
}

void log_event(char* event){
    //open file for appending
    logFile = fopen("logs/log.txt","a");
    //print string to file
    fprintf(logFile,"%s\n",event);
    //close file
    fclose(logFile);
}

void log_event_fmt(const char* fmt, ...){
    va_list args;
    va_start(args, fmt);

    //open file for appending
    logFile = fopen("logs/log.txt","a");
    //print formatted string to file
    vfprintf(logFile, fmt, args);
    //print new line to file
    fprintf(logFile,"\n");
    //close file
    fclose(logFile);

    va_end(args);
}