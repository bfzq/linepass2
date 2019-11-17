#ifndef _LEPOLL_H_
#define _LEPOLL_H_

#include "ltype.h"
#include "ret_code.h"
#include <stdint.h>
ret_type register_epoll(int socked, uint32_t events, uint size);

#endif // _LEPOLL_H_
