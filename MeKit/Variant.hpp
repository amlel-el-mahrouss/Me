/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <MeKit/Foundation.hpp>
#include <MeKit/String.hpp>

namespace MeKernel
{
    class Variant final
    {
    public:
        enum class VariantKind
        {
            kString,
            kPointer,
            kUndefined
        };

    public:
        Variant() = delete;

    public:
        Variant &operator=(const Variant &) = default;
        Variant(const Variant &) = default;

        ~Variant() = default;

    public:
        explicit Variant(StringView* stringView) : m_Ptr((voidPtr)stringView), m_Kind(VariantKind::kString) {}
        explicit Variant(nullPtr) : m_Ptr(nullptr), m_Kind(VariantKind::kUndefined) {}
        explicit  Variant(voidPtr ptr) : m_Ptr(ptr), m_Kind(VariantKind::kPointer) {}

    public:
        const Char* ToString();

    private:
        voidPtr m_Ptr{nullptr};
        VariantKind m_Kind{VariantKind::kUndefined};

    };
} // namespace MeKernel
