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

#include <HALKit/AMD64/Processor.hpp>
#include <MeKit/Array.hpp>
#include <MeKit/Ref.hpp>

namespace MeKernel
{
    template<SizeT Sz>
    class IOArray final
    {
    public:
        IOArray() = delete;

        IOArray(nullPtr) = delete;

        explicit IOArray(Array <UShort, Sz> &ports) : m_Ports(ports) {}
        ~IOArray() {}

        IOArray &operator=(const IOArray &) = default;

        IOArray(const IOArray &) = default;

        operator bool() {
            return !m_Ports.Empty();
        }

    public:
        template<typename T>
        T In(SizeT index) {
            switch (sizeof(T)) {
                case 4:
                    return HAL::in32(m_Ports[index].Leak());
                case 2:
                    return HAL::in16(m_Ports[index].Leak());
                case 1:
                    return HAL::in8(m_Ports[index].Leak());
                default:
                    return 0xFFFF;
            }
        }

        template<typename T>
        void Out(SizeT index, T value) {
            switch (sizeof(T)) {
                case 4:
                    HAL::out32(m_Ports[index].Leak(), value);
                case 2:
                    HAL::out16(m_Ports[index].Leak(), value);
                case 1:
                    HAL::out8(m_Ports[index].Leak(), value);
                default:
                    break;
            }
        }

    private:
        Array <UShort, Sz> m_Ports;
    };

    using IOArray16 = IOArray<16>;
} // namespace MeKernel
