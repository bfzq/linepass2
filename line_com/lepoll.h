#ifndef _LEPOLL_H_
#define _LEPOLL_H_

#include "ltype.h"
#include "ret_code.h"
#include <stdint.h>
ret_type register_epoll(int &epollfd,
                        const int &socked,
                        const uint32_t &register_events,
                        const uint &register_num,
                        const uint wait_epoll_num = 10,
                        const int wait_timeout = 10);
void update_epoll_config(const uint wait_epoll_num = 10,
                         const int wait_timeout = 10);
ret_type wait_epoll(const int &epollfd,
                    struct epoll_event *events,
                    uint events_num);
ret_type cancel_epoll(const int &epoll);
#endif // _LEPOLL_H_
