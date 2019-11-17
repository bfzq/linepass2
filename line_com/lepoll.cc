#include "lepoll.h"
#include "line_log.h"
#include "line_log_tag.h"
#include <sys/epoll.h>
#include <sys/errno.h>
ret_type register_epoll(int socked, uint32_t events, uint size)
{
  int epollfd;
  epollfd = epoll_create(size);
  if (epollfd == -1)
  {
    line_log(ERROR, LINE_LOG_TAG_NET, errno, "Epoll init error.");
    return ret_failed;
  }
  struct epoll_event ev;
  ev.data.fd = socked;
  ev.events = events;
  int r = epoll_ctl(epollfd, EPOLL_CTL_ADD, socked, &ev);
  if (r == -1)
  {
    line_log(ERROR, LINE_LOG_TAG_NET, errno, "Epoll init error.");
    return ret_failed;
  }
  return ret_successful;
}
