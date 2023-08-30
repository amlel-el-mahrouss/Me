/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <KernelKit/MountManager.hpp>
#include <CompilerKit/Compiler.hpp>
#include <MeKit/Foundation.hpp>

#define kInvalidFork -1
#define kInvalidCatalog -1
#define kNameLen 256

#define kIdentLen 5
#define kIdent "MeFS"
#define kPadLen 16

#define kFilesystemVersion 1

enum
{
    kHardDrive = 0xC0,
    kOpticalDrive = 0x0C,
};

struct MeBootBlock
{
    MeKernel::Char Ident[kIdentLen];

    MeKernel::Int64 NumParts;
    MeKernel::Int64 FreeSectors;
    MeKernel::Int64 SectorCount;
    MeKernel::Int64 SectorSz;

    MeKernel::Int64 DiskSize;
    MeKernel::Int32 DiskKind;

    MeKernel::Lba FirstSuperBlock;
    MeKernel::Lba LastSuperBlock;

    MeKernel::Char Pad[kPadLen];
};

struct MeCatalog
{
    MeKernel::Char Name[kNameLen];

    MeKernel::Int32 Flags;
    MeKernel::Int32 Kind;

    MeKernel::Lba FirstFork;
    MeKernel::Lba LastFork;
};

struct MeFork
{
    MeKernel::Int32 Flags;
    MeKernel::Int32 Kind;

    MeKernel::Int64 ID;

    MeKernel::Int64 ResourceId;
    MeKernel::Int32 ResourceKind;
    MeKernel::Int32 ResourceFlags;

    MeKernel::Lba Offset;
    MeKernel::Lba NextFork;
};

#define kResourceTypeDialog 10
#define kResourceTypeString 11
#define kResourceTypeMenu   12

#define kConfigLen 64
#define kPartLen 32

struct MePartitionBlock
{
    MeKernel::Char PartitionName[kPartLen];
    MeKernel::Char ConfigPath[kConfigLen];

    MeKernel::Int32 Flags;
    MeKernel::Int32 Kind;

    MeKernel::Lba StartCatalog;
    MeKernel::SizeT CatalogCount;

    MeKernel::SizeT DiskSize;

    MeKernel::SizeT FreeCatalog;
    MeKernel::SizeT FreeSectors;

    MeKernel::SizeT SectorCount;
    MeKernel::SizeT SectorSize;

    MeKernel::Char Pad[kPadLen];
};

#define kCatalogKindFile 1
#define kCatalogKindDir 2
#define kCatalogKindAlias 3

// shared between network/other filesystems. Export forks as .zip when copying.
#define kCatalogKindShared 4
#define kCatalogKindResource 5
#define kCatalogKindExecutable 6
#define kCatalogKindPage 8

#define kFilesystemSeparator '/'

#define kFilesystemUpDir ".."
#define kFilesystemRoot "/"

#define kFilesystemLE '\r'
#define kFilesystemEOF 0xFFFF

#define kFilesystemBitWidth sizeof(UInt16)
#define kFilesystemLbaType MeKernel::Lba

namespace MeKernel
{
    ///
    /// \name MeFSImpl
    /// MeFS filesystem operations. (catalog creation, remove removal, root fork...)
    ///

    class MeFSImpl final
    {
    public:
        MeFSImpl() = default;
        ~MeFSImpl() = default;

    public:
        ME_COPY_DEFAULT(MeFSImpl);

    public:
        MeFork GetForkFromCatalog(MeCatalog& catalog, const MeKernel::Int64& ID);
        MeCatalog GetCatalog(const char* name);

    public:
        void CreateCatalog(MeCatalog& catalog, const char* name, MeKernel::Int32 flags, MeKernel::Int32 kind);
        void CreateCatalog(MeCatalog& catalog, const char* name);
        bool RemoveCatalog(MeCatalog& catalog);
        bool WriteCatalog(MeCatalog& catalog);

    public:
        Drive& MountDrive(DriveID drive);
        void UnmountDrive(Drive& drive);
        void FormatDrive(Drive& drive);

    };

    ///
    /// \name MeFilesystemHelper
    ///
    /// Filesystem helper.
    ///

    class MeFilesystemHelper final
    {
    public:
        static const char* Root() { return kFilesystemRoot; }
        static const char* UpDir() { return kFilesystemUpDir; }
        static const char Separator() { return kFilesystemSeparator; }

    };

    void rt_write_mefs_part_block(DriveID drive_id);
    void rt_write_mefs_boot_block(DriveID drive_id);
}
