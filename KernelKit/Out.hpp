/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <KernelKit/DeviceManager.hpp>
#include <MeKit/OwnPtr.hpp>
#include <MeKit/Stream.hpp>

namespace MeKernel
{
    class TerminalDevice final : public IDevice<const char*>
    {
    public:
        TerminalDevice(void (*print)(const char *), void (*get)(const char *)) : IDevice<const char*>(print, get) {}
        virtual ~TerminalDevice() {}

        virtual const char *Name() const override { return ("TerminalDevice"); }

        TerminalDevice &operator=(const TerminalDevice &) = default;
        TerminalDevice(const TerminalDevice &) = default;

    };

    namespace Details
    {
        bool serial_init();
    }

    extern TerminalDevice kcout;
} // namespace MeKernel
