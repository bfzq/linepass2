#include "lined_net.h"
#include <sys/socket.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include "lined_args.h"
#include "line_log.h"
#include "ltype.h"
#include <map>
#include "lined_log_tag.h"
#include "lepoll.h"
#include <sys/epoll.h> 
struct send_pool_struct
{
  uint send_pos;
  uint8_t *buf;
  uint len;
};
typedef struct send_pool_struct send_pool_t;
typedef std::map<int, send_pool_t> send_pool_map;
static send_pool_map send_pool;

static const uint register_event_number = 1024;
static const uint wait_epoll_num = 128;
static const uint wait_timeout = 10;


static int lsend();
static int lrecv();

static ret_type real_accept()
{
  return ret_successful;
}

ret_type Linednet::accept_client()
{
  struct epoll_event events[128];
  uint events_num;
  int r = 0;
  int sockfd = 0;
  int event = 0;
  while (true)
  {
    r = wait_epoll(epollfd, events, events_num);
    if (r == ret_failed) return r;
    for (int i = 0; i < events_num; i++)
    {
      sockfd = events[i].data.fd;
      event = events[i].events;
      if (sockfd == socked)
      {
        r = real_accept();
        if (r == ret_failed)
        {
          // TODO: line_log(WARNING, LINED_LOG_TAG_NET, errno, "Socket error.");
        }
      }
      else
      {
        /*
          EPOLLIN：对应的文件描述符上有可读数据。(包括对端SOCKET正常关闭)
          EPOLLOUT：对应的文件描述符上可以写数据；
          EPOLLPRI：对应的文件描述符有紧急的数据可读（这里应该表示有带外数据到来）；
          EPOLLERR：应的文件描述符发生错误；
          EPOLLHUP：对应的文件描述符被挂断；
          EPOLLET：将EPOLL设为边缘触发(Edge Triggered)模式，这是相对于水平触发(Level Triggered)来说的。
          EPOLLONESHOT：只监听一次事件，当监听完这次事件之后，如果还需要继续监听这个socket的话，需要再次把这个socket加入到EPOLL队列里。
        */
        switch (event)
        {
        case EPOLLIN:
        {
          // TODO: lrecv
          break;
        }
        case EPOLLOUT:
        {
          // TODO: lsend
          break;
        }
        case EPOLLERR:
        {
          
          break;
        }
        default:
        {
          break;
        }
        }
      }
    }
  }
  return ret_successful;
}

static void svr_addr_init(struct sockaddr_in &svr_addr)
{
  line_args<lined_args_t> *args = line_args<lined_args_t>::get_instance();
  const lined_args_t *options = args->get_args();
  svr_addr.sin_family = AF_INET;
  svr_addr.sin_port = htons(options->listen_port);
  svr_addr.sin_addr.s_addr = INADDR_ANY;
}
#define BACKLOG (5)
ret_type Linednet::init_sock()
{
  socked = socket(AF_INET, SOCK_STREAM, 0);
  if (socked == -1)
  {
    line_log(ERROR, LINED_LOG_TAG_NET, errno, "Socket error.");
    return ret_failed;
  }
  struct sockaddr_in svr_addr;
  svr_addr_init(svr_addr);
  int r = bind(socked, (struct sockaddr *)&svr_addr, sizeof(struct sockaddr));
  if (r == -1)
  {
    line_log(ERROR, LINED_LOG_TAG_NET, errno, "Bind error.");
    return ret_failed;
  }
  r = listen(socked, BACKLOG);
  if (r = -1)
  {
    line_log(ERROR, LINED_LOG_TAG_NET, errno, "Listen error.");
    return ret_failed;
  }
  r = init_epoll(epollfd, register_event_number);
  if (r = ret_failed)
  {
    line_log(ERROR, LINED_LOG_TAG_NET, errno, "Register epoll error.");
    return ret_failed;
  }
  update_epoll_config(wait_epoll_num, wait_timeout);
  return ret_successful;
}


ret_type Linednet::deinit_sock()
{
  return ret_successful;
}
