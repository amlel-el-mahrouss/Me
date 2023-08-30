/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <CFKit/Property.hpp>
#include <KernelKit/MountManager.hpp>

namespace MeKernel
{
    namespace Indexer
    {
        class IndexableProperty final : public Property
        {
        public:
            ~IndexableProperty() override = default;

        public:
            bool SetPath(Char* path, SizeT len);

        public:
            void AddFlag(Int16 flag);
            void RemoveFlag(Int16 flag);

        private:
            UInt32 fFlags;
            Char fIndexPath[256];

        };

        struct IndexProperty
        {
        public:
            Char Drive[kDriveNameLen];
            Char Path[256];
            Char From[256];
            Char To[256];

        };
    }
}
