/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <CFKit/Property.hpp>

namespace MeKernel
{
    bool Property::StringEquals(StringView &name)
    {
        return m_sName && this->m_sName == name;
    }

    const PropertyId& Property::GetPropertyById()
    {
        return m_Action;
    }
} // namespace MeKernel
