/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <MeKit/Kalloc.hpp>
#include <MeKit/String.hpp>
#include <MeKit/Utils.hpp>

namespace MeKernel
{
    Char* StringView::Data()
    {
        return m_Data;
    }

    const Char* StringView::CData()
    {
        return m_Data;
    }

    Size StringView::Length() const
    {
        return string_length(m_Data);
    }

    bool StringView::operator==(const StringView &rhs) const
    {
        if (rhs.Length() != Length())
            return false;

        for (Size index = 0; index < Length(); ++index)
        {
            if (rhs.m_Data[index] != m_Data[index])
                return false;
        }

        return true;
    }

    bool StringView::operator==(const Char *rhs) const
    {
        if (string_length(rhs) != Length())
            return false;

        for (Size index = 0; index < string_length(rhs); ++index)
        {
            if (rhs[index] != m_Data[index])
                return false;
        }

        return true;
    }

    bool StringView::operator!=(const StringView &rhs) const
    {
        if (rhs.Length() != Length())
            return false;

        for (Size index = 0; index < rhs.Length(); ++index)
        {
            if (rhs.m_Data[index] == m_Data[index])
                return false;
        }

        return true;
    }

    bool StringView::operator!=(const Char *rhs) const
    {
        if (string_length(rhs) != Length())
            return false;

        for (Size index = 0; index < string_length(rhs); ++index)
        {
            if (rhs[index] == m_Data[index])
                return false;
        }

        return true;
    }

    ErrorOr <StringView> StringBuilder::Construct(const Char *data)
    {
        if (!data ||
            *data == 0)
            return {};

        StringView *view = new StringView(string_length(data));
        MUST_PASS(view);

        copy_memory(reinterpret_cast<voidPtr>(const_cast<Char*>(data)), reinterpret_cast<voidPtr>(view->Data()),
                    view->Length());

        return ErrorOr<StringView>(*view);
    }

    const char* StringBuilder::FromInt(const char *fmt, int i)
    {
        if (!fmt)
            return ("-1");

        char *ret = new char[8 + string_length(fmt)];

        if (!ret)
            return ("-1");

        Char result[8];
        if (!to_str(result, sizeof(int), i))
        {
            delete[] ret;
            return ("-1");
        }

        const auto fmt_len = string_length(fmt);
        const auto res_len = string_length(result);

        for (Size idx = 0; idx < fmt_len; ++idx)
        {
            if (fmt[idx] == '%') {
                SizeT result_cnt = idx;

                for (auto y_idx = idx; y_idx < res_len; ++y_idx) {
                    ret[result_cnt] = result[y_idx];
                    ++result_cnt;
                }

                break;
            }

            ret[idx] = fmt[idx];
        }

        return ret; /* Copy that ret into a buffer, Alloca allocates to the stack */
    }

    const char *StringBuilder::FromBool(const char *fmt, bool i)
    {
        if (!fmt)
            return ("?");

        const char *boolean_expr = i ? "true" : "false";
        char *ret = new char[i ? 4 : 5 + string_length(fmt)];

        if (!ret)
            return ("?");

        const auto fmt_len = string_length(fmt);
        const auto res_len = string_length(boolean_expr);

        for (Size idx = 0; idx < fmt_len; ++idx)
        {
            if (fmt[idx] == '%') {
                SizeT result_cnt = idx;

                for (auto y_idx = idx; y_idx < res_len; ++y_idx)
                {
                    ret[result_cnt] = boolean_expr[y_idx];
                    ++result_cnt;
                }

                break;
            }

            ret[idx] = fmt[idx];
        }

        return ret;
    }

    bool StringBuilder::Equals(const char *lhs, const char *rhs)
    {
        if (string_length(rhs) != string_length(lhs))
            return false;

        for (Size index = 0; index < string_length(rhs); ++index)
        {
            if (rhs[index] != lhs[index])
                return false;
        }

        return true;
    }

    Ref<StringView> StringBuilder::ConstructUnwrap(const Char *data)
    {
        return StringBuilder::Construct(data).Leak();
    }

    const char *StringBuilder::Format(const char *fmt, const char *fmt2)
    {
        if (!fmt || !fmt2)
            return ("?");

        char *ret = new char[string_length(fmt2) + string_length(fmt2)];
        if (!ret)
            return ("?");

        for (Size idx = 0; idx < string_length(fmt); ++idx)
        {
            if (fmt[idx] == '%') {
                Size result_cnt = idx;
                for (Size y_idx = 0; y_idx < string_length(fmt2); ++y_idx)
                {
                    ret[result_cnt] = fmt2[y_idx];
                    ++result_cnt;
                }

                break;
            }

            ret[idx] = fmt[idx];
        }

        return ret;
    }

    static void string_append(char *lhs, char *rhs)
    {
        if (lhs && rhs)
        {
            SizeT sz_lhs = string_length(lhs);
            SizeT sz_rhs = string_length(rhs);

            copy_memory(rhs, lhs + sz_lhs, sz_rhs);
        }
    }

    StringView &StringView::operator+=(const Char *rhs)
    {
        string_append(this->m_Data, const_cast<char*>(rhs));
        return *this;
    }

    StringView &StringView::operator+=(const StringView &rhs)
    {
        string_append(this->m_Data, const_cast<char*>(rhs.m_Data));
        return *this;
    }
} // namespace MeKernel
