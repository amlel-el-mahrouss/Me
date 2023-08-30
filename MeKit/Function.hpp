#ifndef _INC_FUNCTION_HPP__
#define _INC_FUNCTION_HPP__

#include <MeKit/Foundation.hpp>

namespace MeKernel
{
template <typename T, typename... Args> class Function final
{
  public:
    Function() = default;

    explicit Function(T (*Fn)(Args... args)) : m_Fn(Fn)
    {
    }

    ~Function()
    {
    }

    Function &operator=(const Function &) = default;
    Function(const Function &) = default;

    template <typename... XArgs> T operator()(Args... args)
    {
        return m_Fn(args...);
    }

    template <typename... XArgs> T Call(Args... args)
    {
        return m_Fn(args...);
    }

    operator bool()
    {
        return m_Fn;
    }
    bool operator!()
    {
        return !m_Fn;
    }

  private:
    T (*m_Fn)(Args... args);
};
} // namespace MeKernel

#endif // !_INC_FUNCTION_HPP__
