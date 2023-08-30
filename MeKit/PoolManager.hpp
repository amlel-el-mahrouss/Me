/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <MeKit/Array.hpp>
#include <MeKit/ArrayList.hpp>
#include <MeKit/ErrorOr.hpp>
#include <MeKit/PageManager.hpp>
#include <MeKit/Pmm.hpp>
#include <MeKit/Ref.hpp>

// last-rev 24/04/23
// file: pool.hpp
// description: memory pool for scheduler.

#define kPoolMaxSz 4096
#define kPoolMag 0x5500A1

namespace MeKernel
{
    enum
    {
        kPoolHypervisor = 0x2,
        kPoolShared = 0x4,
        kPoolUser = 0x6,
        kPoolRw = 0x8,
    };

    struct PoolHeader final
    {
        UInt32 Magic;
        Int32 Flags;
        Boolean Free;
        UIntPtr Pad;
    };

    VoidPtr pool_new_ptr(const MeKernel::Size& Size, Int Flags = 0);
    Int32 pool_free_ptr(MeKernel::voidPtr Pointer);
} // namespace MeKernel
