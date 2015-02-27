//--------------------------------------------------------------------------
// Copyright (C) 2014-2015 Cisco and/or its affiliates. All rights reserved.
// Copyright (C) 2009-2013 Sourcefire, Inc.
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License Version 2 as published
// by the Free Software Foundation.  You may not use, modify or distribute
// this program under any other version of the GNU General Public License.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//--------------------------------------------------------------------------

#ifndef RATE_FILTER_H
#define RATE_FILTER_H

/* @file  rate_filter.h
 * @brief rate filter interface for Snort
 * @ingroup rate_filter
 * @author Dilbagh Chahal
*/

/* @ingroup rate_filter
 * @{
 */

struct RateFilterConfig;
struct SnortConfig;
struct tSFRFConfigNode;
struct Packet;
struct OptTreeNode;

RateFilterConfig* RateFilter_ConfigNew(void);
void RateFilter_ConfigFree(RateFilterConfig*);
void RateFilter_Cleanup(void);

struct SnortConfig;
int RateFilter_Create(SnortConfig* sc, RateFilterConfig*, tSFRFConfigNode*);
void RateFilter_PrintConfig(RateFilterConfig*);

int RateFilter_Test(OptTreeNode*, Packet*);
void RateFilter_ResetActive(void);

/*@}*/
#endif

