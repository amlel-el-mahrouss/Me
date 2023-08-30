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
#include <MeKit/Ref.hpp>

namespace MeKernel
{
using ErrorT = UInt;

template <typename T> class ErrorOr final
{
  public:
    ErrorOr() = default;
    ~ErrorOr() = default;

  public:
    explicit ErrorOr(Int32 err) : mId(err)
    {
    }
    explicit ErrorOr(nullPtr Null)
    {
    }
    explicit ErrorOr(T Class) : mRef(Class)
    {
    }

    ErrorOr &operator=(const ErrorOr &) = default;
    ErrorOr(const ErrorOr &) = default;

    ErrorOr &operator=(const Ref<T> &refErr)
    {
        mRef = refErr;
        return *this;
    }

    Ref<T> Leak()
    {
        return mRef;
    }
    operator bool()
    {
        return mRef;
    }

  private:
    Ref<T> mRef;
    Int32 mId{0};
};

using ErrorOrAny = ErrorOr<voidPtr>;

} // namespace MeKernel
