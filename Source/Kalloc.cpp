/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <MeKit/Kalloc.hpp>

///! this allocator is used by device drivers and the kernel to allocate pages.

namespace MeKernel
{
    static Ref<PTEWrapper*>* kWrapperList = nullptr;
    static SizeT kWrapperCount = 0UL;

    namespace Details
    {
        static voidPtr try_find_ptr(const Size &sz, const bool rw, const bool user)
        {
            for (SizeT indexWrapper = 0; indexWrapper < kWrapperCount; ++indexWrapper)
            {
                if (!kWrapperList[indexWrapper]->Present())
                {
                    kWrapperList[indexWrapper]->Reclaim(); /* very straightforward as you can see. */
                    return reinterpret_cast<voidPtr>(kWrapperList[indexWrapper]->VirtualAddress());
                }
            }

            return nullptr;
        }
    } // namespace Details

    voidPtr kernel_new_ptr(SizeT sz, const bool rw, const bool user)
    {
        if (kWrapperCount < sz)
            return nullptr;

        if (auto ptr = Details::try_find_ptr(sz, rw, user);
            ptr)
            return ptr;

        static Pmm pmm;

        Ref<PTEWrapper*> wrapper = pmm.RequestPage(user, rw);

        if (wrapper)
        {
            kWrapperList[kWrapperCount] = wrapper;
            ++kWrapperCount;

            return reinterpret_cast<voidPtr>(wrapper->VirtualAddress());
        }

        return nullptr;
    }

    Int32 kernel_delete_ptr(voidPtr ptr)
    {
        if (ptr)
        {
            Ref<PTEWrapper*> wrapper;

            const UIntPtr virtualAddress = reinterpret_cast<UIntPtr>(ptr);

            for (SizeT indexWrapper = 0; indexWrapper < kWrapperCount; ++indexWrapper)
            {
                if (kWrapperList[indexWrapper]->VirtualAddress() == virtualAddress)
                {
                    static Pmm pmm;

                    wrapper = kWrapperList[indexWrapper];
                    return pmm.FreePage(wrapper);
                }
            }
        }

        return -1;
    }
} // namespace MeKernel
