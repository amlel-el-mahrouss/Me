/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <CompilerKit/Compiler.hpp>
#include <MeKit/Foundation.hpp>
#include <MeKit/String.hpp>

#define kDriveInvalidID -1
#define kDriveNameLen 32

namespace MeKernel
{
    struct Drive;

    enum
    {
        fMassStorage = 1,
        fFloppy,
        fOpticalDisc,
        fReadOnly,
        fXPMDrive,
        fXPTDrive,
    };

    typedef Int64 DriveID;

    // Mounted drive.
    struct Drive
    {
        char fName[kDriveNameLen]; // /system, /boot...
        Int32 fKind; // fMassStorage, fFloppy, fOpticalDisc.
        DriveID fId; // Drive id.
        Int32 fFlags; // fReadOnly, fXPMDrive, fXPTDrive
    };
}
