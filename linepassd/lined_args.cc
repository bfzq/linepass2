//
// Created by 山猪 on 2019/10/11.
//

#include "lined_args.h"
#include "line_assert.h"
#include "ret_code.h"
lined_args* lined_args::instance_ = nullptr;

static void lined_args_init(lined_args_t &args)
{
  args.listen_port = 0;
  args.pool_num = 0;
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

static int lined_check_key(const char *key, const uint key_len)
{
  return ret_successful;
}

static int lined_check_value(const char *key, const uint key_len,
                             const char *value, const uint value_len)
{
  return ret_successful;
}

int lined_args::parse_args(int argc, char **argv)
{
  char *key = nullptr, *value = nullptr;
  uint key_len = 0, value_len = 0;
  for (int i = 1; i < argc; ++i)
  {
    lined_parse_args_item(argv[i], &key, key_len, &value, value_len);
    if (lined_check_key(key, key_len) == ret_failed)
    {
      //TODO: error log
      return ret_failed;
    }
    if (lined_check_value(key, key_len, value, value_len) == ret_failed)
    {
      //TODO: error log
      return ret_failed;
    }
  }
  return ret_successful;
}
