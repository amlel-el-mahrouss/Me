/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _KERNELKIT_PROCESS_HPP
#define _KERNELKIT_PROCESS_HPP

#include <KernelKit/PermissionManager.hpp>
#include <MeKit/MutableArray.hpp>
#include <MeKit/LockDelegate.hpp>
#include <MeKit/PoolManager.hpp>
#include <ArchKit/Arch.hpp>

#define kMinMicroTime AffinityKind::kVeryLowUsage
#define kPoolSize (1024 / 4096)

namespace MeKernel
{
    typedef Int64 ProcessID;

    inline constexpr SizeT kProcessLen = 256U;

    class Process;
    class ProcessManager;
    class ProcessHelper;

    enum class ProcessStatus : Int
    {
        kStarting,
        kRunning,
        kKilled,
        kFrozen,
        kDead
    };

    enum class AffinityKind : Int
    {
        kInvalid = 300,
        kVeryHigh = 250,
        kHigh = 200,
        kStandard = 150,
        kLowUsage = 100,
        kVeryLowUsage = 50,
    };

    inline bool operator<(AffinityKind lhs, AffinityKind rhs)
    {
        Int lhs_int = static_cast<Int>(lhs);
        Int rhs_int = static_cast<Int>(rhs);

        return lhs_int < rhs_int;
    }

    inline bool operator>(AffinityKind lhs, AffinityKind rhs)
    {
        Int lhs_int = static_cast<Int>(lhs);
        Int rhs_int = static_cast<Int>(rhs);

        return lhs_int > rhs_int;
    }

    inline bool operator<=(AffinityKind lhs, AffinityKind rhs)
    {
        Int lhs_int = static_cast<Int>(lhs);
        Int rhs_int = static_cast<Int>(rhs);

        return lhs_int <= rhs_int;
    }

    inline bool operator>=(AffinityKind lhs, AffinityKind rhs)
    {
        Int lhs_int = static_cast<Int>(lhs);
        Int rhs_int = static_cast<Int>(rhs);

        return lhs_int >= rhs_int;
    }

    using ProcessSubsystem = UInt32;
    using ProcessTime = UInt64;
    using PID = Int64;

    enum class ProcessSelector : Int
    {
        kRingUser,   /* user ring (or ring 3 in x86) */
        kRingDriver, /* ring 2 in x86, hypervisor privileges in other archs */
        kRingKernel, /* machine privileges */
    };

    using ImagePtr = VoidPtr;
    using PoolPtr = VoidPtr;

    class Process final
    {
    private:
        Char Name[kProcessLen];

    private:
        ProcessSubsystem SubSystem;
        ProcessSelector Selector;
        HAL::StackFrame* StackFrame;
        AffinityKind Affinity;
        ProcessStatus Status;

    private:
        ImagePtr Image;
        PoolPtr Pool;

    private:
        SizeT UsedMemory;
        SizeT FreeMemory;
        ProcessTime PTime;
        PID ProcessId;
        Int32 Ring;

    public:
        operator bool() { return Status != ProcessStatus::kDead; }

    public:
        void Crash();
        void Exit(Int32 exit_code = 0);
        const Char* GetName();

    public:
        void Wake(const bool should_wakeup = true);

    public:
        const ProcessSelector &GetSelector();
        const ProcessStatus &GetStatus();
        const AffinityKind &GetAffinity();

    private:
        friend class ProcessSignalManager;

        friend ProcessHelper;
        friend ProcessManager;

    };

    using ProcessPtr = Process*;

    class ProcessManager final
    {
    private:
        ProcessManager() = default;

    public:
        ~ProcessManager() = default;

        ME_COPY_DEFAULT(ProcessManager)

    public:
        operator bool() { return m_Headers.Count() > 0; }
        bool operator!() { return m_Headers.Count() == 0; }

    public:
        void Add(Ref<Process> &Header);
        bool Remove(SizeT Header);

    public:
        Ref<Process>& GetCurrent();
        SizeT StartScheduling();

    public:
        static Ref<ProcessManager> Shared();

    private:
        MutableArray<Ref<Process>> m_Headers;
        Ref<Process> m_CurrentProcess;

    };

    /*
     * Just a helper class, which contains some utilities for the scheduler.
     */

    class ProcessHelper final
    {
    public:
        static bool Switch(HAL::StackFrame* newStack, const PID& newPid);
        static bool CanBeScheduled(Ref<Process>& process);
        static PID& GetCurrentPID();
        static bool StartScheduling();

    };

    const Int32 &rt_get_exit_code() noexcept;
} // namespace MeKernel

#endif // ifndef _KERNELKIT_PROCESS_HPP
