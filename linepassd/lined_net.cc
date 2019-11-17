#include "lined_net.h"
#include "ret_code.h"
#include <sys/socket.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include "lined_args.h"
#include "line_log.h"
#include "ltype.h"
#include <map>
#include "lined_log_tag.h"
// using namespace std;

struct send_pool_struct
{
  uint send_pos;
  uint8_t *buf;
  uint len;
};
typedef struct send_pool_struct send_pool_t;
typedef std::map<int, send_pool_t> send_pool_map;
static send_pool_map send_pool;

void Linednet::accept_client()
{
  while (true)
  {
    
  }
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
int Linednet::init_sock()
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
  return ret_successful;
}
