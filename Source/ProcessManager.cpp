/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <KernelKit/ProcessManager.hpp>
#include <KernelKit/HardwareThread.hpp>
#include <MeKit/Kalloc.hpp>
#include <MeKit/String.hpp>

///! bugs = 0

namespace MeKernel
{
    static Int32 kExitCode = 0;

    const Int32 &rt_get_exit_code() noexcept { return kExitCode; }

    void Process::Crash()
    {
        kcout << "MeKernel: " << this->Name << ": killed.";
        this->Exit(-1);
    }

    void Process::Wake(const bool should_wakeup)
    {
        this->Status = should_wakeup ? ProcessStatus::kStarting : ProcessStatus::kFrozen;
    }

    const Char* Process::GetName()
    {
        return this->Name;
    }

    const ProcessSelector& Process::GetSelector()
    {
        return this->Selector;
    }

    const ProcessStatus& Process::GetStatus()
    {
        return this->Status;
    }

    const AffinityKind& Process::GetAffinity()
    {
        return this->Affinity;
    }

    void Process::Exit(Int32 exit_code)
    {
        if (this->ProcessId != ProcessManager::Shared().Leak().GetCurrent().Leak().ProcessId)
            return;

        // check if we don't like escalate from another use process.
        if (this->Ring == (Int32)ProcessSelector::kRingKernel &&
            ProcessManager::Shared().Leak().GetCurrent().Leak().Ring > 0)
            return;

        kExitCode = exit_code;

        if (this->Ring != (Int32)ProcessSelector::kRingDriver &&
           this->Ring != (Int32)ProcessSelector::kRingKernel)
        {
            pool_free_ptr(this->Pool);

            this->FreeMemory = kPoolMaxSz;
            this->UsedMemory = 0UL;
        }

        /// delete image if not done already.
        if (this->Image)
            kernel_delete_ptr(this->Image);

        ProcessManager::Shared().Leak().Remove(this->ProcessId);
    }

    void ProcessManager::Add(Ref<Process> &process)
    {
        if (!process)
            return;

        kcout << "ProcessManager::Add(Ref<Process> &process)\r\n";

        process.Leak().Pool = pool_new_ptr(kPoolSize, kPoolUser | kPoolRw);

        process.Leak().ProcessId = this->m_Headers.Count();
        this->m_Headers.Add(process);
    }

    bool ProcessManager::Remove(SizeT process)
    {
        if (process > this->m_Headers.Count())
            return false;

        kcout << "ProcessManager::Remove(SizeT process)\r\n";

        return this->m_Headers.Remove(process);
    }

    SizeT ProcessManager::StartScheduling()
    {
        SizeT processIndex = 0; // we store this guy to tell the scheduler how many things we
        // have scheduled

        for (; processIndex < this->m_Headers.Count(); ++processIndex)
        {
            auto process = this->m_Headers[processIndex];
            MUST_PASS(process); // no need for a MUST_PASS(process.Leak());, it is recursive because of the nature of the class;

            // run any process needed to be scheduled.
            if (ProcessHelper::CanBeScheduled(process.Leak()))
            {
                auto unwrapped_process = *process.Leak();

                unwrapped_process.PTime = 0;

                // set the current process.
                m_CurrentProcess = unwrapped_process;

                ProcessHelper::Switch(m_CurrentProcess.Leak().StackFrame,
                                               m_CurrentProcess.Leak().ProcessId);
            }
            else
            {
                // otherwise increment the micro-time.
                ++m_CurrentProcess.Leak().PTime;
            }
        }

        return processIndex;
    }

    Ref<ProcessManager> ProcessManager::Shared()
    {
        static ProcessManager ref;
        return { ref };
    }

    Ref<Process>& ProcessManager::GetCurrent()
    {
        return m_CurrentProcess;
    }

    PID& ProcessHelper::GetCurrentPID()
    {
        kcout << "ProcessHelper::GetCurrentPID\r\n";
        return ProcessManager::Shared().Leak().GetCurrent().Leak().ProcessId;
    }

    bool ProcessHelper::CanBeScheduled(Ref<Process>& process)
    {
        if (process.Leak().Status == ProcessStatus::kFrozen ||
            process.Leak().Status == ProcessStatus::kDead)
            return false;

        if (process.Leak().GetStatus() == ProcessStatus::kStarting)
        {
            if (process.Leak().PTime < static_cast<Int>(kMinMicroTime))
            {
                process.Leak().Status = ProcessStatus::kRunning;
                process.Leak().Affinity = AffinityKind::kStandard;

                return true;
            }

            ++process.Leak().PTime;
        }

        return process.Leak().PTime > static_cast<Int>(kMinMicroTime);
    }

    bool ProcessHelper::StartScheduling()
    {
        if (ProcessHelper::CanBeScheduled(ProcessManager::Shared().Leak().GetCurrent()))
        {
            --ProcessManager::Shared().Leak().GetCurrent().Leak().PTime;
            return false;
        }



        auto process_ref = ProcessManager::Shared().Leak();

        if (!process_ref)
            return false; // we have nothing to schedule. simply return.

        SizeT ret = process_ref.StartScheduling();

        kcout << StringBuilder::FromInt("ProcessHelper::Start() iterated over: % processes\r\n", ret);

        return true;
    }

    bool ProcessHelper::Switch(HAL::StackFrame* the_stack, const PID& new_pid)
    {
        if (!the_stack ||
            new_pid < 0)
            return false;

        for (SizeT index = 0UL; index < kMaxHarts; ++index)
        {
            if (HardwareThreadManager::Shared().Leak()[index].Leak().StackFrame() == the_stack)
            {
                HardwareThreadManager::Shared().Leak()[index].Leak().Busy(false);
                continue;
            }


            if (HardwareThreadManager::Shared().Leak()[index].Leak().IsBusy())
                continue;

            if (HardwareThreadManager::Shared().Leak()[index].Leak().Kind() != ThreadKind::kBoot ||
               HardwareThreadManager::Shared().Leak()[index].Leak().Kind() != ThreadKind::kSystemReserved)
            {
                HardwareThreadManager::Shared().Leak()[index].Leak().Busy(true);
                ProcessHelper::GetCurrentPID() = new_pid;

                return HardwareThreadManager::Shared().Leak()[index].Leak().Switch(the_stack);
            }
        }

        return false;
    }
} // namespace MeKernel
