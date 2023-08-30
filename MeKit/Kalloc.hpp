/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

// last-rev 5/03/23
// file: kmalloc.hpp
// description: memory allocation routines.

#include <MeKit/Foundation.hpp>
#include <MeKit/Pmm.hpp>

namespace MeKernel
{
    Int32 kernel_delete_ptr(voidPtr ptr);
    voidPtr kernel_new_ptr(SizeT sz, const bool rw, const bool user);
} // namespace MeKernel
