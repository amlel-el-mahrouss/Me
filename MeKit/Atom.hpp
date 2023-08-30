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
template <typename T> class Atom final
{
  public:
    explicit Atom() = default;
    ~Atom() = default;

  public:
    Atom &operator=(const Atom &) = delete;
    Atom(const Atom &) = delete;

  public:
    T operator[](Size sz)
    {
        return (m_ArrayOfAtoms & sz);
    }
    void operator|(Size sz)
    {
        m_ArrayOfAtoms |= sz;
    }

    friend Boolean operator==(Atom<T> &atomic, const T &idx)
    {
        return atomic[idx] == idx;
    }

    friend Boolean operator!=(Atom<T> &atomic, const T &idx)
    {
        return atomic[idx] == idx;
    }

  private:
    T m_ArrayOfAtoms;
};
} // namespace MeKernel
