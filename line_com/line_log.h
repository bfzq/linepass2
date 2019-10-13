#ifndef _LINE_LOG_
#define _LINE_LOG_

#include "line_global.h"

enum LOG_LEVEL {DEBUG, INFO, WARNING, ERROR};
int line_log_init(const char *file_path);
int line_log_deinit();
void line_log_level(const LOG_LEVEL level);
/* int line_log(const LOG_LEVEL level, const char *tag, const uint ecode, */
/*              const char *msg); */
int line_log(const LOG_LEVEL level, const char *tag, const uint ecode,
             const char *format, ...);

#endif // _LINE_LOG_
