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

namespace MeKernel
{
    class NVMEPacket;

    class NVMEDevice : public IDevice<NVMEPacket>
    {
    public:
        NVMEDevice(void(*Out)(NVMEPacket outpacket),
                   void(*In)(NVMEPacket inpacket),
                   void(*Cleanup)(void))
            : IDevice(Out, In), fCleanup(Cleanup)
        {}

        virtual ~NVMEDevice()
        {
            if (fCleanup)
                fCleanup();
        }

    public:
        NVMEDevice &operator=(const NVMEDevice &) = default;
        NVMEDevice(const NVMEDevice &) = default;

        virtual const char *Name() const;

    public:
        OwnPtr<NVMEPacket> operator()(UInt32 dmaLow, UInt32 dmaHigh, SizeT sz);

    private:
        void(*fCleanup)(void);


    };
} // namespace MeKernel
