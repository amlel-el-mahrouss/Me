/*
 *	========================================================
 *
 *	MeKernel 	Date Added: 13/02/2023
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef __CRC32_H__
#define __CRC32_H__

#include <MeKit/Foundation.hpp>

#define kCrcCnt (256)

namespace MeKernel
{
    extern UInt crc32_tab[kCrcCnt];
    Int crc32(const Char *crc, Int len);
} // namespace MeKernel

#endif // !__CRC32_H__
