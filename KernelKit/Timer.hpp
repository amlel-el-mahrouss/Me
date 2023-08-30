/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <CompilerKit/Compiler.hpp>
#include <ArchKit/Arch.hpp>
#include <MeKit/ErrorID.hpp>

namespace MeKernel
{
    class ITimer;
    class HardwareTimer;


    class ITimer
    {
    public:
        ITimer() = default;
        virtual ~ITimer() = default;

    public:
        ME_COPY_DEFAULT(ITimer);

    public:
        virtual Int32 Wait() { return ME_UNIMPLEMENTED; }

    };

    class HardwareTimer final : public ITimer
    {
    public:
        explicit HardwareTimer(Int64 seconds);
        ~HardwareTimer() override;

    public:
        ME_COPY_DEFAULT(HardwareTimer);

    public:
        Int32 Wait() override { return ME_UNIMPLEMENTED; }

    };

    inline Int64 Seconds(Int64 time)
    {
        if (time < 0)
            return 0;

        return 1000 / time;
    }
}
