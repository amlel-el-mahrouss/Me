/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <MeKit/ErrorOr.hpp>
#include <MeKit/Foundation.hpp>
#include <CompilerKit/Compiler.hpp>

namespace MeKernel
{
    class Loader
    {
    public:
        Loader() = default;
        virtual ~Loader() = default;

        ME_COPY_DEFAULT(Loader);

    public:
        virtual const char* Format() = 0;
        virtual const char* MIME() = 0;

        virtual ErrorOr<VoidPtr> LoadStart() = 0;

    };
}
