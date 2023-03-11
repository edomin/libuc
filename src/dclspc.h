#ifndef UC_SRC_DCLSPC_H
#define UC_SRC_DCLSPC_H

#ifdef __TINYC__
    #define UC_ATTR_const
    #define UC_ATTR_pure
#else
    #define UC_ATTR_const __attribute__((const))
    #define UC_ATTR_pure __attribute__((pure))
#endif

#define UC_ATTR(ATTR) UC_ATTR_ ## ATTR

#endif
