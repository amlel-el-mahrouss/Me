/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _INC_THREAD_MANAGER_HPP
#define _INC_THREAD_MANAGER_HPP

#include <CompilerKit/Compiler.hpp>
#include <ArchKit/Arch.hpp>
#include <MeKit/Ref.hpp>

#define kMaxHarts 8

namespace MeKernel
{
    using ThreadID = UInt32;

#ifdef __riscv

constexpr UInt32 kMaxHarts = 8UL;

#else

#endif // ifdef __riscv || else

    enum class ThreadKind
    {
        kSystemReserved, // System reserved thread, well user can't use it
        kStandard, // user thread, cannot be used by kernel
        kFallback, // fallback thread, cannot be used by user if not clear or used by kernel.
        kBoot, // The core we booted from, the mama.
    };

    ///
    /// \name HardwareThread
    /// CPU core (PowerPC, Intel, or DEC Alpha)
    ///

    class HardwareThread final
    {
    public:
        HardwareThread();
        ~HardwareThread();

    public:
        ME_COPY_DEFAULT(HardwareThread)

    public:
        operator bool();

    public:
        void Wake(bool wakeup = false) noexcept;
        void Busy(bool busy = false) noexcept;

    public:
        bool Switch(HAL::StackFrame* stack);
        bool IsWokeup() noexcept;

    public:
        HAL::StackFrame* StackFrame() noexcept;
        ThreadKind Kind() noexcept;
        bool IsBusy() noexcept;
        ThreadID ID() noexcept;

    private:
        HAL::StackFrame* m_Stack;
        ThreadKind m_Kind;
        ThreadID m_ID;
        bool m_Wakeup;
        bool m_Busy;
        Int64 m_PID;

    private:
        friend class HardwareThreadManager;

    };

    ///
    /// \name HardwareThread
    ///
    /// C++ HardwareThread manager to manage other cores and dispatch tasks.
    ///

    class HardwareThreadManager final
    {
    private:
        HardwareThreadManager();

    public:
        ~HardwareThreadManager();

    public:
        ME_COPY_DEFAULT(HardwareThreadManager);

    public:
        bool Switch(HAL::StackFrame* the);
        HAL::StackFrame* GetStack();

    public:
        Ref<HardwareThread> operator[](const SizeT& idx);

    public:
        bool operator!();
        operator bool();

    public:
        static Ref<HardwareThreadManager> Shared();

    private:
        Array<HardwareThread, kMaxHarts> m_ThreadList;
        ThreadID m_CurrentThread;

    };
} // namespace MeKernel

#endif // !_INC_THREAD_MANAGER_HPP
