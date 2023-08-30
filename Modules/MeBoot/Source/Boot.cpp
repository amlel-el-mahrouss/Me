/*
 *	========================================================
 *
 *	MeBoot
 * 	Copyright Amlal El Mahrouss., all rights reserved.
 *
 * 	========================================================
 */

#include <BootKit/Boot.hpp>

void BootTextWriter::WriteString(const char* str,
                 unsigned char forecolour,
                 unsigned char backcolour,
                 int x,
                 int y)
{
    if (*str == 0 ||
        !str)
        return;

    for (SizeT idx = 0; idx < __builtin_strlen(str); ++idx)
    {
        this->WriteCharacter(str[idx], forecolour, backcolour, x, y);
        ++x;
    }
}

#ifdef __x86_64__

void BootTextWriter::WriteCharacter(char c,
                    unsigned char forecolour,
                    unsigned char backcolour,
                    int x,
                    int y)
{
     UInt16 attrib = (backcolour << 4) | (forecolour & 0x0F);

     fWhere = (volatile UInt16*)0xB8000 + (y * 80 + x);
     *fWhere = c | (attrib << 8);
}

#endif
