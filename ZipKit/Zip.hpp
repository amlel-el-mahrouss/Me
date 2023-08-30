/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <ZipKit/zlib.hpp>
#include <CompilerKit/Compiler.hpp>

// TODO: integrate MeFS compression.

// MeFS catalog is compressed.
#define kCatalogFlagZip 255
// MeFS catalog has password.
#define kCatalogPassword 256

namespace ZipKit
{
    class DeflateWrapper;
    class InflateWrapper;

    class ZipStream;

    class ZipStream final
    {
    public:
        ZipStream() = default;

        ~ZipStream() noexcept
        {
            if (fDeflate)
                delete fDeflate;

            if (fInflate)
                delete fInflate;
        }

    public:
        ME_COPY_DEFAULT(ZipStream);

    public:
        void* Deflate(const char* name);
        void Inflate(const char* name, void* data);

    private:
        InflateWrapper* fInflate;
        DeflateWrapper* fDeflate;

    };
}
