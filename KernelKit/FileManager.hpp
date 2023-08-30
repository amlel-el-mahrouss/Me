/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <KernelKit/PermissionManager.hpp>
#include <KernelKit/DeviceManager.hpp>
#include <MeKit/Stream.hpp>
#include <MeKit/Ref.hpp>
#include <FSKit/MeFS.hpp>

#include <MeKit/ErrorID.hpp>
#include <MeKit/Ref.hpp>

/// Main filesystem abstraction manager.

#define kBootFolder "/boot"
#define kShLibsFolder "/lib"

#define kSectorSz 512

/// refer to first enum.
#define kFileOpsCount 4

namespace MeKernel
{
    enum
    {
        kFileWriteAll = 100,
        kFileReadAll = 101,
        kFileReadChunk = 102,
        kFileWriteChunk = 103,
    };

    typedef Int64 Node;
    typedef Node NodeDir;

    class IFilesystemManager
    {
    public:
        IFilesystemManager() = default;
        virtual ~IFilesystemManager() = default;

    public:
        ME_COPY_DEFAULT(IFilesystemManager);

    public:
        static void Mount(IFilesystemManager* fileManager);
        static IFilesystemManager* GetMounted();

    public:
        virtual Node Create(const char* path) = 0;
        virtual Node CreateAlias(const char* path) = 0;
        virtual Node CreateDirectory(const char* path) = 0;

    public:
        virtual bool Remove(Node node) = 0;

    public:
        virtual Node Open(const char* path, const char* r) = 0;

    public:
        virtual void Write(Node node, VoidPtr data, Int32 flags) = 0;
        virtual VoidPtr Read(Node node, Int32 flags, SizeT sz) = 0;

    public:
        virtual bool Seek(Node node, SizeT off) = 0;

    public:
        virtual SizeT Tell(Node node) = 0;
        virtual bool Rewind(Node node) = 0;

    };

    class MeFilesystemManager final : public IFilesystemManager
    {
    public:
        MeFilesystemManager();
        ~MeFilesystemManager() override;

    public:
        ME_COPY_DEFAULT(MeFilesystemManager);

    public:
        Node Create(const char* path) override;
        Node CreateAlias(const char* path) override;
        Node CreateDirectory(const char* path) override;

    public:
        bool Remove(Node node) override;

    public:
        Node Open(const char* path, const char* r) override;

    public:
        void Write(Node node, VoidPtr data, Int32 flags) override;
        VoidPtr Read(Node node, Int32 flags, SizeT sz) override;

    public:
        bool Seek(Node node, SizeT off) override;

    public:
        SizeT Tell(Node node) override;
        bool Rewind(Node node) override;

    private:
        MeFSImpl fIO;

    };

    template <typename Encoding = char, typename FSClass = MeFilesystemManager>
    class FileStream final
    {
    public:
        FileStream(const Encoding* path);
        ~FileStream();

    public:
        FileStream &operator=(const FileStream &);                                                                         \
        FileStream(const FileStream &);

    public:
        ErrorOr<Int64> WriteAll(const VoidPtr data) noexcept
        {
            if (data == nullptr)
                return ErrorOr<Int64>(ME_INVALID_DATA);

            auto man = FSClass::GetMounted();

            if (man)
            {
                man->Write(fFile, data, kFileWriteAll);
                return ErrorOr<Int64>(0);
            }

            return ErrorOr<Int64>(ME_INVALID_DATA);
        }

        VoidPtr ReadAll() noexcept
        {
            auto man = FSClass::GetMounted();

            if (man)
            {
                VoidPtr ret = man->Read(fFile, kFileReadAll, 0);
                return ret;
            }

            return nullptr;
        }

        voidPtr Read(SizeT offset, SizeT sz)
        {
            auto man = FSClass::GetMounted();

            if (man)
            {
                man->Seek(fFile, offset);
                auto ret = man->Read(fFile, kFileReadChunk, sz);

                return ret;
            }

            return nullptr;
        }

        void Write(SizeT offset, voidPtr data, SizeT sz)
        {
            auto man = FSClass::GetMounted();

            if (man)
            {
                man->Seek(fFile, offset);
                man->Write(fFile, data, sz, kFileReadChunk);
            }
        }

    public:
        const char* MIME() noexcept;

    private:
        Node fFile;

    };

    using FileStreamUTF8 = FileStream<char>;
    using FileStreamUTF16 = FileStream<wchar_t>;

    template <typename Encoding, typename Class>
    FileStream<Encoding, Class>::FileStream(const Encoding* path)
        : fFile(Class::GetMounted()->Open(path, "r+"))
    {}

    template <typename Encoding, typename Class>
    FileStream<Encoding, Class>::~FileStream() = default;
}
