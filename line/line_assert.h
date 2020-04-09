//
// Created by 山猪 on 2019/10/10.
//

#ifndef LINEPASSC_LINE_ASSERT_H
#define LINEPASSC_LINE_ASSERT_H

#include <assert.h>
#include "debug.h"
inline void line_assert(bool value)
{
#if !defined(DEBUG_OFF)
  assert(value);
#endif
}

#endif //LINEPASSC_LINE_ASSERT_H
