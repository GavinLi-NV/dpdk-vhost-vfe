/*
 * Copyright(c) 2001-2020, Broadcom. All rights reserved. The
 * term Broadcom refers to Broadcom Inc. and/or its subsidiaries.
 * Proprietary and Confidential Information.
 *
 * This source file is the property of Broadcom Corporation, and
 * may not be copied or distributed in any isomorphic form without
 * the prior written consent of Broadcom Corporation.
 *
 * DO NOT MODIFY!!! This file is automatically generated.
 */

#ifndef _CFA_RESOURCE_TYPES_H_
#define _CFA_RESOURCE_TYPES_H_
/*
 * This is the constant used to define invalid CFA
 * resource types across all devices.
 */
#define CFA_RESOURCE_TYPE_INVALID 65535

/* L2 Context TCAM */
#define CFA_RESOURCE_TYPE_P59_L2_CTXT_TCAM    0x0UL
/* Profile Func */
#define CFA_RESOURCE_TYPE_P59_PROF_FUNC       0x1UL
/* Profile TCAM */
#define CFA_RESOURCE_TYPE_P59_PROF_TCAM       0x2UL
/* Exact Match Profile Id */
#define CFA_RESOURCE_TYPE_P59_EM_PROF_ID      0x3UL
/* Wildcard TCAM Profile Id */
#define CFA_RESOURCE_TYPE_P59_WC_TCAM_PROF_ID 0x4UL
/* Wildcard TCAM */
#define CFA_RESOURCE_TYPE_P59_WC_TCAM         0x5UL
/* Meter Profile */
#define CFA_RESOURCE_TYPE_P59_METER_PROF      0x6UL
/* Meter */
#define CFA_RESOURCE_TYPE_P59_METER           0x7UL
/* Meter */
#define CFA_RESOURCE_TYPE_P59_MIRROR          0x8UL
/* Source Properties TCAM */
#define CFA_RESOURCE_TYPE_P59_SP_TCAM         0x9UL
/* Exact Match Flexible Key Builder */
#define CFA_RESOURCE_TYPE_P59_EM_FKB          0xaUL
/* Wildcard Flexible Key Builder */
#define CFA_RESOURCE_TYPE_P59_WC_FKB          0xbUL
/* Table Scope */
#define CFA_RESOURCE_TYPE_P59_TBL_SCOPE       0xcUL
/* L2 Func */
#define CFA_RESOURCE_TYPE_P59_L2_FUNC         0xdUL
/* EPOCH */
#define CFA_RESOURCE_TYPE_P59_EPOCH           0xeUL
/* Metadata */
#define CFA_RESOURCE_TYPE_P59_METADATA        0xfUL
/* Connection Tracking Rule TCAM */
#define CFA_RESOURCE_TYPE_P59_CT_RULE_TCAM    0x10UL
/* Range Profile */
#define CFA_RESOURCE_TYPE_P59_RANGE_PROF      0x11UL
/* Range */
#define CFA_RESOURCE_TYPE_P59_RANGE           0x12UL
/* Link Aggrigation */
#define CFA_RESOURCE_TYPE_P59_LAG             0x13UL
/* VEB TCAM */
#define CFA_RESOURCE_TYPE_P59_VEB_TCAM        0x14UL
#define CFA_RESOURCE_TYPE_P59_LAST           CFA_RESOURCE_TYPE_P59_VEB_TCAM


/* Multicast Group */
#define CFA_RESOURCE_TYPE_P58_MCG             0x0UL
/* Encap 8 byte record */
#define CFA_RESOURCE_TYPE_P58_ENCAP_8B        0x1UL
/* Encap 16 byte record */
#define CFA_RESOURCE_TYPE_P58_ENCAP_16B       0x2UL
/* Encap 64 byte record */
#define CFA_RESOURCE_TYPE_P58_ENCAP_64B       0x3UL
/* Source Property MAC */
#define CFA_RESOURCE_TYPE_P58_SP_MAC          0x4UL
/* Source Property MAC and IPv4 */
#define CFA_RESOURCE_TYPE_P58_SP_MAC_IPV4     0x5UL
/* Source Property MAC and IPv6 */
#define CFA_RESOURCE_TYPE_P58_SP_MAC_IPV6     0x6UL
/* Network Address Translation Source Port */
#define CFA_RESOURCE_TYPE_P58_NAT_SPORT       0x7UL
/* Network Address Translation Destination Port */
#define CFA_RESOURCE_TYPE_P58_NAT_DPORT       0x8UL
/* Network Address Translation Source IPv4 address */
#define CFA_RESOURCE_TYPE_P58_NAT_S_IPV4      0x9UL
/* Network Address Translation Destination IPv4 address */
#define CFA_RESOURCE_TYPE_P58_NAT_D_IPV4      0xaUL
/* Network Address Translation Source IPv4 address */
#define CFA_RESOURCE_TYPE_P58_NAT_S_IPV6      0xbUL
/* Network Address Translation Destination IPv4 address */
#define CFA_RESOURCE_TYPE_P58_NAT_D_IPV6      0xcUL
/* Meter */
#define CFA_RESOURCE_TYPE_P58_METER           0xdUL
/* Flow State */
#define CFA_RESOURCE_TYPE_P58_FLOW_STATE      0xeUL
/* Full Action Records */
#define CFA_RESOURCE_TYPE_P58_FULL_ACTION     0xfUL
/* Action Record Format 0 */
#define CFA_RESOURCE_TYPE_P58_FORMAT_0_ACTION 0x10UL
/* Action Record Format 2 */
#define CFA_RESOURCE_TYPE_P58_FORMAT_2_ACTION 0x11UL
/* Action Record Format 3 */
#define CFA_RESOURCE_TYPE_P58_FORMAT_3_ACTION 0x12UL
/* Action Record Format 4 */
#define CFA_RESOURCE_TYPE_P58_FORMAT_4_ACTION 0x13UL
/* L2 Context TCAM */
#define CFA_RESOURCE_TYPE_P58_L2_CTXT_TCAM    0x14UL
/* Profile Func */
#define CFA_RESOURCE_TYPE_P58_PROF_FUNC       0x15UL
/* Profile TCAM */
#define CFA_RESOURCE_TYPE_P58_PROF_TCAM       0x16UL
/* Exact Match Profile Id */
#define CFA_RESOURCE_TYPE_P58_EM_PROF_ID      0x17UL
/* Wildcard Profile Id */
#define CFA_RESOURCE_TYPE_P58_WC_TCAM_PROF_ID 0x18UL
/* Exact Match Record */
#define CFA_RESOURCE_TYPE_P58_EM_REC          0x19UL
/* Wildcard TCAM */
#define CFA_RESOURCE_TYPE_P58_WC_TCAM         0x1aUL
/* Meter profile */
#define CFA_RESOURCE_TYPE_P58_METER_PROF      0x1bUL
/* Meter */
#define CFA_RESOURCE_TYPE_P58_MIRROR          0x1cUL
/* Source Property TCAM */
#define CFA_RESOURCE_TYPE_P58_SP_TCAM         0x1dUL
/* Exact Match Flexible Key Builder */
#define CFA_RESOURCE_TYPE_P58_EM_FKB          0x1eUL
/* Wildcard Flexible Key Builder */
#define CFA_RESOURCE_TYPE_P58_WC_FKB          0x1fUL
/* VEB TCAM */
#define CFA_RESOURCE_TYPE_P58_VEB_TCAM        0x20UL
#define CFA_RESOURCE_TYPE_P58_LAST           CFA_RESOURCE_TYPE_P58_VEB_TCAM


/* Multicast Group */
#define CFA_RESOURCE_TYPE_P45_MCG             0x0UL
/* Encap 8 byte record */
#define CFA_RESOURCE_TYPE_P45_ENCAP_8B        0x1UL
/* Encap 16 byte record */
#define CFA_RESOURCE_TYPE_P45_ENCAP_16B       0x2UL
/* Encap 64 byte record */
#define CFA_RESOURCE_TYPE_P45_ENCAP_64B       0x3UL
/* Source Property MAC */
#define CFA_RESOURCE_TYPE_P45_SP_MAC          0x4UL
/* Source Property MAC and IPv4 */
#define CFA_RESOURCE_TYPE_P45_SP_MAC_IPV4     0x5UL
/* Source Property MAC and IPv6 */
#define CFA_RESOURCE_TYPE_P45_SP_MAC_IPV6     0x6UL
/* 64B Counters */
#define CFA_RESOURCE_TYPE_P45_COUNTER_64B     0x7UL
/* Network Address Translation Source Port */
#define CFA_RESOURCE_TYPE_P45_NAT_SPORT       0x8UL
/* Network Address Translation Destination Port */
#define CFA_RESOURCE_TYPE_P45_NAT_DPORT       0x9UL
/* Network Address Translation Source IPv4 address */
#define CFA_RESOURCE_TYPE_P45_NAT_S_IPV4      0xaUL
/* Network Address Translation Destination IPv4 address */
#define CFA_RESOURCE_TYPE_P45_NAT_D_IPV4      0xbUL
/* Network Address Translation Source IPv6 address */
#define CFA_RESOURCE_TYPE_P45_NAT_S_IPV6      0xcUL
/* Network Address Translation Destination IPv6 address */
#define CFA_RESOURCE_TYPE_P45_NAT_D_IPV6      0xdUL
/* Meter */
#define CFA_RESOURCE_TYPE_P45_METER           0xeUL
/* Flow State */
#define CFA_RESOURCE_TYPE_P45_FLOW_STATE      0xfUL
/* Full Action Records */
#define CFA_RESOURCE_TYPE_P45_FULL_ACTION     0x10UL
/* Action Record Format 0 */
#define CFA_RESOURCE_TYPE_P45_FORMAT_0_ACTION 0x11UL
/* Action Record Format 2 */
#define CFA_RESOURCE_TYPE_P45_FORMAT_2_ACTION 0x12UL
/* Action Record Format 3 */
#define CFA_RESOURCE_TYPE_P45_FORMAT_3_ACTION 0x13UL
/* Action Record Format 4 */
#define CFA_RESOURCE_TYPE_P45_FORMAT_4_ACTION 0x14UL
/* L2 Context TCAM */
#define CFA_RESOURCE_TYPE_P45_L2_CTXT_TCAM    0x15UL
/* Profile Func */
#define CFA_RESOURCE_TYPE_P45_PROF_FUNC       0x16UL
/* Profile TCAM */
#define CFA_RESOURCE_TYPE_P45_PROF_TCAM       0x17UL
/* Exact Match Profile Id */
#define CFA_RESOURCE_TYPE_P45_EM_PROF_ID      0x18UL
/* Exact Match Record */
#define CFA_RESOURCE_TYPE_P45_EM_REC          0x19UL
/* Wildcard Profile Id */
#define CFA_RESOURCE_TYPE_P45_WC_TCAM_PROF_ID 0x1aUL
/* Wildcard TCAM */
#define CFA_RESOURCE_TYPE_P45_WC_TCAM         0x1bUL
/* Meter profile */
#define CFA_RESOURCE_TYPE_P45_METER_PROF      0x1cUL
/* Meter */
#define CFA_RESOURCE_TYPE_P45_MIRROR          0x1dUL
/* Source Property TCAM */
#define CFA_RESOURCE_TYPE_P45_SP_TCAM         0x1eUL
/* VEB TCAM */
#define CFA_RESOURCE_TYPE_P45_VEB_TCAM        0x1fUL
#define CFA_RESOURCE_TYPE_P45_LAST           CFA_RESOURCE_TYPE_P45_VEB_TCAM


/* Multicast Group */
#define CFA_RESOURCE_TYPE_P4_MCG             0x0UL
/* Encap 8 byte record */
#define CFA_RESOURCE_TYPE_P4_ENCAP_8B        0x1UL
/* Encap 16 byte record */
#define CFA_RESOURCE_TYPE_P4_ENCAP_16B       0x2UL
/* Encap 64 byte record */
#define CFA_RESOURCE_TYPE_P4_ENCAP_64B       0x3UL
/* Source Property MAC */
#define CFA_RESOURCE_TYPE_P4_SP_MAC          0x4UL
/* Source Property MAC and IPv4 */
#define CFA_RESOURCE_TYPE_P4_SP_MAC_IPV4     0x5UL
/* Source Property MAC and IPv6 */
#define CFA_RESOURCE_TYPE_P4_SP_MAC_IPV6     0x6UL
/* 64B Counters */
#define CFA_RESOURCE_TYPE_P4_COUNTER_64B     0x7UL
/* Network Address Translation Source Port */
#define CFA_RESOURCE_TYPE_P4_NAT_SPORT       0x8UL
/* Network Address Translation Destination Port */
#define CFA_RESOURCE_TYPE_P4_NAT_DPORT       0x9UL
/* Network Address Translation Source IPv4 address */
#define CFA_RESOURCE_TYPE_P4_NAT_S_IPV4      0xaUL
/* Network Address Translation Destination IPv4 address */
#define CFA_RESOURCE_TYPE_P4_NAT_D_IPV4      0xbUL
/* Network Address Translation Source IPv6 address */
#define CFA_RESOURCE_TYPE_P4_NAT_S_IPV6      0xcUL
/* Network Address Translation Destination IPv6 address */
#define CFA_RESOURCE_TYPE_P4_NAT_D_IPV6      0xdUL
/* Meter */
#define CFA_RESOURCE_TYPE_P4_METER           0xeUL
/* Flow State */
#define CFA_RESOURCE_TYPE_P4_FLOW_STATE      0xfUL
/* Full Action Records */
#define CFA_RESOURCE_TYPE_P4_FULL_ACTION     0x10UL
/* Action Record Format 0 */
#define CFA_RESOURCE_TYPE_P4_FORMAT_0_ACTION 0x11UL
/* Action Record Format 2 */
#define CFA_RESOURCE_TYPE_P4_FORMAT_2_ACTION 0x12UL
/* Action Record Format 3 */
#define CFA_RESOURCE_TYPE_P4_FORMAT_3_ACTION 0x13UL
/* Action Record Format 4 */
#define CFA_RESOURCE_TYPE_P4_FORMAT_4_ACTION 0x14UL
/* L2 Context TCAM */
#define CFA_RESOURCE_TYPE_P4_L2_CTXT_TCAM    0x15UL
/* Profile Func */
#define CFA_RESOURCE_TYPE_P4_PROF_FUNC       0x16UL
/* Profile TCAM */
#define CFA_RESOURCE_TYPE_P4_PROF_TCAM       0x17UL
/* Exact Match Profile Id */
#define CFA_RESOURCE_TYPE_P4_EM_PROF_ID      0x18UL
/* Exact Match Record */
#define CFA_RESOURCE_TYPE_P4_EM_REC          0x19UL
/* Wildcard Profile Id */
#define CFA_RESOURCE_TYPE_P4_WC_TCAM_PROF_ID 0x1aUL
/* Wildcard TCAM */
#define CFA_RESOURCE_TYPE_P4_WC_TCAM         0x1bUL
/* Meter profile */
#define CFA_RESOURCE_TYPE_P4_METER_PROF      0x1cUL
/* Meter */
#define CFA_RESOURCE_TYPE_P4_MIRROR          0x1dUL
/* Source Property TCAM */
#define CFA_RESOURCE_TYPE_P4_SP_TCAM         0x1eUL
#define CFA_RESOURCE_TYPE_P4_LAST           CFA_RESOURCE_TYPE_P4_SP_TCAM


#endif /* _CFA_RESOURCE_TYPES_H_ */
