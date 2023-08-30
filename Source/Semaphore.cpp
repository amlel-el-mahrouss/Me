/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <KernelKit/Semaphore.hpp>
#include <KernelKit/Timer.hpp>

namespace MeKernel
{
    bool Semaphore::Unlock() noexcept
    {
        if (fLockingProcess)
            fLockingProcess = nullptr;

        return !fLockingProcess;
    }

    bool Semaphore::Lock(ProcessPtr process)
    {
        if (!process ||
            fLockingProcess)
            return false;

        fLockingProcess = process;

        return true;
    }

    bool Semaphore::IsLocked() const { return fLockingProcess; }

    bool Semaphore::LockOrWait(ProcessPtr process, const Int64& seconds)
    {
        if (process == nullptr)
            return false;

        HardwareTimer timer(Seconds(seconds));
        timer.Wait();

        return this->Lock(process);
    }

    void Semaphore::Sync() noexcept
    {
        while (fLockingProcess)
            ;
    }
}
