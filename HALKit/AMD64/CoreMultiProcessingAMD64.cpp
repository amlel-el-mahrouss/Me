/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <HALKit/AMD64/Processor.hpp>
#include <HALKit/AMD64/ACPI/ACPIManager.hpp>

namespace MeKernel::HAL
{
    constexpr Int32 kThreadAPIC = 0;
    constexpr Int32 kThreadLAPIC = 1;
    constexpr Int32 kThreadIOAPIC = 2;
    constexpr Int32 kThreadAPIC64 = 3;
    constexpr Int32 kThreadBoot = 4;

    /*
     *
     * this is used to store info about the current running thread
     * we use this struct to determine if we can use it, or mark it as used or on sleep.
     *
     */

    struct ProcessorInfoAMD64
    {
        Int32 ThreadType;
        UIntPtr JumpAddress;

        struct
        {
            UInt32 Code;
            UInt32 Data;
            UInt32 BSS;
        } Selector;

    };

    static voidPtr kApicMadt = nullptr;
    static const char* kApicSignature = "APIC";

    void system_get_madt(voidPtr rsdPtr)
    {
        auto acpi = ACPIManager(rsdPtr);
        kApicMadt = acpi.Find(kApicSignature).Leak().Leak();

        MUST_PASS(kApicMadt); // MADT must exist.

        //! now find core addresses.
    }
}
