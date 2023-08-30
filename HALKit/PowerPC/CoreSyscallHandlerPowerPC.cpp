/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <ArchKit/Arch.hpp>

MeKernel::Array<void (*)(MeKernel::Int32 id, MeKernel::HAL::StackFrame *), kMaxSyscalls> kSyscalls;

extern "C" void rt_syscall_handle(MeKernel::HAL::StackFrame *stack)
{
    for (MeKernel::SizeT index = 0UL; index < kMaxSyscalls; ++index)
    {
        (kSyscalls[index].Leak().Leak())(stack->ID, stack);
    }
}
