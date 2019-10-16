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
  line_args<lined_args_t>::deinit();
}

static int lined_args_init(int argc, char **argv)
{
  int ret = ret_successful;
  line_args<lined_args_t>::init(lined_load_option);
  if ((ret = lined_parse_option(argc, argv) == ret_failed))
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
