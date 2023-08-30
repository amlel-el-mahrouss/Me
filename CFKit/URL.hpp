/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _INC_URL_HPP__
#define _INC_URL_HPP__

#include <MeKit/Foundation.hpp>
#include <MeKit/String.hpp>

namespace MeKernel
{
    class Url final
    {
    public:
        explicit Url(StringView &strUrl);
        ~Url();

    public:
        Ref<ErrorOr<StringView>> Location() noexcept;
        Ref<ErrorOr<StringView>> Protocol() noexcept;

    private:
        Ref<StringView> m_urlView;

    };

} // namespace MeKernel

#endif /* ifndef _INC_URL_HPP__ */