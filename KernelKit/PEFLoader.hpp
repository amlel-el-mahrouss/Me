#ifndef _INC_PEFLOADER_HPP
#define _INC_PEFLOADER_HPP

#include <KernelKit/PEF.hpp>
#include <MeKit/ErrorOr.hpp>

namespace MeKernel
{
    ///
    /// \name PEFLoader
    /// PEF container format implementation.
    ///
    class PEFLoader final : public Loader
    {
    public:
        PEFLoader() = delete;
        PEFLoader(const char* path);
        ~PEFLoader() override;

    public:
        ME_COPY_DEFAULT(PEFLoader);

    public:
        typedef int(*MainKind)();

    public:
        const char* Format() override { return "PEF"; }
        const char* MIME() override { return "application/X-PEF"; }

    public:
        ErrorOr<VoidPtr> LoadStart() override;
        VoidPtr FindSymbol(const char* name, PEF_OBJ_KIND kind);

    public:
        bool IsLoaded() noexcept;

    private:
        VoidPtr fCachedBlob;
        bool fBad;

    };
}

#endif // ifndef _INC_PEFLOADER_HPP
