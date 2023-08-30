/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <CFKit/GUIDWrapper.hpp>
#include <MeKit/Array.hpp>
#include <MeKit/ArrayList.hpp>
#include <MeKit/ErrorOr.hpp>
#include <MeKit/Foundation.hpp>
#include <MeKit/Ref.hpp>
#include <MeKit/Stream.hpp>
#include <MeKit/String.hpp>

namespace MeKernel::URN::Version1
{
    Ref<GUIDSequence*> make_sequence(const ArrayList <UShort> &seq);
    ErrorOr <Ref<MeKernel::StringView>> try_guid_to_string(Ref<GUIDSequence*> &guid);
} // namespace MeKernel::URN::Version1
