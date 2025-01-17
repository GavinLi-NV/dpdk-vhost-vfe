/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright (c) 2022 NVIDIA Corporation & Affiliates
 */

#ifndef _VIRTQUEUE_H_
#define _VIRTQUEUE_H_

#include <stdint.h>

#include <rte_atomic.h>
#include <rte_memory.h>
#include <rte_mempool.h>
#include <rte_net.h>

#include "virtio.h"
#include "virtio_ring.h"
#include "virtio_logs.h"

/*
 * Per virtio_ring.h in Linux.
 *     For virtio_pci on SMP, we don't need to order with respect to MMIO
 *     accesses through relaxed memory I/O windows, so thread_fence is
 *     sufficient.
 *
 *     For using virtio to talk to real devices (eg. vDPA) we do need real
 *     barriers.
 */
static inline void
virtio_mb(uint8_t weak_barriers)
{
	if (weak_barriers)
		rte_atomic_thread_fence(__ATOMIC_SEQ_CST);
	else
		rte_mb();
}

static inline void
virtio_rmb(uint8_t weak_barriers)
{
	if (weak_barriers)
		rte_atomic_thread_fence(__ATOMIC_ACQUIRE);
	else
		rte_io_rmb();
}

static inline void
virtio_wmb(uint8_t weak_barriers)
{
	if (weak_barriers)
		rte_atomic_thread_fence(__ATOMIC_RELEASE);
	else
		rte_io_wmb();
}

static inline uint16_t
virtqueue_fetch_flags_packed(struct vring_packed_desc *dp,
			      uint8_t weak_barriers)
{
	uint16_t flags;

	if (weak_barriers) {
/* x86 prefers to using rte_io_rmb over __atomic_load_n as it reports
 * a better perf(~1.5%), which comes from the saved branch by the compiler.
 * The if and else branch are identical  on the platforms except Arm.
 */
#ifdef RTE_ARCH_ARM
		flags = __atomic_load_n(&dp->flags, __ATOMIC_ACQUIRE);
#else
		flags = dp->flags;
		rte_io_rmb();
#endif
	} else {
		flags = dp->flags;
		rte_io_rmb();
	}

	return flags;
}

static inline void
virtqueue_store_flags_packed(struct vring_packed_desc *dp,
			      uint16_t flags, uint8_t weak_barriers)
{
	if (weak_barriers) {
/* x86 prefers to using rte_io_wmb over __atomic_store_n as it reports
 * a better perf(~1.5%), which comes from the saved branch by the compiler.
 * The if and else branch are identical on the platforms except Arm.
 */
#ifdef RTE_ARCH_ARM
		__atomic_store_n(&dp->flags, flags, __ATOMIC_RELEASE);
#else
		rte_io_wmb();
		dp->flags = flags;
#endif
	} else {
		rte_io_wmb();
		dp->flags = flags;
	}
}

#ifdef RTE_PMD_PACKET_PREFETCH
#define rte_packet_prefetch(p)  rte_prefetch1(p)
#else
#define rte_packet_prefetch(p)  do {} while(0)
#endif

#define VIRTQUEUE_MAX_NAME_SZ 32

#define VTNET_SQ_RQ_QUEUE_IDX 0
#define VTNET_SQ_TQ_QUEUE_IDX 1
#define VTNET_SQ_CQ_QUEUE_IDX 2

enum { VTNET_RQ = 0, VTNET_TQ = 1, VTNET_CQ = 2, VTNET_AQ = 3 };
/**
 * The maximum virtqueue size is 2^15. Use that value as the end of
 * descriptor chain terminator since it will never be a valid index
 * in the descriptor table. This is used to verify we are correctly
 * handling vq_free_cnt.
 */
#define VQ_RING_DESC_CHAIN_END 32768

/**
 * Control the RX mode, ie. promiscuous, allmulti, etc...
 * All commands require an "out" sg entry containing a 1 byte
 * state value, zero = disable, non-zero = enable.  Commands
 * 0 and 1 are supported with the VIRTIO_NET_F_CTRL_RX feature.
 * Commands 2-5 are added with VIRTIO_NET_F_CTRL_RX_EXTRA.
 */
#define VIRTIO_NET_CTRL_RX              0
#define VIRTIO_NET_CTRL_RX_PROMISC      0
#define VIRTIO_NET_CTRL_RX_ALLMULTI     1
#define VIRTIO_NET_CTRL_RX_ALLUNI       2
#define VIRTIO_NET_CTRL_RX_NOMULTI      3
#define VIRTIO_NET_CTRL_RX_NOUNI        4
#define VIRTIO_NET_CTRL_RX_NOBCAST      5

/**
 * Control the MAC
 *
 * The MAC filter table is managed by the hypervisor, the guest should
 * assume the size is infinite.  Filtering should be considered
 * non-perfect, ie. based on hypervisor resources, the guest may
 * received packets from sources not specified in the filter list.
 *
 * In addition to the class/cmd header, the TABLE_SET command requires
 * two out scatterlists.  Each contains a 4 byte count of entries followed
 * by a concatenated byte stream of the ETH_ALEN MAC addresses.  The
 * first sg list contains unicast addresses, the second is for multicast.
 * This functionality is present if the VIRTIO_NET_F_CTRL_RX feature
 * is available.
 *
 * The ADDR_SET command requests one out scatterlist, it contains a
 * 6 bytes MAC address. This functionality is present if the
 * VIRTIO_NET_F_CTRL_MAC_ADDR feature is available.
 */
struct virtio_net_ctrl_mac {
	uint32_t entries;
	uint8_t macs[][RTE_ETHER_ADDR_LEN];
} __rte_packed;

#define VIRTIO_NET_CTRL_MAC    1
#define VIRTIO_NET_CTRL_MAC_TABLE_SET        0
#define VIRTIO_NET_CTRL_MAC_ADDR_SET         1

/**
 * Control VLAN filtering
 *
 * The VLAN filter table is controlled via a simple ADD/DEL interface.
 * VLAN IDs not added may be filtered by the hypervisor.  Del is the
 * opposite of add.  Both commands expect an out entry containing a 2
 * byte VLAN ID.  VLAN filtering is available with the
 * VIRTIO_NET_F_CTRL_VLAN feature bit.
 */
#define VIRTIO_NET_CTRL_VLAN     2
#define VIRTIO_NET_CTRL_VLAN_ADD 0
#define VIRTIO_NET_CTRL_VLAN_DEL 1

/**
 * RSS control
 *
 * The RSS feature configuration message is sent by the driver when
 * VIRTIO_NET_F_RSS has been negotiated. It provides the device with
 * hash types to use, hash key and indirection table. In this
 * implementation, the driver only supports fixed key length (40B)
 * and indirection table size (128 entries).
 */
#define VIRTIO_NET_RSS_RETA_SIZE 128
#define VIRTIO_NET_RSS_KEY_SIZE 40

struct virtio_net_ctrl_rss {
	uint32_t hash_types;
	uint16_t indirection_table_mask;
	uint16_t unclassified_queue;
	uint16_t indirection_table[VIRTIO_NET_RSS_RETA_SIZE];
	uint16_t max_tx_vq;
	uint8_t hash_key_length;
	uint8_t hash_key_data[VIRTIO_NET_RSS_KEY_SIZE];
};

/*
 * Control link announce acknowledgment
 *
 * The command VIRTIO_NET_CTRL_ANNOUNCE_ACK is used to indicate that
 * driver has received the notification; device would clear the
 * VIRTIO_NET_S_ANNOUNCE bit in the status field after it receives
 * this command.
 */
#define VIRTIO_NET_CTRL_ANNOUNCE     3
#define VIRTIO_NET_CTRL_ANNOUNCE_ACK 0

struct virtio_net_ctrl_hdr {
	uint8_t class;
	uint8_t cmd;
} __rte_packed;

typedef uint8_t virtio_net_ctrl_ack;

#define VIRTIO_NET_OK     0
#define VIRTIO_NET_ERR    1

#define VIRTIO_MAX_CTRL_DATA 2048

struct virtio_pmd_ctrl {
	struct virtio_net_ctrl_hdr hdr;
	virtio_net_ctrl_ack status;
	uint8_t data[VIRTIO_MAX_CTRL_DATA];
};

struct virtio_admin_ctrl_hdr {
	uint8_t class;
	uint8_t cmd;
} __rte_packed;

typedef uint8_t virtio_admin_ctrl_ack;

#define VIRTIO_MAX_ADMIN_DATA 2048

struct virtio_admin_ctrl {
	struct virtio_admin_ctrl_hdr hdr;
	virtio_admin_ctrl_ack status;
	uint8_t data[0];
};

struct vq_desc_extra {
	void *cookie;
	uint16_t ndescs;
	uint16_t next;
};

#define virtnet_rxq_to_vq(rxvq) container_of(rxvq, struct virtqueue, rxq)
#define virtnet_txq_to_vq(txvq) container_of(txvq, struct virtqueue, txq)
#define virtnet_cq_to_vq(cvq) container_of(cvq, struct virtqueue, cq)
#define virtnet_aq_to_vq(avq) container_of(avq, struct virtqueue, aq)
#define virtnet_get_aq_hdr_addr(avq) (avq->virtio_admin_hdr_mz->addr)

struct virtqueue {
	struct virtio_hw  *hw; /**< virtio_hw structure pointer. */
	union {
		struct {
			/**< vring keeping desc, used and avail */
			struct vring ring;
		} vq_split;

		struct {
			/**< vring keeping descs and events */
			struct vring_packed ring;
			bool used_wrap_counter;
			uint16_t cached_flags; /**< cached flags for descs */
			uint16_t event_flags_shadow;
		} vq_packed;
	};

	uint16_t vq_used_cons_idx; /**< last consumed descriptor */
	uint16_t vq_nentries;  /**< vring desc numbers */
	uint16_t vq_free_cnt;  /**< num of desc available */
	uint16_t vq_avail_idx; /**< sync until needed */
	uint16_t vq_free_thresh; /**< free threshold */

	/**
	 * Head of the free chain in the descriptor table. If
	 * there are no free descriptors, this will be set to
	 * VQ_RING_DESC_CHAIN_END.
	 */
	uint16_t  vq_desc_head_idx;
	uint16_t  vq_desc_tail_idx;
	uint16_t  vq_queue_index;   /**< PCI queue index */

	void *vq_ring_virt_mem;  /**< linear address of vring*/
	unsigned int vq_ring_size;

	struct virtadmin_ctl aq;

	rte_iova_t vq_ring_mem; /**< physical address of vring,
	                         * or virtual address for virtio_user. */
	rte_iova_t vq_avail_mem;
	rte_iova_t vq_used_mem;

	uint16_t  *notify_addr;
	struct vq_desc_extra vq_descx[0];
};

/* If multiqueue is provided by host, then we support it. */
#define VIRTIO_NET_CTRL_MQ   4

#define VIRTIO_NET_CTRL_MQ_VQ_PAIRS_SET        0
#define VIRTIO_NET_CTRL_MQ_RSS_CONFIG          1

#define VIRTIO_NET_CTRL_MQ_VQ_PAIRS_MIN        1
#define VIRTIO_NET_CTRL_MQ_VQ_PAIRS_MAX        0x8000

/**
 * This is the first element of the scatter-gather list.  If you don't
 * specify GSO or CSUM features, you can simply ignore the header.
 */
struct virtio_net_hdr {
#define VIRTIO_NET_HDR_F_NEEDS_CSUM 1    /**< Use csum_start,csum_offset*/
#define VIRTIO_NET_HDR_F_DATA_VALID 2    /**< Checksum is valid */
	uint8_t flags;
#define VIRTIO_NET_HDR_GSO_NONE     0    /**< Not a GSO frame */
#define VIRTIO_NET_HDR_GSO_TCPV4    1    /**< GSO frame, IPv4 TCP (TSO) */
#define VIRTIO_NET_HDR_GSO_UDP      3    /**< GSO frame, IPv4 UDP (UFO) */
#define VIRTIO_NET_HDR_GSO_TCPV6    4    /**< GSO frame, IPv6 TCP */
#define VIRTIO_NET_HDR_GSO_ECN      0x80 /**< TCP has ECN set */
	uint8_t gso_type;
	uint16_t hdr_len;     /**< Ethernet + IP + tcp/udp hdrs */
	uint16_t gso_size;    /**< Bytes to append to hdr_len per frame */
	uint16_t csum_start;  /**< Position to start checksumming from */
	uint16_t csum_offset; /**< Offset after that to place checksum */
};

/**
 * This is the version of the header to use when the MRG_RXBUF
 * feature has been negotiated.
 */
struct virtio_net_hdr_mrg_rxbuf {
	struct   virtio_net_hdr hdr;
	uint16_t num_buffers; /**< Number of merged rx buffers */
};

/* Region reserved to allow for transmit header and indirect ring */
#define VIRTIO_MAX_TX_INDIRECT 8
struct virtio_tx_region {
	struct virtio_net_hdr_mrg_rxbuf tx_hdr;
	union {
		struct vring_desc tx_indir[VIRTIO_MAX_TX_INDIRECT];
		struct vring_packed_desc
			tx_packed_indir[VIRTIO_MAX_TX_INDIRECT];
	} __rte_aligned(16);
};

static inline int
desc_is_used(struct vring_packed_desc *desc, struct virtqueue *vq)
{
	uint16_t used, avail, flags;

	flags = virtqueue_fetch_flags_packed(desc, vq->hw->weak_barriers);
	used = !!(flags & VRING_PACKED_DESC_F_USED);
	avail = !!(flags & VRING_PACKED_DESC_F_AVAIL);

	return avail == used && used == vq->vq_packed.used_wrap_counter;
}

static inline void
vring_desc_init_packed(struct virtqueue *vq, int n)
{
	int i;

	for (i = 0; i < n - 1; i++) {
		vq->vq_packed.ring.desc[i].id = i;
		vq->vq_descx[i].next = i + 1;
	}
	vq->vq_packed.ring.desc[i].id = i;
	vq->vq_descx[i].next = VQ_RING_DESC_CHAIN_END;
}

/* Chain all the descriptors in the ring with an END */
static inline void
vring_desc_init_split(struct vring_desc *dp, uint16_t n)
{
	uint16_t i;

	for (i = 0; i < n - 1; i++)
		dp[i].next = (uint16_t)(i + 1);
	dp[i].next = VQ_RING_DESC_CHAIN_END;
}

static inline void
vring_desc_init_indirect_packed(struct vring_packed_desc *dp, int n)
{
	int i;

	for (i = 0; i < n; i++) {
		dp[i].id = (uint16_t)i;
		dp[i].flags = VRING_DESC_F_WRITE;
	}
}

/**
 * Tell the backend not to interrupt us. Implementation for packed virtqueues.
 */
static inline void
virtqueue_disable_intr_packed(struct virtqueue *vq)
{
	if (vq->vq_packed.event_flags_shadow != RING_EVENT_FLAGS_DISABLE) {
		vq->vq_packed.event_flags_shadow = RING_EVENT_FLAGS_DISABLE;
		vq->vq_packed.ring.driver->desc_event_flags =
			vq->vq_packed.event_flags_shadow;
	}
}

/**
 * Tell the backend not to interrupt us. Implementation for split virtqueues.
 */
static inline void
virtqueue_disable_intr_split(struct virtqueue *vq)
{
	vq->vq_split.ring.avail->flags |= VRING_AVAIL_F_NO_INTERRUPT;
}

/**
 * Tell the backend not to interrupt us.
 */
static inline void
virtqueue_disable_intr(struct virtqueue *vq)
{
	if (virtio_with_packed_queue(vq->hw))
		virtqueue_disable_intr_packed(vq);
	else
		virtqueue_disable_intr_split(vq);
}

/**
 * Tell the backend to interrupt. Implementation for packed virtqueues.
 */
static inline void
virtqueue_enable_intr_packed(struct virtqueue *vq)
{
	if (vq->vq_packed.event_flags_shadow == RING_EVENT_FLAGS_DISABLE) {
		vq->vq_packed.event_flags_shadow = RING_EVENT_FLAGS_ENABLE;
		vq->vq_packed.ring.driver->desc_event_flags =
			vq->vq_packed.event_flags_shadow;
	}
}

/**
 * Tell the backend to interrupt. Implementation for split virtqueues.
 */
static inline void
virtqueue_enable_intr_split(struct virtqueue *vq)
{
	vq->vq_split.ring.avail->flags &= (~VRING_AVAIL_F_NO_INTERRUPT);
}

/**
 * Tell the backend to interrupt us.
 */
static inline void
virtqueue_enable_intr(struct virtqueue *vq)
{
	if (virtio_with_packed_queue(vq->hw))
		virtqueue_enable_intr_packed(vq);
	else
		virtqueue_enable_intr_split(vq);
}

/**
 *  Dump virtqueue internal structures, for debug purpose only.
 */
void virtqueue_dump(struct virtqueue *vq);

/* Flush the elements in the used ring. */
void virtqueue_rxvq_flush(struct virtqueue *vq);

int virtqueue_rxvq_reset_packed(struct virtqueue *vq);

int virtqueue_txvq_reset_packed(struct virtqueue *vq);

static inline int
virtqueue_full(const struct virtqueue *vq)
{
	return vq->vq_free_cnt == 0;
}

static inline int
virtio_get_queue_type(struct virtio_hw *hw, uint16_t vq_idx)
{
	if (vq_idx == hw->max_queue_pairs * 2)
		return VTNET_CQ;
	else if (vq_idx % 2 == 0)
		return VTNET_RQ;
	else
		return VTNET_TQ;
}

/* virtqueue_nused has load-acquire or rte_io_rmb insed */
static inline uint16_t
virtqueue_nused(const struct virtqueue *vq)
{
	uint16_t idx;

	if (vq->hw->weak_barriers) {
	/**
	 * x86 prefers to using rte_smp_rmb over __atomic_load_n as it
	 * reports a slightly better perf, which comes from the saved
	 * branch by the compiler.
	 * The if and else branches are identical with the smp and io
	 * barriers both defined as compiler barriers on x86.
	 */
#ifdef RTE_ARCH_X86_64
		idx = vq->vq_split.ring.used->idx;
		rte_smp_rmb();
#else
		idx = __atomic_load_n(&(vq)->vq_split.ring.used->idx,
				__ATOMIC_ACQUIRE);
#endif
	} else {
		idx = vq->vq_split.ring.used->idx;
		rte_io_rmb();
	}
	return idx - vq->vq_used_cons_idx;
}

void vq_ring_free_chain(struct virtqueue *vq, uint16_t desc_idx);
void vq_ring_free_chain_packed(struct virtqueue *vq, uint16_t used_idx);
void vq_ring_free_inorder(struct virtqueue *vq, uint16_t desc_idx,
			  uint16_t num);

static inline void
vq_update_avail_idx(struct virtqueue *vq)
{
	if (vq->hw->weak_barriers) {
	/* x86 prefers to using rte_smp_wmb over __atomic_store_n as
	 * it reports a slightly better perf, which comes from the
	 * saved branch by the compiler.
	 * The if and else branches are identical with the smp and
	 * io barriers both defined as compiler barriers on x86.
	 */
#ifdef RTE_ARCH_X86_64
		rte_smp_wmb();
		vq->vq_split.ring.avail->idx = vq->vq_avail_idx;
#else
		__atomic_store_n(&vq->vq_split.ring.avail->idx,
				 vq->vq_avail_idx, __ATOMIC_RELEASE);
#endif
	} else {
		rte_io_wmb();
		vq->vq_split.ring.avail->idx = vq->vq_avail_idx;
	}
}

static inline void
vq_update_avail_ring(struct virtqueue *vq, uint16_t desc_idx)
{
	uint16_t avail_idx;
	/*
	 * Place the head of the descriptor chain into the next slot and make
	 * it usable to the host. The chain is made available now rather than
	 * deferring to virtqueue_notify() in the hopes that if the host is
	 * currently running on another CPU, we can keep it processing the new
	 * descriptor.
	 */
	avail_idx = (uint16_t)(vq->vq_avail_idx & (vq->vq_nentries - 1));
	if (unlikely(vq->vq_split.ring.avail->ring[avail_idx] != desc_idx))
		vq->vq_split.ring.avail->ring[avail_idx] = desc_idx;
	vq->vq_avail_idx++;
}

static inline int
virtqueue_kick_prepare(struct virtqueue *vq)
{
	/*
	 * Ensure updated avail->idx is visible to vhost before reading
	 * the used->flags.
	 */
	virtio_mb(vq->hw->weak_barriers);
	return !(vq->vq_split.ring.used->flags & VRING_USED_F_NO_NOTIFY);
}

static inline int
virtqueue_kick_prepare_packed(struct virtqueue *vq)
{
	uint16_t flags;

	/*
	 * Ensure updated data is visible to vhost before reading the flags.
	 */
	virtio_mb(vq->hw->weak_barriers);
	flags = vq->vq_packed.ring.device->desc_event_flags;

	return flags != RING_EVENT_FLAGS_DISABLE;
}

/*
 * virtqueue_kick_prepare*() or the virtio_wmb() should be called
 * before this function to be sure that all the data is visible to vhost.
 */
static inline void
virtqueue_notify(struct virtqueue *vq)
{
	VIRTIO_OPS(vq->hw)->notify_queue(vq->hw, vq);
}

#endif /* _VIRTQUEUE_H_ */
