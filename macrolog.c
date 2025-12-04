#include <stdlib.h>
#include "macrolog.h"

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