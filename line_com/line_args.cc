//
// Created by 山猪 on 2019/10/10.
//

#include "line_args.h"
#include "ret_code.h"
#include "line_assert.h"

line_args* line_args::instance_ = nullptr;

int line_args::init(args_key keys)
{
  if (instance_ == nullptr)
    instance_ = new line_args();
  return ret_successful;
}

void line_args::deinit()
{
  if (instance_ != nullptr)
  {
    delete instance_;
    instance_ = nullptr;
  }
}

line_args* line_args::get_instance()
{
  return instance_;
}

int line_args::parse_args(int argc, char **argv)
{
  return ret_successful;
}

arg_value line_args::get_value(const arg_key &key) const
{
  args_map::const_iterator value;
  value = args_.find(key);
  line_assert(value != args_.end());
  return value->second;
}