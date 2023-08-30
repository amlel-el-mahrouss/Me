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
#include <CompilerKit/Compiler.hpp>
#include <KernelKit/ProcessManager.hpp>

namespace MeKernel
{
    class Semaphore final
    {
    public:
        Semaphore() = default;
        ~Semaphore() = default;

    public:
        bool IsLocked() const;
        bool Unlock() noexcept;

    public:
        void Sync() noexcept;

    public:
        bool Lock(ProcessPtr process);
        bool LockOrWait(ProcessPtr process, const Int64& seconds);

    public:
        ME_COPY_DEFAULT(Semaphore);

    private:
        Process* fLockingProcess{ nullptr };

    };
}
