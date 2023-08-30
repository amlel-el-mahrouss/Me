/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _INC_PERMISSION_MANAGER_HPP
#define _INC_PERMISSION_MANAGER_HPP

#include <KernelKit/ProcessManager.hpp>
#include <CompilerKit/Compiler.hpp>
#include <MeKit/Foundation.hpp>

namespace MeKernel
{
    enum class RingKind
    {
        kRingUser = 3,
        kRingDriver = 2,
        kRingKernel = 0,
        kUnknown = -1,
    };

    class PermissionSelector final
    {
    private:
        explicit PermissionSelector(const Int32& sel);
        explicit PermissionSelector(const RingKind& kind);

        ~PermissionSelector();

    public:
        ME_COPY_DEFAULT(PermissionSelector)

    public:
        bool operator==(const PermissionSelector& lhs);
        bool operator!=(const PermissionSelector& lhs);

    public:
        RingKind Ring() const;

    private:
        RingKind fRing;

    };
}

#endif /* ifndef _INC_PERMISSION_MANAGER_HPP */
