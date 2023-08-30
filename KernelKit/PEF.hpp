/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _INC_LOADER_PEF_HPP
#define _INC_LOADER_PEF_HPP

#include <MeKit/Foundation.hpp>
#include <KernelKit/Loader.hpp>
#include <CompilerKit/Compiler.hpp>

#define kPefMagic "PEF"
#define kPefMagicLen 3

#define kPefNameLen 64

// Protable Executable Format, a format designed for any computer.

namespace MeKernel
{
    enum PEF_CPU
    {
        kPefArchPower, /* PowerPC 64 */
        kPefArchIntel86S,
        kPefArchAMD64,
        kPefArchARM64,
        kPefArchInvalid,
    };

    enum PEF_KIND
    {
        kPefKindExec = 1, /* <none> */
        kPefKindSharedObject = 2, /* .so */
        kPefKindObject = 4, /* .o */
        kPefKindDwarf = 5, /* .o */
    };

    /* PEF container */
    typedef struct PEFContainer
    {
        Char Magic[kPefMagicLen];
        UInt32 Version;
        UInt32 Kind;
        UInt32 Cpu;
        UInt32 SubCpu; /* Cpu specific information */
        SizeT HdrSz; /* Size of header */
        SizeT Count; /* container header count */
    } PEFContainer;

    /* First PEFContainerHeader starts after PEFContainer */
    /* Last container is .end */

    /* PEF executable section */

    typedef struct PEFContainerHeader
    {
        Char Name[kPefNameLen]; /* it's name */
        UInt32 Flags; /* it's flags */
        UInt16 Kind; /* it's kind */
        UIntPtr Off; /* code file offset */
        SizeT Size; /* code Size */
    } PEFContainerHeader;

    enum PEF_OBJ_KIND
    {
        kPefCode = 0xC,
        kPefData = 0xD,
        kPefZero = 0xE,
    };
}

#endif /* ifndef _INC_LOADER_PEF_HPP */
