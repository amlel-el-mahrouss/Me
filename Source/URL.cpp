/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <CFKit/URL.hpp>
#include <KernelKit/Out.hpp>
#include <MeKit/Utils.hpp>

namespace MeKernel
{
    Url::Url(StringView &strUrl) : m_urlView(strUrl, false) {}
    Url::~Url() = default;

    constexpr const char *kProtos[] = {
        "https",
        "http",
        "file",
        "ftp",
        "search",
        "rsh",
    };

    constexpr const int kUrlOutSz = 3; //! ://
    constexpr const int kProtosCount = 7;
    constexpr const int kRangeSz = 4096;

    static ErrorOr<StringView> url_extract_url_location(const char *url)
    {
        if (!url || *url == 0 || string_length(url, kRangeSz) > kRangeSz)
            return ErrorOr<StringView>{-1};

        StringView view(string_length(url));

        SizeT i = 0;
        bool scheme_found = false;

        for (; i < string_length(url); ++i)
        {
            if (!scheme_found)
            {
                for (int y = 0; kProtosCount; ++y)
                {
                    if (string_in_string(view.CData(), kProtos[y]))
                    {
                        i += string_length(kProtos[y]) + kUrlOutSz;
                        scheme_found = true;

                        break;
                    }
                }
            }

            view.Data()[i] += url[i];
        }

        return ErrorOr<StringView>(view);
    }

    static ErrorOr<StringView> url_extract_url_protocol(const char *url)
    {
        if (!url || *url == 0 || string_length(url, kRangeSz) > kRangeSz)
            return ErrorOr<StringView>{-1};

        ErrorOr<StringView> view{ -1 };
        return view;
    }

    Ref<ErrorOr<StringView>> Url::Location() noexcept
    {

        const char *src = m_urlView.Leak().CData();
        auto loc = url_extract_url_location(src);

        if (!loc)
            return {};

        return Ref<ErrorOr<StringView>>(loc);
    }

    Ref<ErrorOr<StringView>> Url::Protocol() noexcept
    {

        const char *src = m_urlView.Leak().CData();
        auto loc = url_extract_url_protocol(src);

        if (!loc)
            return {};

        return Ref<ErrorOr<StringView>>(loc);
    }
} // namespace MeKernel
