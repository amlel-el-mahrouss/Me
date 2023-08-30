/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <KernelKit/Framebuffer.hpp>

namespace MeKernel
{
    Framebuffer::Framebuffer(MeKernel::Ref<FramebufferContext*> &addr)
            : m_FrameBufferAddr(addr), m_Colour(FramebufferColorKind::RGB32)
    {}

    Framebuffer::~Framebuffer() = default;

    volatile UIntPtr *Framebuffer::operator[](const UIntPtr &width_and_height)
    {
        if (m_FrameBufferAddr)
            return reinterpret_cast<volatile MeKernel::UIntPtr*>(m_FrameBufferAddr->m_Base + width_and_height);

        return nullptr;
    }

    const FramebufferColorKind &Framebuffer::Colour(const FramebufferColorKind &colour)
    {
        if (colour != FramebufferColorKind::INVALID)
            m_Colour = colour;

        return m_Colour;
    }
} // namespace MeKernel
