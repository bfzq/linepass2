//
// Created by 山猪 on 2019/10/10.
//

#ifndef LINEPASSC_LINE_ARGS_H
#define LINEPASSC_LINE_ARGS_H
#include <set>
#include <string>
typedef std::string arg_key;
typedef std::set<arg_key> args_key;
#define ARG_KEY_LEN (16)
#define ARG_VALUE_LEN (32)
class line_args
{
protected:
  args_key keys_;
  
public:
  virtual int parse_args(int argc, char **argv) = 0;
  void init_keys(args_key keys);
};


#endif //LINEPASSC_LINE_ARGS_H
