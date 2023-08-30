/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <HALKit/AMD64/Page.hpp>
#include <MeKit/Foundation.hpp>
#include <MeKit/PageManager.hpp>

namespace MeKernel
{
namespace Details
{
enum PAGE_BIT
{
    ProtectedModeEnable = 0,
    MonitorCoProcessor = 1,
    Emulation = 2,
    TaskSwitched = 3,
    ExtensionType = 4,
    NumericError = 5,
    WriteProtect = 16,
    AlignementMask = 18,
    NotWriteThrough = 29,
    CacheDisable = 30,
    Paging = 31,
};
} // namespace Details

class ATTRIBUTE(packed) PTE final
{
  public:
    Boolean Present : 1;
    Boolean Rw : 1;
    Boolean User : 1;
    Boolean Wt : 1;
    Boolean Cache : 1;
    Boolean Accessed : 1;
    Boolean Shared : 1;
    Boolean ExecDisable : 1;
    UIntPtr PhysAddr : 32;
};

class ATTRIBUTE(packed) PDE final
{
  public:
    ATTRIBUTE(aligned(PTE_ALIGN)) PTE Entries[PTE_MAX];
};

namespace Details
{
UIntPtr create_page_wrapper(Boolean rw, Boolean user);
void exec_disable(UIntPtr addr);
bool page_disable(UIntPtr addr);
} // namespace Details

// TODO: SwapVirtualMemoryDevice class!
} // namespace MeKernel
