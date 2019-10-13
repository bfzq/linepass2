//
// Created by 山猪 on 2019/10/11.
//

#ifndef LINEPASSC_LINED_ARGS_H
#define LINEPASSC_LINED_ARGS_H

#include "line_args.h"
#include "line_global.h"
struct lined_args_struct
{
  uint listen_port;
  uint pool_num;
  char log_path[LOG_PATH_LEN + 1];
  char verify_id[VERIFY_ID_LEN + 1];
};
typedef struct lined_args_struct lined_args_t;
class lined_args : public line_args
{
private:
  static lined_args *instance_;
  lined_args_t args_;
private:
  lined_args();
  ~lined_args() = default;
public:
  static void init();
  static void deinit();
  static lined_args* get_instance();
public:
  int parse_args(int argc, char **argv) override;
};


#endif //LINEPASSC_LINED_ARGS_H
