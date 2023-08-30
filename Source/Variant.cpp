/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <MeKit/Variant.hpp>

namespace MeKernel
{
    const Char *Variant::ToString()
    {
        if (!m_Ptr)
        {
            return ("{Nullptr}");
        };

        switch (m_Kind)
        {
            case VariantKind::kString:
                return ("Class:{String}");
            case VariantKind::kPointer:
                return ("Memory:{Pointer}");
            default:
                return ("Unknown:{Undefined}");
        }
    }

} // namespace MeKernel
