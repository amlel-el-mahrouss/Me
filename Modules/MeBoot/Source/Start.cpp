/*
 *	========================================================
 *
 *	MeBoot
 * 	Copyright Amlal El Mahrouss., all rights reserved.
 *
 * 	========================================================
 */

#include <BootKit/Boot.hpp>

Int32 BootMain(void)
{
    BootTextWriter writer;
    writer.WriteString("Loading MeKernel...", kBlack, kWhite, 0, 0);

    return 0;
}
