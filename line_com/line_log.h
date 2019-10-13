#ifndef _LINE_LOG_
#define _LINE_LOG_

#include "line_global.h"

enum LOG_LEVEL {DEBUG, INFO, WARNING, ERROR};
int line_log_init();
int line_log(const LOG_LEVEL level, const char *tag, const uint ecode,
             const char *msg);

#endif // _LINE_LOG_
