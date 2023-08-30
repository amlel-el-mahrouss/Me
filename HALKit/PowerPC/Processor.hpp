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
#include <MeKit/Utils.hpp>

#define __aligned __attribute__((aligned(4)))

namespace MeKernel::HAL
{
    typedef UIntPtr Reg;

    struct __aligned StackFrame
    {
        Reg R0;
        Reg R1;
        Reg R2;
        Reg R3;
        Reg R4;
        Reg R5;
        Reg R6;
        Reg R7;
        Reg ID; // R8
    };
}

extern "C" void int_handle_math(MeKernel::UIntPtr sp);
extern "C" void int_handle_pf(MeKernel::UIntPtr sp);
