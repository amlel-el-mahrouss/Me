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
#include <MeKit/Function.hpp>

#ifdef __x86_64__
#   include <HALKit/AMD64/Hypervisor.hpp>
#   include <HALKit/AMD64/Processor.hpp>
#   include <HALKit/AMD64/Page.hpp>
#elif defined(__powerpc)
#   include <HALKit/PowerPC/Processor.hpp>
#endif

namespace MeKernel
{
    class SystemCallDefaultImpl final
    {
    public:
        static Int32 Exec() { return 0; }

    };

    template <SSizeT ID, typename CLS>
    class SystemCall final
    {
    public:
        SystemCall()
        {
            kcout << "SystemCall::SystemCall";
        }

        ~SystemCall()
        {
            kcout << "SystemCall::~SystemCall";
        }

        SystemCall &operator=(const SystemCall &) = default;
        SystemCall(const SystemCall &) = default;

        // Should not be called alone!
        template <typename RET>
        RET Exec() const
        {
            kcout << "SystemCall->Exec<RET>()";
            return CLS::Exec();
        }

    };

    constexpr static inline SSizeT syscall_hash(const char *seed, int mul)
    {
        SSizeT hash = 0;

        for (SSizeT idx = 0; seed[idx] != 0; ++idx)
        {
            hash += seed[idx];
            hash ^= mul;
        }

        return hash;
    }
} // namespace MeKernel

#define kMaxSyscalls 0x100
#define kSyscallGate 0x80

extern MeKernel::Array<void (*)(MeKernel::Int32 id, MeKernel::HAL::StackFrame *), kMaxSyscalls> kSyscalls;

extern "C" void rt_wait_for_io();
extern "C" void rt_syscall_handle(MeKernel::HAL::StackFrame *stack);
extern "C" MeKernel::HAL::StackFrame* rt_get_current_context();
extern "C" int rt_do_context_switch(MeKernel::HAL::StackFrame* stackLeft, MeKernel::HAL::StackFrame* stackRight);
