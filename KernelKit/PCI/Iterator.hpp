#ifndef __PCI_ITERATOR_HPP__
#define __PCI_ITERATOR_HPP__

#include <KernelKit/PCI/Database.hpp>
#include <KernelKit/PCI/Device.hpp>
#include <MeKit/Array.hpp>
#include <MeKit/Foundation.hpp>
#include <MeKit/Ref.hpp>

#define ME_BUS_COUNT (256)
#define ME_DEVICE_COUNT (33)
#define ME_FUNCTION_COUNT (8)

namespace MeKernel::PCI {
    class Iterator final {
    public:
        Iterator() = delete;

    public:
        explicit Iterator(const Types::PciDeviceKind &deviceType);

        Iterator &operator=(const Iterator &) = default;

        Iterator(const Iterator &) = default;

        ~Iterator();

    public:
        Ref<PCI::Device> operator[](const Size &sz);

    private:
        Array<PCI::Device, ME_BUS_COUNT> m_Devices;
    };
} // namespace MeKernel::PCI

#endif // __PCI_ITERATOR_HPP__
