/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <HALKit/AMD64/ACPI/ACPIManager.hpp>
#include <MeKit/String.hpp>

namespace MeKernel
{
    ACPIManager::ACPIManager(voidPtr rsdPtr)
        : m_Rsdp(rsdPtr), m_Entries(0)
    {
        RSDP* _rsdPtr = reinterpret_cast<RSDP*>(this->m_Rsdp);

        MUST_PASS(_rsdPtr);
        MUST_PASS(_rsdPtr->Revision >= 2);
    }

    void ACPIManager::Shutdown() {}
    void ACPIManager::Reset() {}

    ErrorOr <voidPtr> ACPIManager::Find(const char *signature)
    {
        MUST_PASS(m_Rsdp);

        if (!signature)
            return ErrorOr<voidPtr>{-2};

        if (*signature == 0)
            return ErrorOr<voidPtr>{-3};

        RSDP *rsdPtr = reinterpret_cast<RSDP*>(this->m_Rsdp);

        auto xsdt = rsdPtr->XsdtAddress;
        SizeT num = (rsdPtr->Length + sizeof(SDT)) / 8;

        for (Size index = 0; index < num; ++index)
        {
            SDT *sdt = reinterpret_cast<SDT*>(xsdt + sizeof(SDT) + index * 8);

            if (!Checksum(sdt->Signature, 4))
                panic(RUNTIME_CHECK_ACPI);

            if (StringBuilder::Equals(const_cast<const char*>(sdt->Signature), signature))
                return ErrorOr<voidPtr>(reinterpret_cast<voidPtr>(sdt));
        }

        return ErrorOr<voidPtr>{-1};
    }

    bool ACPIManager::Checksum(const char *checksum, SSizeT len)
    {
        if (len == 0)
            return -1;

        char chr = 0;

        for (int index = 0; index < len; ++index)
        {
            chr += checksum[index];
        }

        return chr == 0;
    }
} // namespace MeKernel
