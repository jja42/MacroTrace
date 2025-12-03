#include "macrosave.h"
#include <string.h>
#include <ctype.h>

FILE* temptraceFile;


void access_temp_trace_file()
{
//Create Trace File
temptraceFile = fopen("temp/temp_trace.txt", "w");

//Close the file
fclose(temptraceFile); 

//Reopen in append
temptraceFile = fopen("temp/temp_trace.txt", "a");
}

void write_temp_trace_file(char* line){
    fwrite(line, 1, strlen(line), temptraceFile);
    fprintf(temptraceFile,"\n");
}

void close_temp_trace_file(){
    fclose(temptraceFile);
}

void sanitize_filename(char *str) {
    for (size_t i = 0; i < strlen(str); i++) {
        if (!isalnum(str[i]) && str[i] != '-' && str[i] != '_') {
            str[i] = '_';
        }
    }
}

void save_trace_file(char* filename){
    sanitize_filename(filename);

    int character;

    //Read From Temp File
    FILE* traceFile;
    temptraceFile = fopen("temp/temp_trace.txt","r");

    char traceFilename[strlen(filename)+20];
    snprintf(traceFilename, sizeof(traceFilename), "tracefiles/%s.txt", filename);

    //Create Trace File
    traceFile = fopen(traceFilename, "w");
    if (traceFilename == NULL)
    {
        printf("ERROR: Cannot create macro file: %s\n", traceFilename);
        return;
    }

    // Read contents from file
    while ((character = fgetc(temptraceFile)) != EOF)
    {
        fputc(character, traceFile);
    }

    printf("Macro Saved to %s\n", traceFilename);

    fclose(temptraceFile);
    fclose(traceFile);
    return;
}

