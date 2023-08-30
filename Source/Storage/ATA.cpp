/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <StorageKit/ATA.hpp>
#include <ArchKit/Arch.hpp>

namespace MeKernel
{
    Ref<PRDT*> kPrdt = nullptr;
    Ref<IOArray16*> kBmr = nullptr;

    bool set_prdt_struct(Ref<PRDT*>& refCtrl)
    {
        if (!kPrdt)
        {
            kPrdt = refCtrl;
            kcout << "[set_prdt_struct] PRDT is set now.";

            return true;
        }

        kcout << "[set_prdt_struct] [WARNING] Tried to change PRDT's value..\n";
        return false;
    }

    bool set_io_array(Ref<IOArray16*>& bmr)
    {
        if (!kBmr)
        {
            kBmr = bmr;
            kcout << "[set_io_array] IOArray is set now.";
            return true;
        }

        kcout << "[set_io_array] [WARNING] Tried to change IOArray's value..\n";
        return false;
    }


    enum
    {
        k28BitRead = 0xC8,
        k48BitRead = 0x25,
        k28BitWrite = 0xCA,
        k48BitWrite = 0x35,
    };

#define kATAError 2

    const char* ata_read_28(ULong lba)
    {
        static char buffer[512];

        UIntPtr* packet = (UIntPtr*)kPrdt.Leak()->PhysicalAddress();

        packet[0] = k28BitRead;
        packet[2] = (UIntPtr)&buffer;

        rt_wait_for_io();

        return buffer;
    }

    const char *ata_read_48(ULong lba)
    {
        static char buffer[512];

         UIntPtr* packet = (UIntPtr*)kPrdt.Leak()->PhysicalAddress();

         packet[0] = k48BitRead;
         packet[2] = (UIntPtr)&buffer;

         rt_wait_for_io();

         return buffer;
    }

    Int32 ata_write_48(ULong lba, const char *text)
    {
         UIntPtr* packet = (UIntPtr*)kPrdt.Leak()->PhysicalAddress();

         packet[0] = k48BitWrite;
         packet[2] = (UIntPtr)&text;

         rt_wait_for_io();

         return packet[1] == 2 ? kATAError : 0;
    }

    Int32 ata_write_28(ULong lba, const char *text)
    {
        UIntPtr* packet = (UIntPtr*)kPrdt.Leak()->PhysicalAddress();

        packet[0] = k28BitWrite;
        packet[2] = (UIntPtr)&text;

        rt_wait_for_io();

        return packet[1] == 2 ? kATAError : 0;
    }
} // namespace MeKernel
