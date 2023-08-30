/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _INC_CL_HPP
#define _INC_CL_HPP

#include <MeKit/Foundation.hpp>

#define ME_COPY_DELETE(KLASS)                                                                                         \
    KLASS &operator=(const KLASS &) = delete;                                                                          \
    KLASS(const KLASS &) = delete;

#define ME_COPY_DEFAULT(KLASS)                                                                                        \
    KLASS &operator=(const KLASS &) = default;                                                                         \
    KLASS(const KLASS &) = default;

#define ME_MOVE_DELETE(KLASS)                                                                                         \
    KLASS &operator=(KLASS &&) = delete;                                                                               \
    KLASS(KLASS &&) = delete;

#define ME_MOVE_DEFAULT(KLASS)                                                                                        \
    KLASS &operator=(KLASS &&) = default;                                                                              \
    KLASS(KLASS &&) = default;


#ifdef __GNUC__
#   define CXX_TECH "GNU"
#else
#   define CXX_TECH "C++"
#endif

#endif /* ifndef _INC_CL_HPP */
