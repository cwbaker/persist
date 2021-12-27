#pragma once

#if defined PERSIST_ASSERT && !defined NDEBUG
#define assert(condition) PERSIST_ASSERT(condition)
#else
#include <assert.h>
#endif
