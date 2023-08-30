/*
 *	========================================================
 *
 *	MeBoot
 * 	Copyright Amlal El Mahrouss., all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <BootKit/Defines.hpp>

typedef void* XCOFFImage;
typedef void* PEFImage;

class BootTextWriter final
{
    volatile UInt16* fWhere;

public:
    void WriteString(const char* c,
                     unsigned char forecolour,
                     unsigned char backcolour,
                     int x,
                     int y);

    void WriteCharacter(char c,
                        unsigned char forecolour,
                        unsigned char backcolour,
                        int x,
                        int y);

public:
    BootTextWriter() = default;
    ~BootTextWriter() = default;

public:
    BootTextWriter& operator=(const BootTextWriter&) = default;
    BootTextWriter(const BootTextWriter&) = default;

};

enum
{
    kBlack,
    kBlue,
    kGreen,
    kCyan,
    kRed,
    kMagenta,
    kBrown,
    kLightGray,
    kDarkGray,
    kLightBlue,
    kLightGreen,
    kLightCyan,
    kLightRed,
    kLightMagenta,
    kYellow,
    kWhite,
};
