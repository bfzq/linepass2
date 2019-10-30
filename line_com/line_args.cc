//
// Created by 山猪 on 2019/10/10.
//

#include "line_args.h"

// #include "line_error.h"



void line_parse_args_item(const char *arg, char **key, uint32_t &key_len,
                          char **value, uint32_t &value_len)
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



opt_t line_check_option(const args_key &keys, const char *key,
                        const uint32_t key_len, const char *value,
                        const uint32_t value_len)
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
    line_log(ERROR, LINE_LOG_TAG_OPTION, LINE_UNKNOWN_OPTION,
             "Uknown option %s", opt.key);
    opt = {0, 0};
  }
  return opt;
}

