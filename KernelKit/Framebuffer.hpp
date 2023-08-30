/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _INC_FB_HPP__
#define _INC_FB_HPP__

#include <MeKit/Foundation.hpp>
#include <MeKit/Ref.hpp>

namespace MeKernel
{
    enum class FramebufferColorKind : UChar
    {
        RGB32,
        RGB16,
        RGB8,
        INVALID,
    };

    class FramebufferContext final
    {
    private:
        UIntPtr m_Base;
        UIntPtr m_Bpp;
        UInt m_Width;
        UInt m_Height;

    private:
        friend class Framebuffer;

    };

    class Framebuffer final
    {
    public:
        explicit Framebuffer(Ref<FramebufferContext*> &addr);

        ~Framebuffer();

        Framebuffer &operator=(const Framebuffer &) = delete;
        Framebuffer(const Framebuffer &) = delete;

        volatile UIntPtr *operator[](const UIntPtr &width_and_height);

        const FramebufferColorKind &Colour(const FramebufferColorKind &colour = FramebufferColorKind::INVALID);

    private:
        Ref<FramebufferContext*> &m_FrameBufferAddr;
        FramebufferColorKind m_Colour;

    };
} // namespace MeKernel

#endif /* ifndef _INC_FB_HPP__ */
