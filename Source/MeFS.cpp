/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <FSKit/MeFS.hpp>
#include <MeKit/Utils.hpp>
#include <KernelKit/Out.hpp>
#include <StorageKit/Storage.hpp>
#include <KernelKit/FileManager.hpp>

#define kDefaultPartName "Untitled"
#define kDefaultConfigPath "/boot/Demarrer.ini"

namespace MeKernel
{
    ///! From the StorageKit API.
    extern Lba rt_drive_start_lba(DriveID drive_id);
    extern SizeT rt_drive_size(DriveID drive_id);
    extern Lba rt_drive_end_lba(DriveID drive_id);
    extern Int32 rt_drive_kind(DriveID drive_id);

    extern bool rt_write_to_disk(DriveID drive_id, voidPtr address, SizeT sz, Lba lba);
    extern bool rt_read_from_disk(DriveID drive_id, voidPtr address, SizeT sz, Lba lba);

    void rt_write_mefs_boot_block(DriveID drive_id)
    {
        if (drive_id == -1)
        {
            kcout << "Not a drive! aborting...";
            return;
        }

        auto start = rt_drive_start_lba(drive_id);
        auto sz = rt_drive_size(drive_id);

        MeBootBlock boot_block;
        set_memory(&boot_block, 0, sizeof(MeBootBlock));

        boot_block.FreeSectors = boot_block.SectorCount = sz % kSectorSz;
        boot_block.DiskKind = rt_drive_kind(drive_id);
        boot_block.NumParts = 1;
        boot_block.DiskSize = sz;

        boot_block.FirstSuperBlock = start + sizeof(MeBootBlock);
        boot_block.LastSuperBlock = boot_block.FirstSuperBlock;

        copy_memory((voidPtr)kIdent, (voidPtr)boot_block.Ident, kIdentLen);
        copy_memory((voidPtr)"\0\0\0\0\0\0\0\0\0\0\0\0\0", (voidPtr)boot_block.Pad, kPadLen);

        rt_write_to_disk(drive_id, &boot_block, sizeof(MeBootBlock), rt_drive_start_lba(drive_id));
    }

    void rt_write_mefs_part_block(DriveID drive_id)
    {
        if (drive_id == -1)
        {
            kcout << "Not a drive! aborting...";
            return;
        }

        auto sz = rt_drive_size(drive_id);

        MePartitionBlock part_block;
        set_memory(&part_block, 0, sizeof(MePartitionBlock));

        part_block.FreeSectors = part_block.SectorCount = sz % kSectorSz;
        part_block.DiskSize = sz;
        part_block.FreeCatalog = part_block.FreeSectors;
        part_block.StartCatalog = kSectorSz;

        copy_memory((voidPtr)part_block.PartitionName, (voidPtr)kDefaultPartName, string_length(kDefaultPartName));
        copy_memory((voidPtr)part_block.ConfigPath, (voidPtr)kDefaultConfigPath, string_length(kDefaultConfigPath));

        ///! this will take care of allocating forks.
        rt_write_to_disk(drive_id, &part_block, sizeof(MePartitionBlock), rt_drive_start_lba(drive_id) + sizeof(MeBootBlock));
    }
}
