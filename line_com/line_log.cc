#include "line_log.h"

// #include <iostream>

// using namespace std;

#include <cstring>
#include <stdio.h>
#include "ret_code.h"             

int line_log(const LOG_LEVEL level, const char *tag, const uint ecode,
             const char *msg)
{
  char log[1024] = {0};
  char level_str[16];
  // log_level_str(level_str, level);
  switch (level)
  {
  case ERROR:
  {
    sprintf(log, "[time] [ERROR] [%s], errno: %d, %s. \n", tag, ecode, msg);
    break;
  }
  case WARNING:
  {
    sprintf(log, "[time] [WARNING] [%s], %s. \n", tag, msg);
    break;
  }
  case DEBUG:
  {
    sprintf(log, "[time] [DEBUG] [%s], errno: %d, %s. \n", tag, ecode, msg);
    break;
  }
  default:
  {
    sprintf(log, "[time] [INFO] [%s], %s. \n", tag, msg);
    break;
  }
  }
  // TODO: print log to file
  printf(log);
  return ret_successful;
}
