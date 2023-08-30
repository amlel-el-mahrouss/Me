/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <MeKit/PoolManager.hpp>
#include <MeKit/PageManager.hpp>
#include <MeKit/Panic.hpp>

/// bugs: 0

namespace MeKernel
{
    class PoolHelper final
    {
    public:
        static Size& GetCount()
        {
            return s_NumPools;
        }

        static Ref<Pmm>& GetPmm()
        {
            return s_Pmm;
        }

        static Boolean& IsEnabled()
        {
            return s_PoolsAreEnabled;
        }

        static Array<Ref<PTEWrapper*>, kPoolMaxSz>& The()
        {
            return s_Pool;
        }

    private:
        static Size s_NumPools;
        static Ref<Pmm> s_Pmm;

    private:
        static Boolean s_PoolsAreEnabled;
        static Array<Ref<PTEWrapper*>, kPoolMaxSz> s_Pool;

    };

    SizeT PoolHelper::s_NumPools = 0UL;
    Ref<Pmm> PoolHelper::s_Pmm;
    Boolean PoolHelper::s_PoolsAreEnabled = true;
    Array<Ref<PTEWrapper*>, kPoolMaxSz> PoolHelper::s_Pool;

    static voidPtr find_unused_pool(Int flags);
    static void free_pool_internal(voidPtr vaddr);
    static voidPtr make_pool(voidPtr vaddr, Int flags);
    static bool check_and_free_pool(const SizeT &index, voidPtr ptr);

    static voidPtr find_unused_pool(Int flags)
    {
        for (SizeT index = 0; index < kPoolMaxSz; ++index)
        {
            if (PoolHelper::The()[index] && !PoolHelper::The()[index].Leak().Leak().Leak()->Present())
            {
                PoolHelper::GetPmm().Leak().TogglePresent(PoolHelper::The()[index].Leak().Leak(), true);
                kcout << "[find_unused_pool] Done, trying now to make a pool\r\n";

                return make_pool((voidPtr)PoolHelper::The()[index].Leak().Leak().Leak()->VirtualAddress(), flags);
            }
        }

        return nullptr;
    }

    static voidPtr make_pool(voidPtr virtualAddress, Int flags)
    {
        if (virtualAddress)
        {
            PoolHeader* pool_hdr = reinterpret_cast<PoolHeader*>(virtualAddress);

            if (!pool_hdr->Free)
            {
                kcout << "[make_pool] pool_hdr->Free, Pool already exists\n";
                return nullptr;
            }

            pool_hdr->Flags = flags;
            pool_hdr->Magic = kPoolMag;
            pool_hdr->Free = false;

            kcout << "[make_pool] New allocation has been done.\n";
            return reinterpret_cast<voidPtr>((reinterpret_cast<UIntPtr>(virtualAddress) + sizeof(PoolHeader)));
        }

        kcout << "[make_pool] Address is invalid";
        return nullptr;
    }

    static void free_pool_internal(voidPtr virtualAddress)
    {
        PoolHeader* pool_hdr = reinterpret_cast<PoolHeader*>(reinterpret_cast<UIntPtr>(virtualAddress) - sizeof(PoolHeader));

        if (pool_hdr->Magic == kPoolMag)
        {
            pool_hdr->Free = false;
            pool_hdr->Flags = 0;

            kcout << "[free_pool_internal] Successfully marked header as free!\r\n";
        }
    }

    static bool check_and_free_pool(const SizeT &index, voidPtr ptr)
    {
        if (PoolHelper::The()[index])
        { // ErrorOr<>::operator bool
            if (!PoolHelper::The()[index].Leak().Leak().IsStrong())
            { // we want them to be weak
                // because we allocated it.
                if (PoolHelper::The()[index].Leak().Leak().Leak()->VirtualAddress() == (UIntPtr) ptr)
                {
                    PoolHelper::GetPmm().Leak().FreePage(PoolHelper::The()[index].Leak().Leak());
                    --PoolHelper::GetCount();

                    free_pool_internal(ptr);
                    ptr = nullptr;

                    return true;
                }
            }
        }

        return false;
    }

    voidPtr pool_new_ptr(Int flags)
    {
        if (!PoolHelper::IsEnabled())
            return nullptr;

        if (PoolHelper::GetCount() > kPoolMaxSz)
            return nullptr;

        if (voidPtr ret = find_unused_pool(flags))
            return ret;

        // this wasn't set to true
        auto ref_page = PoolHelper::GetPmm().Leak().RequestPage(((flags & kPoolUser)),
                                                         (flags & kPoolRw));
        if (ref_page)
        {
            ///! reserve page.
            PoolHelper::The()[PoolHelper::GetCount()].Leak() = ref_page;
            ++PoolHelper::GetCount(); // increment the number of addresses we have now.

            kcout << "[pool_new_ptr] New Address found!\r\n";

            // finally make the pool address.
            return make_pool(reinterpret_cast<voidPtr>(ref_page.Leak()->VirtualAddress()), flags);
        }

        return nullptr;
    }

    Int32 pool_free_ptr(voidPtr ptr)
    {
        if (!PoolHelper::IsEnabled())
            return -1;

        if (ptr)
        {
            SizeT base = PoolHelper::GetCount();
            if (check_and_free_pool(base, ptr))
                return 0;

            for (SizeT index = 0; index < kPoolMaxSz; ++index)
            {
                if (check_and_free_pool(index, ptr))
                    return 0;

                --base;
            }
        }

        return -1;
    }
} // namespace MeKernel
