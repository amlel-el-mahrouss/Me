/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <KernelKit/HardwareThread.hpp>
#include <KernelKit/ProcessManager.hpp>
#include <ArchKit/Arch.hpp>

namespace MeKernel
{
    extern void rt_wake_thread(HAL::StackFrame* stack);
    extern void rt_hang_thread(HAL::StackFrame* stack);

    HardwareThread::HardwareThread() = default;
    HardwareThread::~HardwareThread() = default;

    ThreadID HardwareThread::ID() noexcept { return m_ID; }
    ThreadKind HardwareThread::Kind() noexcept { return m_Kind; }

    bool HardwareThread::IsBusy() noexcept { return m_Busy; }

    HAL::StackFrame* HardwareThread::StackFrame() noexcept
    {
        MUST_PASS(m_Stack);
        return m_Stack;
    }

    void HardwareThread::Busy(bool busy) noexcept
    {
        m_Busy = busy;
    }

    HardwareThread::operator bool()
    {
        return m_Stack;
    }

    void HardwareThread::Wake(bool wakeup) noexcept
    {
        m_Wakeup = wakeup;

        if (!m_Wakeup)
            rt_hang_thread(m_Stack);
        else
            rt_wake_thread(m_Stack);
    }

    bool HardwareThread::Switch(HAL::StackFrame* stack)
    {
        if (stack == nullptr)
            return false;

        return rt_do_context_switch(m_Stack, stack) == 0;
    }

    bool HardwareThread::IsWokeup() noexcept { return m_Wakeup; }

    HardwareThreadManager::HardwareThreadManager() = default;
    HardwareThreadManager::~HardwareThreadManager() = default;

    Ref<HardwareThreadManager> HardwareThreadManager::Shared()
    {
        static HardwareThreadManager manager;
        return { manager };
    }

    HAL::StackFrame *HardwareThreadManager::GetStack()
    {
        if (m_ThreadList[m_CurrentThread].Leak() &&
            ProcessHelper::GetCurrentPID() == m_ThreadList[m_CurrentThread].Leak().Leak().m_PID)
            return m_ThreadList[m_CurrentThread].Leak().Leak().m_Stack;

        return nullptr;
    }

    bool HardwareThreadManager::Switch(HAL::StackFrame* stack)
    {
        if (!stack)
            return false;

        for (Size idx = 0; idx < kMaxHarts; ++idx)
        {
            if (m_ThreadList[idx].Leak().Leak().m_Stack != nullptr)
                continue;

            m_ThreadList[idx].Leak().Leak().m_Stack = stack;
            m_ThreadList[idx].Leak().Leak().m_ID = idx;
            m_ThreadList[idx].Leak().Leak().m_PID = ProcessHelper::GetCurrentPID();

            MUST_PASS(rt_get_current_context());

            return rt_do_context_switch(rt_get_current_context(), stack) == 0;
        }

        return false;
    }

    Ref<HardwareThread> HardwareThreadManager::operator[](const SizeT& idx)
    {
        if (!m_ThreadList[idx].Leak())
            return {};

        return m_ThreadList[idx].Leak();
    }

    HardwareThreadManager::operator bool() { return !m_ThreadList.Empty(); }

    bool HardwareThreadManager::operator!() { return m_ThreadList.Empty(); }
} // namespace MeKernel
