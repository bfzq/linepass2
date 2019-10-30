//
// Created by 山猪 on 2019/10/11.
//

#ifndef LINEPASSC_LINED_ARGS_H
#define LINEPASSC_LINED_ARGS_H

#include "line_args.h"
#include "line_global.h"
struct lined_args_struct
{
  uint32_t listen_port;
  uint32_t pool_num;
  char log_path[LOG_PATH_LEN + 1];
  char verify_id[VERIFY_ID_LEN + 1];
};
typedef struct lined_args_struct lined_args_t;

int lined_parse_option(int argc, char **argv);
void lined_load_option(lined_args_t &args, const opt_t &opt);
#endif //LINEPASSC_LINED_ARGS_H
