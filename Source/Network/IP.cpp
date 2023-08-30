/*
 *	========================================================
 *
 *	MeKit
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <NetworkKit/IP.hpp>
#include <MeKit/Utils.hpp>

namespace MeKernel
{
    RawIPAddress::RawIPAddress(char bytes[4])
    {
        copy_memory(bytes, m_Addr, 4);
    }

    bool RawIPAddress::operator==(const RawIPAddress& ipv4)
    {
        for (Size index = 0; index < 4; ++index)
        {
            if (ipv4.m_Addr[index] != m_Addr[index])
                return false;
        }

        return true;
    }

    bool RawIPAddress::operator!=(const RawIPAddress& ipv4)
    {
        for (Size index = 0; index < 4; ++index)
        {
            if (ipv4.m_Addr[index] == m_Addr[index])
                return false;
        }

        return true;
    }

    char& RawIPAddress::operator[](const Size& index)
    {
        kcout << "[RawIPAddress::operator[]] Fetching Index...\r\n";

        if (index > 4)
            panic(RUNTIME_CHECK_EXPRESSION);

        return m_Addr[index];
    }

    RawIPAddress6::RawIPAddress6(char bytes[8])
    {
        copy_memory(bytes, m_Addr, 8);
    }

    char &RawIPAddress6::operator[](const Size &index)
    {
        kcout << "[RawIPAddress6::operator[]] Fetching Index...\r\n";

        if (index > 8)
            panic(RUNTIME_CHECK_EXPRESSION);

        return m_Addr[index];
    }

    bool RawIPAddress6::operator==(const RawIPAddress6& ipv6)
    {
        for (SizeT index = 0; index < 8; ++index)
        {
            if (ipv6.m_Addr[index] != m_Addr[index])
                return false;
        }

        return true;
    }

    bool RawIPAddress6::operator!=(const RawIPAddress6& ipv6)
    {
        for (SizeT index = 0; index < 8; ++index)
        {
            if (ipv6.m_Addr[index] == m_Addr[index])
                return false;
        }

        return true;
    }

    ErrorOr<StringView> IPHelper::ToStringView(Ref<RawIPAddress6> ipv6)
    {
        auto str = StringBuilder::Construct(ipv6.Leak().Address());
        return str;
    }

    ErrorOr<StringView> IPHelper::ToStringView(Ref<RawIPAddress> ipv4)
    {
        auto str = StringBuilder::Construct(ipv4.Leak().Address());
        return str;
    }

    bool IPHelper::IpCheckV4(const char *ip)
    {
        int cnter = 0;

        for (Size base = 0; base < string_length(ip); ++base)
        {
            if (ip[base] == '.')
            {
                cnter = 0;
            }
            else
            {
                if (cnter == 3)
                    return false;

                ++cnter;
            }
        }

        return true;
    }
} // namespace MeKit
