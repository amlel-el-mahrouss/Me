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
#include <KernelKit/Out.hpp>
#include <MeKit/String.hpp>
#include <MeKit/Ref.hpp>

namespace MeKernel
{
class RawIPAddress6;
class RawIPAddress;
class NetworkManager;

class RawIPAddress final
{
  private:
    RawIPAddress(char bytes[4]);
    ~RawIPAddress() = default;

    RawIPAddress &operator=(const RawIPAddress &) = delete;
    RawIPAddress(const RawIPAddress &) = default;

  public:
    char *Address()
    {
        return m_Addr;
    }

    char &operator[](const Size &index);

    bool operator==(const RawIPAddress &ipv6);
    bool operator!=(const RawIPAddress &ipv6);

  private:
    char m_Addr[4];

    friend NetworkManager; // it is the one creating these addresses, thus this
                           // is why the constructors are private.
};

class RawIPAddress6 final
{
  private:
    RawIPAddress6(char Bytes[8]);
    ~RawIPAddress6() = default;

    RawIPAddress6 &operator=(const RawIPAddress6 &) = delete;
    RawIPAddress6(const RawIPAddress6 &) = default;

  public:
    char *Address()
    {
        return m_Addr;
    }

    char &operator[](const Size &index);

    bool operator==(const RawIPAddress6 &ipv6);
    bool operator!=(const RawIPAddress6 &ipv6);

  private:
    char m_Addr[8];

    friend NetworkManager;
};

class IPHelper
{
  public:
    static ErrorOr<StringView> ToStringView(Ref<RawIPAddress6> ipv6);
    static ErrorOr<StringView> ToStringView(Ref<RawIPAddress> ipv4);
    static bool IpCheckV4(const char *ip);

};
} // namespace MeKernel
