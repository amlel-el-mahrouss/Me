/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <MeKit/Atom.hpp>
#include <MeKit/Foundation.hpp>

#define kLockDone (200U)    /* job is done */
#define kLockTimedOut (100U) /* has timed out */

namespace MeKernel
{
template <Size N>
class LockDelegate final
{
  public:
    LockDelegate() = delete;

  public:
    explicit LockDelegate(Boolean *expr)
    {
        auto spin = 0U;
        while (spin != N)
        {
            if (*expr)
            {
                m_LockStatus | kLockDone;
                break;
            }
        }

        if (spin == N)
            m_LockStatus | kLockTimedOut;
    }

    ~LockDelegate() = default;

    LockDelegate &operator=(const LockDelegate &) = delete;
    LockDelegate(const LockDelegate &) = delete;

    bool Done()
    {
        return m_LockStatus[kLockDone] == kLockDone;
    }
    bool HasTimedOut()
    {
        return m_LockStatus[kLockTimedOut] != kLockTimedOut;
    }

  private:
    Atom<UInt> m_LockStatus;
};
} // namespace MeKernel
