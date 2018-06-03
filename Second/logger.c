#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include "logger.h"

static const char* logLevel2Txt(enum LEVEL l)
{
     return 
          l == LOG_INFO ? "[INFO ]" :
          l == LOG_WARN ? "[WARN ]" :
                          "[ERROR]"
     ;
}

void logger( enum LEVEL l, const char* format, ...)
{
     va_list args;
     va_start (args, format);

     FILE* log_file = fopen("logger.log", "a");

     if(log_file)
     {
          time_t now;
          char* time_str = 0;
          memset( &now, 0, sizeof(time_t) );
          time(&now);
          time_str = ctime(&now);
          if(time_str)
          {
               time_str[strlen(time_str)-1] = 0; // rid off trailing '\n'
               fprintf(log_file, "%20s%10s ", time_str, logLevel2Txt(l) );
               vfprintf(log_file, format, args);
               fprintf(log_file,"\n");
          }
          fclose(log_file);
     }

     va_end(args);
}

