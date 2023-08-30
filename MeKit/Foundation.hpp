/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <MeKit/Macros.hpp>

#ifndef _INC_NO_STDC_HEADERS
#   include <stddef.h>
#   include <stdint.h>
#endif

#ifdef __has_feature
#if !__has_feature(cxx_nullptr)
#   error You must at least have nullptr featured in your C++ compiler.
#endif
#endif

namespace MeKernel
{
    using voidPtr = void *;
    using VoidPtr = void *;
    using nullPtr = decltype(nullptr);
    using NullPtr = decltype(nullptr);

    using Int = int;
    using Int32 = int;
    using UShort = unsigned short;
    using UInt16 = unsigned short;
    using Short = short;
    using Int16 = short;
    using UInt = unsigned int;
    using UInt32 = unsigned int;
    using Long = long int;
    using Int64 = long int;
    using ULong = unsigned long int;
    using UInt64 = unsigned long int;
    using Boolean = bool;
    using Bool = bool;
    using Char = char;
    using UChar = unsigned char;
    using UInt8 = unsigned char;

    using SSize = Int64;
    using SSizeT = Int64;
    using Size = __SIZE_TYPE__;
    using SizeT = __SIZE_TYPE__;
    using IntPtr = __INTPTR_TYPE__;
    using UIntPtr = __UINTPTR_TYPE__;
    using IntFast = __INT_FAST32_TYPE__;
    using IntFast64 = __INT_FAST64_TYPE__;
    using PtrDiff = __PTRDIFF_TYPE__;

    using Utf8Char = char8_t;
    using Utf16Char = char16_t;
    using Utf32Char = char32_t;

    using Lba = SSizeT;

    enum class Endian : UChar
    {
        kLittle,
        kBig
    };

    template <typename Args> Args &&forward(Args &arg)
    {
        return static_cast<Args &&>(arg);
    }

    template <typename Args> Args &&move(Args &&arg)
    {
        return static_cast<Args &&>(arg);
    }
} // namespace MeKernel

#define DEDUCE_ENDIAN(address, value)                                                                                  \
    (((reinterpret_cast<MeKernel::Char*>(address)[0]) == (value)) ? (MeKernel::Endian::kBig)                      \
                                                                    : (MeKernel::Endian::kLittle))

#define Yes (true)
#define No (false)
