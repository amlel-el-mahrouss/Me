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

extern "C" [[noreturn]] void abort()
{
    while (true)
    {
        MeKernel::HAL::rt_cli();
        MeKernel::HAL::rt_halt();
    }
}

/* Each error code is attributed with an ID, which will prompt a string onto the
 * screen. */
namespace MeKernel
{
    void panic(const MeKernel::Int& id)
    {
#ifdef __DEBUG__
        kcout << "Me: Kernel Panic! \r\n";
        kcout << StringBuilder::FromInt("kError : % \n", id);

        DumpManager::Dump();
#endif // __DEBUG__

        abort();
    }

    void runtime_check(bool expr, const char *file, const char *line)
    {
        if (!expr)
        {
#ifdef __DEBUG__
            kcout << "[KERNEL] Check Failed!\n";
            kcout << "[KERNEL] File: " << file << "\n";
            kcout << "[KERNEL] Where: " << line << "\n";

            MeKernel::panic(RUNTIME_CHECK_FAILED); // Runtime Check failed
#endif // __DEBUG__
        }
    }
} // namespace MeKernel
