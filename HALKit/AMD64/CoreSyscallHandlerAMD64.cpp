/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <KernelKit/PermissionManager.hpp>
#include <HALKit/AMD64/Processor.hpp>

#include <ArchKit/Arch.hpp>

MeKernel::Array<void (*)(MeKernel::Int32 id, MeKernel::HAL::StackFrame *), kMaxSyscalls> kSyscalls;

// IDT System Call Handler.
// NOTE: don't trust the user.
extern "C" void rt_syscall_handle(MeKernel::HAL::StackFrame *stack)
{
    for (MeKernel::SizeT index = 0UL; index < kMaxSyscalls; ++index)
    {
        (kSyscalls[index].Leak().Leak())(stack->ID, stack);
    }
}
