/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <KernelKit/FileManager.hpp>

#include <MeKit/ErrorID.hpp>
#include <MeKit/Utils.hpp>

namespace MeKernel
{
    extern bool rt_node_exists(Node node) noexcept;
    extern const char* rt_get_name_from_node(Node node) noexcept;

    static Node rt_open_or_create_node(MeFSImpl fIO, int catalogKind, const char* path) noexcept;

    static IFilesystemManager* kMounted = nullptr;
    MeFilesystemManager::MeFilesystemManager() = default;
    MeFilesystemManager::~MeFilesystemManager() = default;

    static Node rt_open_or_create_node(MeFSImpl fIO, int catalogKind, const char* path) noexcept
    {
        if (string_length(path) > kNameLen)
            return ME_TOO_LONG;

        if (fIO.GetCatalog(path).Kind != kInvalidCatalog)
            return ME_FILE_EXISTS;

        MeCatalog catalog;

        catalog.Flags = 0;
        catalog.Kind = catalogKind;

        copy_memory((voidPtr)catalog.Name, (voidPtr)path, string_length(path));

        auto node = fIO.WriteCatalog(catalog);
        
        return node;
    }

    bool MeFilesystemManager::Remove(Node node)
    {
        if (!rt_node_exists(node))
            return false;

        // will automatically erase it's forks.
        auto catalog = fIO.GetCatalog(rt_get_name_from_node(node));
        return fIO.RemoveCatalog(catalog);
    }

    Node MeFilesystemManager::Create(const char* path)
    {
        return rt_open_or_create_node(fIO, kCatalogKindFile, path);
    }

    Node MeFilesystemManager::CreateDirectory(const char *path)
    {
        return rt_open_or_create_node(fIO, kCatalogKindDir, path);
    }

    Node MeFilesystemManager::CreateAlias(const char *path)
    {
        return rt_open_or_create_node(fIO, kCatalogKindAlias, path);
    }

    namespace Details
    {
        enum
        {
            kPartXPM, // Me PowerStation
            kPartXPT, // PC
            kPartUDF, // DVD.
        };

        extern void rt_write_partiton_scheme(Int kind);
        extern void rt_write_filesystem(Int kind);
    }

    IFilesystemManager* IFilesystemManager::GetMounted()
    {
        return kMounted;
    }

    void IFilesystemManager::Mount(IFilesystemManager* fileManager)
    {
        if (fileManager)
            kMounted = fileManager;
    }
}
