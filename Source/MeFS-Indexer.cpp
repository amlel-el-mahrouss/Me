/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <MeKit/Utils.hpp>
#include <FSKit/MeFS-Indexer.hpp>
#include <CompilerKit/Compiler.hpp>

#define kMaxLenIndexer 256

namespace MeKernel
{
    namespace Indexer
    {
        bool IndexableProperty::SetPath(Char* path, SizeT len)
        {
            if (len > kMaxLenIndexer)
                return false;

            copy_memory((voidPtr)fIndexPath, (voidPtr)path, len);

            return true;
        }

        void IndexableProperty::AddFlag(Int16 flag) { fFlags |= flag; }
        void IndexableProperty::RemoveFlag(Int16 flag) { fFlags &= flag; }

        class IMeFSIterator;

        using IndexElement = voidPtr;

        ///
        /// \name IMeFSIterator
        /// Stores relevant information for file indexing.
        ///

        class IMeFSIterator
        {
        public:
            IMeFSIterator() = default;
            virtual ~IMeFSIterator() = default;

        public:
            ME_COPY_DEFAULT(IMeFSIterator);

        public:
            virtual void Add(IndexableProperty& indexProp) {  }
            virtual void Remove(IndexableProperty& indexProp) {  }
            virtual IndexElement Find(IndexProperty& filters) { return nullptr; }

        };
    }
}
