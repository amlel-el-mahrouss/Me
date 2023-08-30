/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <CFKit/GUIDWizard.hpp>
#include <MeKit/Ref.hpp>

namespace MeKernel::URN::Version1
{
    auto make_sequence(const ArrayList <UShort> &uuidSeq) -> Ref<GUIDSequence*>
    {
        GUIDSequence *seq = new GUIDSequence();

        if (!seq)
            return {};

        Ref<GUIDSequence*> sequenceReference{seq, true};

        sequenceReference->m_Ms1 |= uuidSeq[0];
        sequenceReference->m_Ms2 |= uuidSeq[1];
        sequenceReference->m_Ms3 |= uuidSeq[2];
        sequenceReference->m_Ms3 |= uuidSeq[3];

        return sequenceReference;
    }

// This function is not complete for now
    auto try_guid_to_string(Ref<GUIDSequence*> seq) -> ErrorOr <Ref<StringView>>
    {
        Char buf[32];

        for (Size index = 0; index < 16; ++index) {
            buf[index] = seq->u8[index];
        }

        for (Size index = 16; index < 24; ++index) {
            buf[index] = seq->u16[index];
        }

        for (Size index = 24; index < 28; ++index) {
            buf[index] = seq->u32[index];
        }

        auto view = StringBuilder::Construct(buf);

        if (view)
            return ErrorOr<Ref<StringView>> { view.Leak() };

        return ErrorOr<Ref<StringView>> {-1};
    }
} // namespace MeKernel::URN::Version1
