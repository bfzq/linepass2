#include "lepoll.h"
#include "line_log.h"
#include "line_log_tag.h"
#include <sys/epoll.h>
#include <sys/errno.h>
#include <unistd.h>

static uint wait_epoll_num_ = 0;
static int wait_timeout_ = 0;

ret_type register_epoll(int &epollfd,
                        const int &socked,
                        const uint32_t &register_events,
                        const uint &register_num,
                        const uint wait_epoll_num,
                        const int wait_timeout)
{
  epollfd = epoll_create(register_num);
  if (epollfd == -1)
  {
    line_log(ERROR, LINE_LOG_TAG_NET, errno, "Epoll init error.");
    return ret_failed;
  }
  struct epoll_event ev;
  ev.data.fd = socked;
  ev.events = register_events;
  int r = epoll_ctl(epollfd, EPOLL_CTL_ADD, socked, &ev);
  if (r == -1)
  {
    line_log(ERROR, LINE_LOG_TAG_NET, errno, "Epoll init error.");
    return ret_failed;
  }
  update_epoll_config(wait_epoll_num, wait_timeout);
  return ret_successful;
}

void update_epoll_config(const uint wait_epoll_num,
                         const int wait_timeout)
{
  wait_epoll_num_ = wait_epoll_num;
  wait_timeout_ = wait_timeout;
}

ret_type wait_epoll(const int &epollfd,
                    struct epoll_event *events,
                    uint &events_num)
{
  int r = events_num = epoll_wait(epollfd, events, wait_epoll_num_, wait_timeout_);
  if (r == -1)
  {
    line_log(ERROR, LINE_LOG_TAG_NET, errno, "Wait epoll error.");
    return ret_failed;
  }
  return ret_successful;
}

ret_type cancel_epoll(const int &epoll)
{
  int r = close(epoll);
  if (r == -1)
  {
    line_log(ERROR, LINE_LOG_TAG_NET, errno, "Close epoll error.");
    return ret_failed;
  }
  return ret_successful;
}
