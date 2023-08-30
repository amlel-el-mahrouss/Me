
/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */
#pragma once

#include <MeKit/Kalloc.hpp>

typedef __SIZE_TYPE__ size_t; // gcc will complain about that

void* operator new(size_t sz) noexcept;
void* operator new[](size_t sz) noexcept;

void operator delete(void *sz) noexcept;
void operator delete(void *, unsigned long);
void operator delete[](void *sz) noexcept;
