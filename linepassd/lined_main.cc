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

static ret_type lined_args_init(int argc, char **argv)
{
  ret_type ret = ret_successful;
  line_args<lined_args_t>::init(lined_load_option);
  if ((ret = lined_parse_option(argc, argv) == ret_failed))
    return ret_failed;
  return ret_successful;
}

static ret_type main_init(int argc, char **argv)
{
  ret_type ret = ret_successful;
  switch (0)
  {
  case 0:
  {
    ret = lined_args_init(argc, argv);
    if (ret == ret_failed)
      break;
  }
  }
  return ret;
}

ret_type lined_main(int argc, char **argv)
{
  if (main_init(argc, argv) == ret_failed)
  {
    deinit();
    return ret_failed;
  }
  return ret_successful;
}
