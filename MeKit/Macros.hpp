/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#ifndef char
#define char(X) ((X)*1024)
#endif

#ifndef KIB
#define KIB(X) (char(X) * 1024)
#endif

#ifndef MIB
#define MIB(X) (KIB(X) * 1024)
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (((sizeof(a) / sizeof(*(a))) / (static_cast<MeKernel::Size>(!(sizeof(a) % sizeof(*(a)))))))
#endif

#ifndef ALIGN
#define ALIGN(X) __attribute__((aligned(X)))
#endif // #ifndef ALIGN

#ifndef ATTRIBUTE
#define ATTRIBUTE(X) __attribute__((X))
#endif // #ifndef ATTRIBUTE

#ifndef __cplusplus
#error[__gorm__] __cplusplus is not defined!
#endif // #ifndef __cplusplus

#ifndef __gorm__
#define __gorm__ (20230208)
#endif // !__gorm__

#ifndef EXTERN_C
#define EXTERN_C()                                                                                                     \
    extern "C"                                                                                                         \
    {
#define END_EXTERN_C()                                                                                                 \
    }                                                                                                                  \
    ;
#endif

#ifndef MAKE_ENUM
#define MAKE_ENUM(NAME)                                                                                                \
    enum NAME                                                                                                          \
    {
#endif

#ifndef END_ENUM
#define END_ENUM()                                                                                                     \
    }                                                                                                                  \
    ;
#endif

#ifndef MAKE_STRING_ENUM
#define MAKE_STRING_ENUM(NAME)                                                                                         \
    namespace NAME                                                                                                     \
    {
#endif

#ifndef ENUM_STRING
#define ENUM_STRING(NAME, VAL) constexpr const char *NAME = VAL
#endif

#ifndef END_STRING_ENUM
#define END_STRING_ENUM() }
#endif

#ifndef Alloca
#define Alloca(Sz) __builtin_alloca(Sz)
#endif // #ifndef Alloca

#ifndef CantReach
#define CantReach() __builtin_unreachable()
#endif

#ifndef __MeKernel__
#define __MeKernel__ "DR1"
#endif
