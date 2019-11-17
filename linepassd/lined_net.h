#ifndef _LINED_NET_H_
#define _LINED_NET_H_

class Linednet
{
public:
  Linednet() = default;
  ~Linednet() = default;
public:
  int init_sock();
  void accept_client();
private:
  int socked;
};

int lsend();
int lrecv();

#endif // _LINED_NET_H_
