#ifndef _LINED_NET_H_
#define _LINED_NET_H_
#include "ret_code.h"
class Linednet
{
public:
  Linednet() = default;
  ~Linednet() = default;
public:
  ret_type init_sock();
  ret_type deinit_sock();
  ret_type accept_client();
private:
  int socked;
  int epollfd;
};

#endif // _LINED_NET_H_
