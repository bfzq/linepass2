//
// Created by 山猪 on 2019/10/10.
//

#ifndef LINEPASSC_LINE_ARGS_H
#define LINEPASSC_LINE_ARGS_H
#include <map>
#include <set>
#include <string>
typedef std::string arg_key;
typedef std::string arg_value;
typedef std::set<arg_key> args_key;
typedef std::map<arg_key, arg_value> args_map;
class line_args
{
private:
  args_map args_;
  static line_args *instance_;
  args_key keys_;
private:
  line_args() = default;
  ~line_args() = default;

public:
  static int init(args_key keys);
  static void deinit();
  static line_args* get_instance();

public:
  arg_value get_value(const arg_key &key) const;
  int parse_args(int argc, char **argv);
};


#endif //LINEPASSC_LINE_ARGS_H
