// a way to create and find our pages.
// I'm thinking about a separate way of getting a paged area.

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
#include <MeKit/PageAllocator.hpp>
#include <MeKit/Ref.hpp>

#ifndef kBadAddress
#define kBadAddress (0)
#endif // #ifndef kBadAddress

namespace MeKernel
{
class PageManager;

class PTEWrapper final
{
  public:
    explicit PTEWrapper(Boolean Rw = false, Boolean User = false, Boolean ExecDisable = false, UIntPtr Address = 0);
    ~PTEWrapper();

    PTEWrapper &operator=(const PTEWrapper &) = default;
    PTEWrapper(const PTEWrapper &) = default;

  public:
    void FlushTLB(Ref<PageManager> &pm);
    const UIntPtr &VirtualAddress();

    bool Reclaim();
    bool Shareable();
    bool Present();
    bool Access();

  private:
    Boolean m_Rw;
    Boolean m_User;
    Boolean m_ExecDisable;
    UIntPtr m_VirtAddr;
    Boolean m_Cache;
    Boolean m_Shareable;
    Boolean m_Wt;
    Boolean m_Present;
    Boolean m_Accessed;

  private:
    friend class PageManager;
    friend class Pmm;
};

struct PageManager final
{
  public:
    PageManager() = default;
    ~PageManager() = default;

    PageManager &operator=(const PageManager &) = default;
    PageManager(const PageManager &) = default;

  public:
    PTEWrapper *Request(Boolean Rw, Boolean User, Boolean ExecDisable);
    bool Free(Ref<PTEWrapper*> &wrapper);

  private:
    void FlushTLB(UIntPtr VirtAddr);

  private:
    friend PTEWrapper;
    friend class Pmm;
};
} // namespace MeKernel
