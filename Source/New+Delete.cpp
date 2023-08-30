/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <MeKit/Kalloc.hpp>
#include <MeKit/New.hpp>

void* operator new[](size_t sz) { return MeKernel::kernel_new_ptr(sz, true, false); }

void* operator new(size_t sz) { return MeKernel::kernel_new_ptr(sz, true, false); }

void operator delete[](void* ptr) { MeKernel::kernel_delete_ptr(ptr); }

void operator delete(void* ptr) { MeKernel::kernel_delete_ptr(ptr); }

void operator delete(void* ptr, size_t sz) { MeKernel::kernel_delete_ptr(ptr); }