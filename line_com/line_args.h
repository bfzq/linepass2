//
// Created by 山猪 on 2019/10/10.
//

#ifndef LINEPASSC_LINE_ARGS_H
#define LINEPASSC_LINE_ARGS_H
#include <set>
#include <string>
#include "line_global.h"
#include "ret_code.h"
#include "line_log.h"
#include "line_log_tag.h"
#include "line_error.h"
#include "line_assert.h"

typedef std::string arg_key;
typedef std::set<arg_key> args_key;
#define ARG_KEY_LEN (16)
#define ARG_VALUE_LEN (32)
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
template<typename T>
class line_args
{
 private:
  static line_args *instance_;
  args_key keys_;
  // 静态成员函数指针
  static void(*load_option_)(T&, const opt_t&);
  T args_;
 private:
  line_args() = default;
  ~line_args() = default;
 public:
  static int init(void(*load_option)(T&, const opt_t&));
  static int deinit();
  static line_args* get_instance();
 public:
  int parse_args(int argc, char **argv);
  int update_option(const char *key, const char *value);
  void init_keys(args_key keys);
 public:
  const T* get_args();
};

extern void line_parse_args_item(const char *arg, char **key, uint32_t &key_len,
                                  char **value, uint32_t &value_len);

extern opt_t line_check_option(const args_key &keys, const char *key,
                                const uint32_t key_len, const char *value,
                                const uint32_t value_len);

template<typename T>
line_args<T>* line_args<T>::instance_ = nullptr;

template<typename T>
void(*(line_args<T>::load_option_))(T&, const opt_t&) = nullptr;

template<typename T>
int line_args<T>::init(void(*load_option)(T&, const opt_t&))
{
  line_assert(instance_ == nullptr);
  load_option_ = load_option;
  instance_ = new line_args<T>();
  return ret_successful;
}

template<typename T>
line_args<T>* line_args<T>::get_instance()
{
  line_assert(instance_ != nullptr);
  return instance_;
}

template<typename T>
int line_args<T>::deinit()
{
  line_assert(instance_ != nullptr);
  delete instance_;
  instance_ = nullptr;
  return ret_successful;
}

template<typename T>
int line_args<T>::parse_args(int argc, char **argv)
{
  char *key = nullptr, *value = nullptr;
  uint32_t key_len = 0, value_len = 0;
  for (int i = 1; i < argc; ++i)
  {
    line_parse_args_item(argv[i], &key, key_len, &value, value_len);
    opt_t opt = line_check_option(keys_, key, key_len, value, value_len);
    if (opt == opt_t{0, 0})
    {
      line_log(ERROR, LINE_LOG_TAG_OPTION, LINE_CANT_PARSE_OPTION, "Parse options err.");
      return ret_failed;
    }
    load_option_(args_, opt);
  }
  return ret_successful;
}

template<typename T>
int line_args<T>::update_option(const char *key, const char *value)
{
  opt_t opt = line_check_option(keys_, key, strlen(key), value, strlen(value));
  if (opt == opt_t{0, 0})
  {
    line_log(ERROR, LINE_LOG_TAG_OPTION, LINE_CANT_PARSE_OPTION, "Parse options err.");
    return ret_failed;
  }
  load_option_(args_, opt);
  return ret_successful;
}

template<typename T>
void line_args<T>::init_keys(args_key keys)
{
  keys_ = keys;
}

template<typename T>
const T* line_args<T>::get_args()
{
  return &args_;
}

#endif //LINEPASSC_LINE_ARGS_H
