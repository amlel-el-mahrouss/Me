
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

namespace MeKernel
{
    Int copy_memory(const voidPtr src, voidPtr dst, Size len);
    Int move_memory(const voidPtr src, voidPtr dst, Size len);
    voidPtr set_memory(voidPtr dst, Char val, Size len);
    void zero_memory(voidPtr pointer, Size len);
    Int string_cmp(const Char *src, const Char *cmp, Size len);
    const Char *alloc_string(const Char *text);
    Size string_length(const Char *str);
    Size string_length(const Char *str, SizeT _len);
    Boolean to_str(Char *buf, Int limit, Int base);
    Boolean is_newln(Char chr);
    Boolean is_space(Char chr);
    Int to_uppercase(Int c);
    Int to_lower(Int c);
    voidPtr string_in_string(const char* in, const char* needle);
} // namespace MeKernel
