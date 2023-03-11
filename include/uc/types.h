#ifndef UC_INCLUDE_UC_TYPES_H
#define UC_INCLUDE_UC_TYPES_H

#include "uc/config.h"

#ifdef __TINYC__
    #include <stddef.h>
    typedef uint32_t uint_least32_t;
#else
    #include <stdint.h>
#endif

#ifndef UC_HAVE_UINT_LEAST24_T
    typedef uint_least32_t uint_least24_t;
#endif

#endif
