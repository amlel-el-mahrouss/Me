/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <SystemKit/Defines.hpp>
#include <CompilerKit/Compiler.hpp>

class MeMemoryException;

typedef void* MeHeapPtr;

class MeHeap final
{
private:
    MeHeap();

public:
    ~MeHeap();

public:
    ME_COPY_DEFAULT(MeHeap);

public:
    static MeHeap* Shared() noexcept;

public:
    void Dispose(MeHeapPtr me) noexcept;
    MeHeapPtr New(SizeT sz);

};
