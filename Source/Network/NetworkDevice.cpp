/*
 *	========================================================
 *
 *	MeKit
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <NetworkKit/NetworkDevice.hpp>

// network devices implementation.
// PPPNetworkService, TCPNetworkDevice, UDPNetworkService

namespace MeKernel
{
    NetworkDevice::NetworkDevice(void (*out)(NetworkDeviceCommand), void (*in)(NetworkDeviceCommand), void(*on_cleanup)(void))
            : IDevice<NetworkDeviceCommand>(out, in), fCleanup(on_cleanup)
    {
#ifdef __DEBUG__
        kcout << "New NetworkDevice allocated";
#endif
    }

    NetworkDevice::~NetworkDevice()
    {
        if (fCleanup)
            fCleanup();
    }
} // namespace MeKit
