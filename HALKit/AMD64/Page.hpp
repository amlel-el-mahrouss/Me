/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <MeKit/Foundation.hpp>

#ifndef PTE_MAX
#define PTE_MAX (512)
#endif //! PTE_MAX

#ifndef PTE_ALIGN
#define PTE_ALIGN (4096)
#endif //! PTE_ALIGN

extern "C" void flush_tlb(MeKernel::UIntPtr VirtualAddr);
extern "C" void write_cr3(MeKernel::UIntPtr pde);
extern "C" void write_cr0(MeKernel::UIntPtr bit);
extern "C" MeKernel::UIntPtr read_cr0();
extern "C" MeKernel::UIntPtr read_cr2();
extern "C" MeKernel::UIntPtr read_cr3();

namespace MeKernel::HAL
{
    struct PageTable64
    {
        bool Present: 1;
        bool Rw: 1;
        bool User: 1;
        bool Wt: 1;
        bool Cache: 1;
        bool Accessed: 1;
        MeKernel::Int32 Reserved: 6;
        MeKernel::UIntPtr PhysicalAddress: 36;
        MeKernel::Int32 Reserved1: 15;
        bool ExecDisable: 1;

    };

    PageTable64 *hal_alloc_page(SizeT sz, Boolean rw, Boolean user);

    UIntPtr hal_create_page(Boolean rw, Boolean user);
} // namespace MeKernel::HAL
