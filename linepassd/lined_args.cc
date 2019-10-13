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
lined_args* lined_args::instance_ = nullptr;

static void lined_args_init(lined_args_t &args)
{
  args.listen_port = 0;
  args.pool_num = 0;
  args.log_path[0] = 0;
}

lined_args::lined_args()
{
  lined_args_init(args_);
}

void lined_args::init()
{
  line_assert(instance_ == nullptr);
  instance_ = new lined_args();
}

void lined_args::deinit()
{
  line_assert(instance_ != nullptr);
  delete instance_;
  instance_ = nullptr;
}

lined_args* lined_args::get_instance()
{
  line_assert(instance_ != nullptr);
  return instance_;
}

static void lined_parse_args_item(const char *arg, char **key, uint &key_len,
                                  char **value, uint &value_len)
{
  if (strlen(arg) <= 3)
    return;
  arg += 2;
  *key = (char *) (arg);
  while (*(++arg) != '=');
  key_len = arg - *key;
  arg++;
  *value = (char*)arg;
  value_len = strlen(arg);
}

struct line_option_struct
{
  char key[ARG_KEY_LEN];
  char value[ARG_VALUE_LEN];
  bool operator==(const line_option_struct &opt)
  {
    return strcmp(key, opt.key) == 0 && strcmp(value, opt.value) == 0;
  }
};
typedef line_option_struct opt_t;


static void lined_load_option(lined_args_t &args, const opt_t &opt)
{
  if (strcmp(opt.key, LISTEN_PORT) == 0)
  {
    args.listen_port = atoi(opt.value);
  }
  else if (strcmp(opt.key, POOL_NUM) == 0)
  {
    args.pool_num = atoi(opt.value);
  }
}

static opt_t lined_check_option(const args_key &keys, const char *key,
                                const uint key_len, const char *value,
                                const uint value_len)
{
  opt_t opt = {0, 0};
  line_assert(key != nullptr);
  strncpy(opt.key, key, key_len);
  opt.key[key_len] = '\0';
  args_key::const_iterator right_key = keys.find(opt.key);
  if (right_key != keys.end())
  {
    char tmp_value[ARG_VALUE_LEN];
    strncpy(opt.value, value, value_len);
    opt.value[value_len] = '\0';
  }
  else
  {
    line_log(ERROR, LINED_LOG_TAG_OPTION, LINED_UNKNOWN_OPTION,
             "Uknown option %s", opt.key);
    opt = {0, 0};
  }
  return opt;
}

int lined_args::parse_args(int argc, char **argv)
{
  char *key = nullptr, *value = nullptr;
  uint key_len = 0, value_len = 0;
  for (int i = 1; i < argc; ++i)
  {
    lined_parse_args_item(argv[i], &key, key_len, &value, value_len);
    opt_t opt = lined_check_option(keys_, key, key_len, value, value_len);
    if (opt == opt_t{0, 0})
    {
      //TODO: error log
      line_log(ERROR, LINED_LOG_TAG_OPTION, LINED_CANT_PARSE_OPTION, "Parse options err.");
      return ret_failed;
    }
    lined_load_option(args_, opt);
  }
  line_log(DEBUG, LINED_LOG_TAG_OPTION, 0,
           ".listen_port=%u .pool_num=%u .file_path=%s.",
           args_.listen_port, args_.pool_num, args_.log_path);
  return ret_successful;
}
