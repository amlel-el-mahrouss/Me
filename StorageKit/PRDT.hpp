/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */
#pragma once

#include <KernelKit/PCI/Dma.hpp>
#include <KernelKit/PCI/Iterator.hpp>

#define PRDT_TRANSFER_SIZE (sizeof(MeKernel::UShort))

namespace MeKernel
{
    class PRDT final
    {
    public:
        PRDT() = delete;
        PRDT(const UIntPtr &physAddr);
        ~PRDT();

        PRDT &operator=(const PRDT &) = default;
        PRDT(const PRDT &) = default;

    public:
        const UInt &Low();
        const UShort &High();
        const UIntPtr &PhysicalAddress();

    public:
        PRDT &operator=(const UIntPtr& prdtAddress);

    public:
        operator bool()
        {
            return m_PrdtAddr != 0;
        }

    private:
        union
        {
            UInt m_Low;
            UShort m_High;
        };

        UIntPtr m_PrdtAddr;

    };

    using PhysicalAddress = PRDT; // here
} // namespace MeKernel
