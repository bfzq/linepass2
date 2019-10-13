#include "line_log.h"

// #include <iostream>

// using namespace std;

#include <cstring>
#include <stdio.h>
#include "ret_code.h"             
#include <cstdarg>

static LOG_LEVEL print_level = DEBUG;

static void line_log_cat(char *log, const LOG_LEVEL level, const char *tag,
                         const uint ecode, const char *msg)
{
  switch (level)
  {
  case ERROR:
  {
    sprintf(log, "[time][ERROR][%s], errno: %d, %s. \n", tag, ecode, msg);
    break;
  }
  case WARNING:
  {
    sprintf(log, "[time][WARNING][%s], %s. \n", tag, msg);
    break;
  }
  case DEBUG:
  {
    sprintf(log, "[time][DEBUG][%s], errno: %d, %s. \n", tag, ecode, msg);
    break;
  }
  default:
  {
    sprintf(log, "[time][INFO][%s], %s. \n", tag, msg);
    break;
  }
  }
}

static int line_log_flush_to_file(const char *log)
{
  // TODO: print log to file
  printf(log);
  return ret_successful;
}

int line_log(const LOG_LEVEL level, const char *tag, const uint ecode,
             const char *msg)
{
  if (level < print_level)
    return ret_successful;
  char log[1024] = {0};
  line_log_cat(log, level, tag, ecode, msg);
  return line_log_flush_to_file(log);
}

int line_log(const LOG_LEVEL level, const char *tag, const uint ecode,
             const char *format, ...)
{
  if (level < print_level)
    return ret_successful;
  char msg[512], log[1024];
  va_list args;
  va_start(args, format);
  vsnprintf(msg, 1024, format, args);
  va_end(args);
  line_log_cat(log, level, tag, ecode, msg);
  return line_log_flush_to_file(log);
}

void line_log_level(const LOG_LEVEL level)
{
  print_level = level;
}

int line_log_init(const char *file_path)
{
  return ret_successful;
}

int line_log_deinit()
{
  return ret_successful;
}


