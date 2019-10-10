//
// Created by 山猪 on 2019/10/10.
//

#include "lined_main.h"
#include "ret_code.h"
#include "lined_args.h"
#include "lined_args_key.h"
static void deinit()
{
  // init顺序和deinit顺序相逆
  lined_args::deinit();
}

static int lined_args_init(int argc, char **argv)
{
  int ret = ret_successful;
  lined_args::init();
  line_args *args = lined_args::get_instance();
  args->init_keys({LISTEN_PORT, POOL_NUM});
  if ((ret = args->parse_args(argc, argv) == ret_failed))
    return ret_failed;
  return ret_successful;
}

int lined_main(int argc, char **argv)
{
  switch (0)
  {
  case 0:
  {
    int ret = ret_successful;
    ret = lined_args_init(argc, argv);
    if (ret == ret_failed)
      break;
    return ret_successful;
  }
  }
  deinit();
  return ret_failed;
}