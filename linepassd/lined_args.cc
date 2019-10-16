//
// Created by 山猪 on 2019/10/11.
//

#include "lined_args.h"
#include "line_assert.h"
#include "ret_code.h"
#include "lined_args_key.h"
#include "line_log.h"
#include "lined_log_tag.h"
#include "lined_error.h"
#include "debug.h"

void lined_load_option(lined_args_t &args, const opt_t &opt)
{
  if (strcmp(opt.key, LISTEN_PORT) == 0)
  {
    args.listen_port = atoi(opt.value);
  }
  else if (strcmp(opt.key, POOL_NUM) == 0)
  {
    args.pool_num = atoi(opt.value);
  }
  else if (strcmp(opt.key, LOG_PATH) == 0)
  {
    strcpy(args.log_path, opt.value);
  }
  else if (strcmp(opt.key, VERIFY_ID) == 0)
  {
    strcpy(args.verify_id, opt.value);
  }
}

int lined_parse_option(int argc, char **argv)
{
  line_args<lined_args_t> *args = line_args<lined_args_t>::get_instance();
  args->init_keys({LISTEN_PORT, POOL_NUM, LOG_PATH, VERIFY_ID});
  args->parse_args(argc, argv);
#if !defined(DEBUG_OFF)
  const lined_args_t *options = args->get_args();
  line_log(DEBUG, LINE_LOG_TAG_OPTION, 0,
           ".listen_port=%u .pool_num=%u .file_path=%s .verify_id=%s",
           options->listen_port, options->pool_num, options->log_path,
           options->verify_id);
#endif
  return ret_successful;
}
