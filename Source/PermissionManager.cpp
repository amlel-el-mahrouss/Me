/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <KernelKit/PermissionManager.hpp>

namespace MeKernel
{
    PermissionSelector::PermissionSelector(const Int32& sel)
        : fRing((RingKind)sel)
    {}

    PermissionSelector::PermissionSelector(const RingKind& ringKind)
        : fRing(ringKind)
    {}

    PermissionSelector::~PermissionSelector() = default;

    bool PermissionSelector::operator==(const PermissionSelector& lhs)
    {
        return lhs.fRing == this->fRing;
    }

    bool PermissionSelector::operator!=(const PermissionSelector& lhs)
    {
        return lhs.fRing != this->fRing;
    }

    RingKind PermissionSelector::Ring() const { return this->fRing; }
}
