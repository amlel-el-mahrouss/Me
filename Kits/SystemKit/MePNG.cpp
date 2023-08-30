/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <SystemKit/MePNG.hpp>
#include <MeKit/ErrorID.hpp>
#include <MeKit/Utils.hpp>
#include <MeKit/Ref.hpp>

static const char* png_error_to_str(const int err);

enum
{
    kPngErrAdler,
    kPngErrCrc,
    kPngErrCompr,
    kPngUnknown,
};

typedef void* PNGImage;

static const char* png_error_to_str(const int err)
{
    switch (err)
    {
        case kPngErrAdler:
            return "Png: Bad adler32.";
        case kPngErrCompr:
            return "Png: Bad compression.";
        case kPngErrCrc:
            return "Png: Bad CRC32.";
        case kPngUnknown:
        default:
            return "Png: Error while loading image.";
    }

    return "Png: Unknown error.";
}

class PngHeader
{
public:
    UInt8 Mag1;
    Char* Mag2;
    UInt16 DosDetect;
    UInt16 DosEOF;
    UInt16 UnixLF;

};

#define kIHDRMag "IHDR"
#define kIDATMag "IDAT"
#define kIENDMag "IEND"

static MeFilePtr png_open_file(const char* path)
{
    MeFilePtr thePng = new MeFile(path);

    thePng->SetMIME("image/png");
    thePng->Rewind();

    return thePng;
}

static MeKernel::Ref<PngHeader> png_read_header(MeFilePtr thePng)
{
    if (thePng)
    {
        MeKernel::Ref<PngHeader> header;

        header.Leak().Mag1 = *(UInt8*)thePng->Read(sizeof(UInt8));

        MeKernel::copy_memory((MeKernel::voidPtr)header.Leak().Mag2,
                              (MeKernel::voidPtr)thePng->Read(MeKernel::string_length("PNG")),
                                                              MeKernel::string_length("PNG"));

        header.Leak().DosDetect = *(UInt16*)thePng->Read(sizeof(UInt16));
        header.Leak().DosEOF = *(UInt16*)thePng->Read(sizeof(UInt16));
        header.Leak().UnixLF = *(UInt16*)thePng->Read(sizeof(UInt16));

        return header;
    }

    return MeKernel::Ref<PngHeader>{ };
}
