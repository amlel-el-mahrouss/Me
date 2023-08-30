/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <ArchKit/Arch.hpp>
#include <MeKit/String.hpp>
#include <KernelKit/ProcessManager.hpp>

extern "C" void idt_handle_system_call(MeKernel::UIntPtr rsp)
{
    MeKernel::HAL::StackFrame *sf = reinterpret_cast<MeKernel::HAL::StackFrame*>(rsp);
    rt_syscall_handle(sf);

    MeKernel::kcout << "System Call with ID: " << MeKernel::StringBuilder::FromInt("syscall{%}", sf->ID);
}

extern "C" void idt_handle_gpf(MeKernel::UIntPtr rsp)
{
    MUST_PASS(MeKernel::ProcessManager::Shared().Leak().GetCurrent());

    MeKernel::kcout << "RSP:" << MeKernel::StringBuilder::FromInt("sp{%}", rsp);

    MeKernel::kcout << "General Protection Fault, Caused by "
                   << MeKernel::ProcessManager::Shared().Leak().GetCurrent().Leak().GetName();

    MeKernel::ProcessManager::Shared().Leak().GetCurrent().Leak().Crash();
}

extern "C" void idt_handle_scheduler(MeKernel::UIntPtr rsp)
{
    MeKernel::kcout << "RSP:" << MeKernel::StringBuilder::FromInt("sp{%}", rsp);

    MeKernel::kcout << "Will be scheduled back later "
                   << MeKernel::ProcessManager::Shared().Leak().GetCurrent().Leak().GetName();

    /// schedule another process.
    if (!MeKernel::ProcessHelper::StartScheduling())
    {
        MeKernel::kcout << "Let's continue schedule this process...\r\n";
    }
}

extern "C" void idt_handle_pf(MeKernel::UIntPtr rsp)
{
    MeKernel::kcout << "RSP:" << MeKernel::StringBuilder::FromInt("sp{%}", rsp);

    MUST_PASS(MeKernel::ProcessManager::Shared().Leak().GetCurrent());

    MeKernel::kcout << "Segmentation Fault, Caused by "
                   << MeKernel::ProcessManager::Shared().Leak().GetCurrent().Leak().GetName();

    MeKernel::ProcessManager::Shared().Leak().GetCurrent().Leak().Crash();
}

extern "C" void idt_handle_math(MeKernel::UIntPtr rsp)
{
    MeKernel::kcout << "RSP:" << MeKernel::StringBuilder::FromInt("sp{%}", rsp);

    MUST_PASS(MeKernel::ProcessManager::Shared().Leak().GetCurrent());

    MeKernel::kcout << "Math error, Caused by "
                   << MeKernel::ProcessManager::Shared().Leak().GetCurrent().Leak().GetName();

    MeKernel::ProcessManager::Shared().Leak().GetCurrent().Leak().Crash();
}

extern "C" void idt_handle_generic(MeKernel::UIntPtr rsp)
{
    MeKernel::kcout << "RSP:" << MeKernel::StringBuilder::FromInt("sp{%}", rsp);

    MUST_PASS(MeKernel::ProcessManager::Shared().Leak().GetCurrent());

    MeKernel::kcout << "Processor error, Caused by "
                   << MeKernel::ProcessManager::Shared().Leak().GetCurrent().Leak().GetName();

    MeKernel::ProcessManager::Shared().Leak().GetCurrent().Leak().Crash();
}
