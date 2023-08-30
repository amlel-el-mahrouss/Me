
/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <MeKit/PageManager.hpp>
#include <MeKit/Ref.hpp>

namespace MeKernel
{
    class Pmm;
    class PTEWrapper;

    class Pmm final
    {
    public:
        Pmm();
        ~Pmm();

    public:
        explicit Pmm(Ref<PageManager*> &pm);

        Pmm &operator=(const Pmm &) = delete;
        Pmm(const Pmm &) = delete;

        Ref<PTEWrapper*> RequestPage(Boolean user = false, Boolean readWrite = false);
        Boolean FreePage(Ref<PTEWrapper*> refPage);

        Boolean ToggleRw(Ref<PTEWrapper*> refPage, Boolean enable = true);
        Boolean TogglePresent(Ref<PTEWrapper*> refPage, Boolean enable = true);
        Boolean ToggleUser(Ref<PTEWrapper*> refPage, Boolean enable = true);
        Boolean ToggleShare(Ref<PTEWrapper*> refPage, Boolean enable = true);

    private:
        Ref<PageManager*> m_PageManager;
    
    };
} // namespace MeKernel
