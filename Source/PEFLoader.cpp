/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <KernelKit/FileManager.hpp>
#include <KernelKit/PEFLoader.hpp>
#include <KernelKit/Out.hpp>
#include <MeKit/Kalloc.hpp>
#include <MeKit/String.hpp>
#include <MeKit/OwnPtr.hpp>
#include <MeKit/ErrorID.hpp>

namespace MeKernel
{
    namespace Details
    {
        static UInt32 pef_get_platform(void)
        {
#ifdef __POWER
            return kPefArchPower;
#elif defined(__x86_64__)
            return kPefArchAMD64;
#else
            return kPefArchInvalid;
#endif // __POWER || __x86_64__
        }
    }

    PEFLoader::PEFLoader(const char* path)
        : fCachedBlob(nullptr), fBad(false)
    {
        OwnPtr<FileStream<char>> file;

        file.New(path);

        if (!StringBuilder::Equals(file->MIME(), MIME()))
        {

            VoidPtr executable_blob = file->ReadAll();

            if (!fCachedBlob)
                fCachedBlob = executable_blob;

            PEFContainer* container = reinterpret_cast<PEFContainer*>(fCachedBlob);

            auto fFree = [&]() -> void {
                kcout << "PEF: Warning: Bad executable, program will not be started!";
                fBad = true;

                kernel_delete_ptr(fCachedBlob);
                
                fCachedBlob = nullptr;
            };

            if (container->Cpu == Details::pef_get_platform() &&
                    container->Magic[0] == kPefMagic[0] &&
                    container->Magic[1] == kPefMagic[1] &&
                    container->Magic[2] == kPefMagic[2])
            {
                if (container->Kind != kPefKindObject ||
                    container->Kind != kPefKindDwarf)
                {
                    kcout << "PEF: Info: good executable. can proceed.";
                    return;
                }
            }

            fFree();
        }
    }

    PEFLoader::~PEFLoader()
    {
        if (fCachedBlob)
            fCachedBlob = nullptr; ///! Do not free this blob, otherwise we'll get invalid instructions exception from the cpu.
    }

    VoidPtr PEFLoader::FindSymbol(const char* name, PEF_OBJ_KIND kind)
    {
        if (!fCachedBlob ||
            fBad)
            return nullptr;

        PEFContainer* container = reinterpret_cast<PEFContainer*>(fCachedBlob);
        PEFContainerHeader* container_header = reinterpret_cast<PEFContainerHeader*>((UIntPtr)fCachedBlob + sizeof(PEFContainer));

        for (SizeT index = 0; index < container->Count; ++index)
        {
            kcout << "Iterating over container at index: " << StringBuilder::FromInt("%", index) << ", name: " << container_header->Name << "\n";

            if (StringBuilder::Equals(container_header->Name, name))
            {
                kcout << "Found potential container, checking for validity.";

                if (container_header->Kind == kind)
                    return static_cast<UIntPtr*>(fCachedBlob) + container_header->Off;

                continue;
            }
        }

        return nullptr;
    }

    ErrorOr<VoidPtr> PEFLoader::LoadStart()
    {
        if (auto sym = this->FindSymbol("_start", kPefCode); sym)
            return ErrorOr<VoidPtr>(sym);

        return ErrorOr<VoidPtr>(ME_EXEC_ERROR);
    }

    bool PEFLoader::IsLoaded() noexcept { return !fBad && fCachedBlob; }
} // namespace MeKernel
