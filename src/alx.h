/*
 * Copyright (c) 2010 - 2011 Atheros Communications Inc.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _ALX_H_
#define _ALX_H_

#include "alx_compat.h"
#include "alx_sw.h"

/*
 * Definition to enable some features
 */
#undef CONFIG_ALX_MSIX
#undef CONFIG_ALX_MSI
#undef CONFIG_ALX_MTQ
#undef CONFIG_ALX_MRQ
#undef CONFIG_ALX_RSS
/* #define CONFIG_ALX_MSIX */
#define CONFIG_ALX_MSI
#define CONFIG_ALX_MTQ
#define CONFIG_ALX_MRQ
#ifdef CONFIG_ALX_MRQ
#define CONFIG_ALX_RSS
#endif

/* just for kernel 2.6 and up */
/* #define CONFIG_ALX_DIAG */
#ifdef CONFIG_ALX_DIAG
#define CONFIG_ALX_IOPORT
#endif

/*
 * Definition for validate HW
 */
#define ALX_VALID_MTQ 0
#define ALX_VALID_RSS 0
#if ALX_VALID_RSS
#define ALX_DUMP_RSS_DESC 1
#else
#define ALX_DUMP_RSS_DESC 0
#endif

/*
 * Definition for Dumping msg
 */
/* TPD, RRD and RFD Description */
#define ALX_DUMP_RRD_DESC	0
#define ALX_DUMP_RFD_DESC	0
#define ALX_DUMP_TPD_DESC	0

#define ALX_MSG_DEFAULT		0


/* Logging functions and macros */
#define alx_err(_adpt, _format, ...)	\
	alx_printk_always(_adpt, ERR, _format, ##__VA_ARGS__)

#define alx_netif_info(_adpt, _mlevel, _format, ...) \
	alx_printk(_adpt, _mlevel, INFO, _format, ##__VA_ARGS__)

#define alx_netif_warn(_adpt, _mlevel, _format, ...) \
	alx_printk(_adpt, _mlevel, WARNING, _format, ##__VA_ARGS__)

#define alx_netif_dbg(_adpt, _mlevel, _format, ...) \
	alx_printk(_adpt, _mlevel, DEBUG, _format, ##__VA_ARGS__)


#define alx_printk(_adpt, _mlevel, _klevel, _format, ...)		\
	do {								\
		if (_adpt->msg_enable & NETIF_MSG_##_mlevel)		\
			printk(KERN_##_klevel "alx: %s: %s: " _format,	\
				_adpt->netdev->name,			\
				__func__ , ##__VA_ARGS__);		\
	} while (0)


#define alx_printk_always(_adpt, _klevel, _format, ...)			\
	do {								\
		printk(KERN_##_klevel "alx: %s: %s: " _format,		\
			_adpt->netdev->name, __func__ , ##__VA_ARGS__); \
	} while (0)

/*
 * Definitions for ioctl
 *
 * redefine them as alx ioctl vector of our own
 */
#define SIOCDEVEXTCOMMAND  0x89F0 /* command of device */
struct ext_command_buf {
	void  *addr;
	__u32 size;
};

struct ext_command_dat {
	__u32 val0;
	__u32 val1;
};

struct ext_command_mac {
	__u32  num;
	union {
		__u32  val32;
		__u16  val16;
		__u8   val8;
	};
};

struct ext_command_mii {
	__u16  dev;
	__u16  num;
	__u16  val;
};

struct ext_command_rss {
	__u32  num;
	__u32  val;
};

struct ext_ioctl_data {
	__u32	cmd_type;
	union {
		struct ext_command_buf  cmdu_buf;
		struct ext_command_dat  cmdu_dat;
		struct ext_command_mac  cmdu_mac;
		struct ext_command_mii  cmdu_mii;
		struct ext_command_rss  cmdu_rss;
	} cmd_cmdu;
};

#define cmd_buf   cmd_cmdu.cmdu_buf
#define cmd_dat   cmd_cmdu.cmdu_dat
#define cmd_mac   cmd_cmdu.cmdu_mac
#define cmd_mii   cmd_cmdu.cmdu_mii
#define cmd_rss   cmd_cmdu.cmdu_rss

#define ALX_IOCTL_EXT_DEVICE_INACTIVE	0x1
#define ALX_IOCTL_EXT_DEVICE_RESET	0x2

#define ALX_IOCTL_EXT_GMAC_REG_32	0x3
#define ALX_IOCTL_EXT_SMAC_REG_32	0x4
#define ALX_IOCTL_EXT_GMAC_REG_16	0x5
#define ALX_IOCTL_EXT_SMAC_REG_16	0x6
#define ALX_IOCTL_EXT_GMAC_REG_8	0x7
#define ALX_IOCTL_EXT_SMAC_REG_8	0x8

#define ALX_IOCTL_EXT_GMAC_CFG_32	0x9
#define ALX_IOCTL_EXT_SMAC_CFG_32	0x10
#define ALX_IOCTL_EXT_GMAC_IO_32	0x11
#define ALX_IOCTL_EXT_SMAC_IO_32	0x12

#define ALX_IOCTL_EXT_GMII_EXT_REG	0x13
#define ALX_IOCTL_EXT_SMII_EXT_REG	0x14

#define ALX_IOCTL_EXT_GRSS_KEY_32	0x15
#define ALX_IOCTL_EXT_SRSS_KEY_32	0x16
#define ALX_IOCTL_EXT_GRSS_TAB_32	0x17
#define ALX_IOCTL_EXT_SRSS_TAB_32	0x18
#define ALX_IOCTL_EXT_RSS_UPDATE	0x19

#define ALX_IOCTL_EXT_DIAG_BEGIN	0x20
#define ALX_IOCTL_EXT_DIAG_END		0x21
#define ALX_IOCTL_EXT_TX_PKTS		0x22
#define ALX_IOCTL_EXT_RX_PKTS		0x23
/*
 * Diag tool support
 */
#ifdef CONFIG_ALX_DIAG

#define ALX_DIAG_MAX_PACKET_BUFS	1

#define ALX_DIAG_MAX_DATA_BUFFER	(48 * 64 * 1024)
#define ALX_DIAG_MAX_TX_PACKETS		64
#define ALX_DIAG_MAX_RX_PACKETS		512

struct alx_diag_buf {
	u8	*addr;
	u32	offset;
	u32	length;
};

struct alx_diag_packet {
	struct alx_diag_packet  *next;
	u32			length;  /* total length of the packet(buf) */
	u32			type;    /* packet type, vlan, ip checksum */
	struct alx_diag_buf	buf[ALX_DIAG_MAX_PACKET_BUFS];
	struct alx_diag_buf	sglist[ALX_DIAG_MAX_PACKET_BUFS];
	u16			vlanid;
	u16			mss;
	u32			hash;
	u16			cpu_num;
	u16			xsum;        /* rx, ip-payload checksum */
	u16			csum_start;  /* custom checksum offset to the
					      * mac-header */
	u16			csum_pos;    /* custom checksom position
					      * (to the mac_header) */
	u32			uplevel_reserved[4];
	void			*lowlevel_reserved[4];
};
#define ALX_DIAG_PKTYPE_IPXSUM		0x00000001L /* ip checksum offload,
						     * TO:task offload */
#define ALX_DIAG_PKTYPE_L4XSUM		0x00000002L /* tcp/udp checksum
						     * offload */
#define ALX_DIAG_PKTYPE_VLANINST	0x00000004L /* insert vlan tag */
#define ALX_DIAG_PKTYPE_TSOV1		0x00000008L /* tcp large send v1 */
#define ALX_DIAG_PKTYPE_TSOV2		0x00000010L /* tcp large send v2 */
#define ALX_DIAG_PKTYPE_CXSUM		0x00000020L /* checksum offload */
#define ALX_DIAG_PKTYPE_VLANTAGGED	0x00000040L /* vlan tag */
#define ALX_DIAG_PKTYPE_IPV4		0x00000080L /* ipv4 */
#define ALX_DIAG_PKTYPE_IPV6		0x00000100L /* ipv6 */
#define ALX_DIAG_PKTYPE_TCP		0x00000200L /* tcp */
#define ALX_DIAG_PKTYPE_UDP		0x00000400L /* udp */
#define ALX_DIAG_PKTYPE_EII		0x00000800L /* ethernet II */
#define ALX_DIAG_PKTYPE_802_3		0x00001000L /* 802.3 */
#define ALX_DIAG_PKTYPE_SNAP		0x00002000L /* 802.2/snap */
#define ALX_DIAG_PKTYPE_FRAGMENT	0x00004000L /* fragment ip packet */
#define ALX_DIAG_PKTYPE_SGLIST_VALID	0x00008000L /* SGList valid */
#define ALX_DIAG_PKTYPE_HASH_VLAID	0x00010000L /* Hash valid */
#define ALX_DIAG_PKTYPE_CPUNUM_VALID	0x00020000L /* CpuNum valid */
#define ALX_DIAG_PKTYPE_XSUM_VALID	0x00040000L
#define ALX_DIAG_PKTYPE_IPXSUM_ERR	0x00080000L
#define ALX_DIAG_PKTYPE_L4XSUM_ERR	0x00100000L
#define ALX_DIAG_PKTYPE_802_3_LEN_ERR	0x00200000L
#define ALX_DIAG_PKTYPE_INCOMPLETE_ERR	0x00400000L
#define ALX_DIAG_PKTYPE_CRC_ERR		0x00800000L
#define ALX_DIAG_PKTYPE_RX_ERR		0x01000000L
#define ALX_DIAG_PKTYPE_PTP		0x02000000L /* 1588 PTP */
#define ALX_DIAG_PKTYPE_LLDP		0x04000000L /* IEEE LLDP */
#endif

#define ALX_VLAN_TO_TAG(_vlan, _tag)	\
	_tag =  ((((_vlan) >> 8) & 0xFF) | (((_vlan) & 0xFF) << 8))

#define ALX_TAG_TO_VLAN(_tag, _vlan)	\
	_vlan = ((((_tag) >> 8) & 0xFF) | (((_tag) & 0xFF) << 8))

/* Coalescing Message Block */
struct coals_msg_block {
	int test;
};


#define BAR_0   0
#define BAR_1   1
#define BAR_2   2

#define ALX_DEF_RX_BUF_SIZE	1536
#define ALX_MAX_JUMBO_PKT_SIZE	(9*1024)
#define ALX_MAX_TSO_PKT_SIZE	(7*1024)

#define ALX_MAX_ETH_FRAME_SIZE	ALX_MAX_JUMBO_PKT_SIZE
#define ALX_MIN_ETH_FRAME_SIZE	68


#define ALX_MAX_RX_QUEUES	8
#define ALX_MAX_TX_QUEUES	4
#define ALX_MAX_HANDLED_INTRS	5

#define ALX_WATCHDOG_TIME   (5 * HZ)

struct alx_cmb {
	char name[IFNAMSIZ + 9];
	void *cmb;
	dma_addr_t dma;
};
struct alx_smb {
	char name[IFNAMSIZ + 9];
	void *smb;
	dma_addr_t dma;
};


/*
 * RRD : definition
 */
struct alx_rrdes_general {
	u32 xsum:16;
	u32 nor:4;  /* number of RFD */
	u32 si:12;  /* start index of rfd-ring */

	u32 hash;

	u32 vlan_tag:16; /* vlan-tag */
	u32 pid:8;       /* Header Length of Header-Data Split. WORD unit */
	u32 reserve0:1;
	u32 rss_cpu:3;   /* CPU number used by RSS */
#if 0
	u32 rss_t6:1;	/* TCP(IPv6) flag for RSS hash algrithm */
	u32 rss_i6:1;	/* IPv6 flag for RSS hash algrithm */
	u32 rss_t4:1;	/* TCP(IPv4)  flag for RSS hash algrithm */
	u32 rss_i4:1;	/* IPv4 flag for RSS hash algrithm */
#endif
	u32 rss_flag:4;

	u32 pkt_len:14; /* length of the packet */
	u32 l4f:1;      /* L4(TCP/UDP) checksum failed */
	u32 ipf:1;      /* IP checksum failed */
	u32 vlan_flag:1;/* vlan tag */
	u32 reserve:3;
	u32 res:1;      /* received error summary */
	u32 crc:1;      /* crc error */
	u32 fae:1;      /* frame alignment error */
	u32 trunc:1;    /* truncated packet, larger than MTU */
	u32 runt:1;     /* runt packet */
	u32 icmp:1;     /* incomplete packet,
			 * due to insufficient rx-descriptor
			 */
	u32 bar:1;      /* broadcast address received */
	u32 mar:1;      /* multicast address received */
	u32 type:1;     /* ethernet type */
	u32 fov:1;      /* fifo overflow*/
	u32 lene:1;     /* length error */
	u32 update:1;   /* update*/
};

struct alx_rrdesc {
	union {
		struct alx_rrdes_general gnr;
		/* flat format */
		union {
			struct {
				u32 dw0;
				u32 dw1;
				u32 dw2;
				u32 dw3;
			} d;
			struct {
				u64 qw0;
				u64 qw1;
			} q;
		} fmt;
	} rr_desc;
};
#define rr_dw0	rr_desc.fmt.d.dw0
#define rr_dw1	rr_desc.fmt.d.dw1
#define rr_dw2	rr_desc.fmt.d.dw2
#define rr_dw3	rr_desc.fmt.d.dw3
#define rr_gnr	rr_desc.gnr

/*
 * RFD : definition
 */

/* RFD desciptor */
struct alx_rfdes_general {
	u64   addr;
};

struct alx_rfdesc {
	union {
		struct alx_rfdes_general gnr;
		/* flat format */
		union {
			struct {
				u32 dw0;
				u32 dw1;
			} d;
			struct {
				u64 qw0;
			} q;
		} fmt;
	} rf_desc;
};
#define rf_dw0	rf_desc.fmt.d.dw0
#define rf_dw1	rf_desc.fmt.d.dw1
#define rf_qw0	rf_desc.fmt.q.qw0
#define rf_gnr	rf_desc.gnr

/*
 * TPD : definition
 */

/* tpd - general parameter format */
struct alx_tpdes_general {
	u32  buffer_len:16; /* include 4-byte CRC */
	u32  vlan_tag:16;

	u32  l4hdr_offset:8; /* tcp/udp header offset to the 1st byte of
			      * the packet
			      */
	u32  c_csum:1;   /* must be 0 in this format */
	u32  ip_csum:1;  /* do ip(v4) header checksum offload */
	u32  tcp_csum:1; /* do tcp checksum offload, both ipv4 and ipv6 */
	u32  udp_csum:1; /* do udp checksum offlaod, both ipv4 and ipv6 */
	u32  lso:1;
	u32  lso_v2:1;  /* must be 0 in this format */
	u32  vtagged:1; /* vlan-id tagged already */
	u32  instag:1;  /* insert vlan tag */

	u32  ipv4:1;    /* ipv4 packet */
	u32  type:1;    /* type of packet (ethernet_ii(1) or snap(0)) */
	u32  reserve:12; /* reserved, must be 0 */
	u32  epad:1;     /* even byte padding when this packet */
	u32  last_frag:1; /* last fragment(buffer) of the packet */

	u64 addr;
};

/* tpd - custom checksum parameter format */
struct alx_tpdes_checksum {
	u32 buffer_len:16; /* include 4-byte CRC */
	u32 vlan_tag:16;

	u32 payld_offset:8; /* payload offset to the 1st byte of
			     *  the packet
			     */
	u32 c_sum:1;  /* do custom chekcusm offload,
		       * must be 1 in this format
		       */
	u32 ip_sum:1;   /* must be 0 in thhis format */
	u32 tcp_sum:1;  /* must be 0 in this format */
	u32 udp_sum:1;  /* must be 0 in this format */
	u32 lso:1;      /* must be 0 in this format */
	u32 lso_v2:1;   /* must be 0 in this format */
	u32 vtagged:1;  /* vlan-id tagged already */
	u32 instag:1;   /* insert vlan tag */

	u32 ipv4:1;     /* ipv4 packet */
	u32 type:1;     /* type of packet (ethernet_ii(1) or snap(0)) */
	u32 cxsum_offset:8;  /* checksum offset to the 1st byte of
			      * the packet
			      */
	u32 reserve:4;  /* reserved, must be 0 */
	u32 epad:1;     /* even byte padding when this packet */
	u32 last_frag:1; /* last fragment(buffer) of the packet */

	u64 addr;
};


/* tpd - tcp large send format (v1/v2) */
struct alx_tpdes_tso {
	u32 buffer_len:16; /* include 4-byte CRC */
	u32 vlan_tag:16;

	u32 tcphdr_offset:8; /* tcp hdr offset to the 1st byte of packet */
	u32 c_sum:1;   /* must be 0 in this format */
	u32 ip_sum:1;  /* must be 0 in thhis format */
	u32 tcp_sum:1; /* must be 0 in this format */
	u32 udp_sum:1; /* must be 0 in this format */
	u32 lso:1;     /* do tcp large send (ipv4 only) */
	u32 lso_v2:1;  /* must be 0 in this format */
	u32 vtagged:1; /* vlan-id tagged already */
	u32 instag:1;  /* insert vlan tag */

	u32 ipv4:1;    /* ipv4 packet */
	u32 type:1;    /* type of packet (ethernet_ii(1) or snap(0)) */
	u32 mss:13;    /* MSS if do tcp large send */
	u32 last_frag:1; /* last fragment(buffer) of the packet */

	u32 addr_lo;
	u32 addr_hi;
};

struct alx_tpdesc {
	union {
		struct alx_tpdes_general   gnr;
		struct alx_tpdes_checksum  sum;
		struct alx_tpdes_tso       tso;
		/* flat format */
		union {
			struct {
				u32 dw0;
				u32 dw1;
				u32 dw2;
				u32 dw3;
			} d;
			struct {
				u64 qw0;
				u64 qw1;
			} q;
		} fmt;
	} tp_desc;
};
#define tp_dw0	tp_desc.fmt.d.dw0
#define tp_dw1	tp_desc.fmt.d.dw1
#define tp_dw2	tp_desc.fmt.d.dw2
#define tp_dw3	tp_desc.fmt.d.dw3
#define tp_qw0	tp_desc.fmt.q.qw0
#define tp_qw1	tp_desc.fmt.q.qw1
#define tp_gnr	tp_desc.gnr
#define tp_sum	tp_desc.sum
#define tp_tso	tp_desc.tso


#define ALX_RRD(_que, _i)	\
		(&(((struct alx_rrdesc *)(_que)->rrq.rrdesc)[(_i)]))
#define ALX_RFD(_que, _i)	\
		(&(((struct alx_rfdesc *)(_que)->rfq.rfdesc)[(_i)]))
#define ALX_TPD(_que, _i)	\
		(&(((struct alx_tpdesc *)(_que)->tpq.tpdesc)[(_i)]))


/*
 * alx_ring_header represents a single, contiguous block of DMA space
 * mapped for the three descriptor rings (tpd, rfd, rrd) and the two
 * message blocks (cmb, smb) described below
 */
struct alx_ring_header {
	void *desc;             /* virtual address */
	dma_addr_t dma;         /* physical address*/
	unsigned int size;      /* length in bytes */
	unsigned int used;
};


/*
 * alx_buffer is wrapper around a pointer to a socket buffer
 * so a DMA handle can be stored along with the skb
 */
struct alx_buffer {
	struct sk_buff *skb;    /* socket buffer */
	u16 length;             /* rx buffer length */
	dma_addr_t dma;
};

struct alx_sw_buffer {
	struct sk_buff *skb;    /* socket buffer */

	u32 vlan_tag:16;
	u32 vlan_flag:1;
	u32 reserved:15;
};

/* receive free descriptor (rfd) queue */
struct alx_rfd_queue {
	struct alx_buffer *rfbuff;
	struct alx_rfdesc *rfdesc;	/* virtual address */
	dma_addr_t rfdma;	/* physical address */
	u16 size;	/* length in bytes */
	u16 count;	/* number of descriptors in the ring */

	u16 produce_idx; /* it's written to rxque->produce_reg */
	u16 consume_idx; /* unused*/
};

/* receive return desciptor (rrd) queue */
struct alx_rrd_queue {
	struct alx_rrdesc *rrdesc;	/* virtual address */
	dma_addr_t rrdma;	/* physical address */
	u16 size;	/* length in bytes */
	u16 count;	/* number of descriptors in the ring */

	u16 produce_idx; /* unused */
	u16 consume_idx; /* rxque->consume_reg */
};

/* software desciptor (swd) queue */
struct alx_swd_queue {
	struct alx_sw_buffer *swbuff;
	u16 count;	/* number of descriptors in the ring */
	u16 produce_idx;
	u16 consume_idx;
};

/* rx queue */
struct alx_rx_queue {
	struct device *dev;	/* device for dma mapping */
	struct net_device *netdev;	/* netdev ring belongs to */
	struct alx_msix_param *msix;

	struct alx_rrd_queue rrq;
	struct alx_rfd_queue rfq;
	struct alx_swd_queue swq;


	u16 que_idx;		/* index in multi rx queues*/
	u16 max_packets;		/* max work per interrupt */

	u16 produce_reg;
	u16 consume_reg;
	u32 flags;
};
#define ALX_RX_FLAG_SW_QUE    BIT_0
#define ALX_RX_FLAG_HW_QUE    BIT_1
#define CHK_RX_FLAG(_flag)    CHK_FLAG(rxque, RX, _flag)
#define SET_RX_FLAG(_flag)    SET_FLAG(rxque, RX, _flag)
#define CLI_RX_FLAG(_flag)    CLI_FLAG(rxque, RX, _flag)

#define GET_RF_BUFFER(_rque, _i)    (&((_rque)->rfq.rfbuff[(_i)]))
#define GET_SW_BUFFER(_rque, _i)    (&((_rque)->swq.swbuff[(_i)]))


/* transimit packet descriptor (tpd) ring */
struct alx_tpd_queue {
	struct alx_buffer *tpbuff;
	struct alx_tpdesc *tpdesc;	/* virtual address */
	dma_addr_t tpdma;	/* physical address */
	u16 size;	/* length in bytes */
	u16 count;	/* number of descriptors in the ring */

	u16 produce_idx;
	u16 consume_idx;
	u16 last_produce_idx;
};

/* tx queue */
struct alx_tx_queue {
	struct device *dev;	/* device for dma mapping */
	struct net_device *netdev;	/* netdev ring belongs to */

	struct alx_tpd_queue tpq;
	struct alx_msix_param *msix;

	u16 que_idx;     /* needed for multiqueue queue management */
	u16 max_packets; /* max packets per interrupt */

	u16 produce_reg;
	u16 consume_reg;
};
#define GET_TP_BUFFER(_tque, _i)    (&((_tque)->tpq.tpbuff[(_i)]))


/*
 * definition for array allocations.
 */
#define ALX_MAX_MSIX_INTRS	16
#define ALX_MAX_RX_QUEUES	8
#define ALX_MAX_TX_QUEUES	4

enum alx_msix_type {
	alx_msix_type_rx,
	alx_msix_type_tx,
	alx_msix_type_other,
};
#define ALX_MSIX_TYPE_OTH_TIMER		0
#define ALX_MSIX_TYPE_OTH_ALERT		1
#define ALX_MSIX_TYPE_OTH_SMB		2
#define ALX_MSIX_TYPE_OTH_PHY		3

/* ALX_MAX_MSIX_INTRS of these are allocated,
 * but we only use one per queue-specific vector.
 */
struct alx_msix_param {
	struct alx_adapter *adpt;
	unsigned int vec_idx; /* index in HW interrupt vector */
	char name[IFNAMSIZ + 9];

	/* msix interrupts for queue */
	u8 rx_map[ALX_MAX_RX_QUEUES];
	u8 tx_map[ALX_MAX_TX_QUEUES];
	u8 rx_count;     /* Rx ring count assigned to this vector */
	u8 tx_count;     /* Tx ring count assigned to this vector */

#ifdef CONFIG_ALX_NAPI
	struct napi_struct napi;
#endif
#ifndef HAVE_NETDEV_NAPI_LIST
	struct net_device poll_dev;
#endif
#ifdef HAVE_IRQ_AFFINITY_HINT
	cpumask_var_t affinity_mask;
#endif
	u32 flags;
};

#define ALX_MSIX_FLAG_RX0	BIT_0
#define ALX_MSIX_FLAG_RX1	BIT_1
#define ALX_MSIX_FLAG_RX2	BIT_2
#define ALX_MSIX_FLAG_RX3	BIT_3
#define ALX_MSIX_FLAG_RX4	BIT_4
#define ALX_MSIX_FLAG_RX5	BIT_5
#define ALX_MSIX_FLAG_RX6	BIT_6
#define ALX_MSIX_FLAG_RX7	BIT_7
#define ALX_MSIX_FLAG_TX0	BIT_8
#define ALX_MSIX_FLAG_TX1	BIT_9
#define ALX_MSIX_FLAG_TX2	BIT_10
#define ALX_MSIX_FLAG_TX3	BIT_11
#define ALX_MSIX_FLAG_TIMER	BIT_12
#define ALX_MSIX_FLAG_ALERT	BIT_13
#define ALX_MSIX_FLAG_SMB	BIT_14
#define ALX_MSIX_FLAG_PHY	BIT_15

#define ALX_MSIX_FLAG_RXS		(\
		ALX_MSIX_FLAG_RX0	|\
		ALX_MSIX_FLAG_RX1	|\
		ALX_MSIX_FLAG_RX2	|\
		ALX_MSIX_FLAG_RX3	|\
		ALX_MSIX_FLAG_RX4	|\
		ALX_MSIX_FLAG_RX5	|\
		ALX_MSIX_FLAG_RX6	|\
		ALX_MSIX_FLAG_RX7)
#define ALX_MSIX_FLAG_TXS		(\
		ALX_MSIX_FLAG_TX0	|\
		ALX_MSIX_FLAG_TX1	|\
		ALX_MSIX_FLAG_TX2	|\
		ALX_MSIX_FLAG_TX3)
#define ALX_MSIX_FLAG_ALL		(\
		ALX_MSIX_FLAG_RXS	|\
		ALX_MSIX_FLAG_TXS	|\
		ALX_MSIX_FLAG_TIMER	|\
		ALX_MSIX_FLAG_ALERT	|\
		ALX_MSIX_FLAG_SMB	|\
		ALX_MSIX_FLAG_PHY)

#define CHK_MSIX_FLAG(_flag)	CHK_FLAG(msix, MSIX, _flag)
#define SET_MSIX_FLAG(_flag)	SET_FLAG(msix, MSIX, _flag)
#define CLI_MSIX_FLAG(_flag)	CLI_FLAG(msix, MSIX, _flag)

/*
 *board specific private data structure
 */
struct alx_adapter {
	struct net_device *netdev;
	struct pci_dev *pdev;
	struct net_device_stats net_stats;
	bool netdev_registered;

#ifdef NETIF_F_HW_VLAN_TX
	struct vlan_group   *vlgrp;
#endif
	u16 bd_number;    /* board number;*/

	struct alx_msix_param *msix[ALX_MAX_MSIX_INTRS];
	struct msix_entry *msix_entries;
	int num_msix_rxques;
	int num_msix_txques;
	int num_msix_noques;    /* true count of msix_noques for device */
	int num_msix_intrs;

	int min_msix_intrs;
	int max_msix_intrs;

	/* All Descriptor memory */
	struct alx_ring_header ring_header;

	/* TX */
	struct alx_tx_queue *tx_queue[ALX_MAX_TX_QUEUES];
	/* RX */
	struct alx_rx_queue *rx_queue[ALX_MAX_RX_QUEUES];

	u16  num_txques;
	u16  num_rxques; /* equal max(num_hw_rxques, num_sw_rxques) */
	u16  num_hw_rxques;
	u16  num_sw_rxques;

	u16  max_rxques;
	u16  max_txques;

	u16  num_txdescs;
	u16  num_rxdescs;

	u32  rxbuf_size;

	struct alx_cmb cmb;
	struct alx_smb smb;

	/* structs defined in alx_hw.h */
	struct alx_hw       hw;
	struct alx_hw_stats hw_stats;
#ifdef CONFIG_ALX_DIAG
	u8			*diag_recv_buf;
	u8			*diag_send_buf;
	u8			*diag_info_buf;
	struct alx_diag_packet  *diag_pkt_info;
	u32			diag_recv_size;
	u32			diag_send_size;
	u32			diag_info_size;
	struct sk_buff_head	diag_skb_list;
#endif

	u32 *config_space;

	struct work_struct alx_task;
	struct timer_list  alx_timer;

	unsigned long link_jiffies;

	u32 wol;
	spinlock_t tx_lock;
	spinlock_t rx_lock;
	atomic_t irq_sem;

	u16 msg_enable;
	unsigned long flags[2];
};

#define ALX_ADPT_FLAG_0_MSI_CAP			BIT_0
#define ALX_ADPT_FLAG_0_MSI_EN			BIT_1
#define ALX_ADPT_FLAG_0_MSIX_CAP		BIT_2
#define ALX_ADPT_FLAG_0_MSIX_EN			BIT_3
#define ALX_ADPT_FLAG_0_MRQ_CAP			BIT_4
#define ALX_ADPT_FLAG_0_MRQ_EN			BIT_5
#define ALX_ADPT_FLAG_0_MTQ_CAP			BIT_6
#define ALX_ADPT_FLAG_0_MTQ_EN			BIT_7
#define ALX_ADPT_FLAG_0_SRSS_CAP		BIT_8
#define ALX_ADPT_FLAG_0_SRSS_EN			BIT_9
#define ALX_ADPT_FLAG_0_FIXED_MSIX		BIT_10
#define ALX_ADPT_FLAG_0_RESET_REQUESTED		BIT_29
#define ALX_ADPT_FLAG_0_LSC_REQUESTED		BIT_30
#define ALX_ADPT_FLAG_0_DBG_REQUESTED		BIT_31

#define ALX_ADPT_FLAG_1_STATE_TESTING		BIT_0
#define ALX_ADPT_FLAG_1_STATE_RESETTING		BIT_1
#define ALX_ADPT_FLAG_1_STATE_DOWN		BIT_2
#define ALX_ADPT_FLAG_1_STATE_WATCH_DOG		BIT_3
#define ALX_ADPT_FLAG_1_STATE_DIAG_RUNNING	BIT_4
#define ALX_ADPT_FLAG_1_STATE_INACTIVE		BIT_5


#define CHK_ADPT_FLAG(_idx, _flag)	\
		CHK_FLAG_ARRAY(adpt, _idx, ADPT, _flag)
#define SET_ADPT_FLAG(_idx, _flag)	\
		SET_FLAG_ARRAY(adpt, _idx, ADPT, _flag)
#define CLI_ADPT_FLAG(_idx, _flag)	\
		CLI_FLAG_ARRAY(adpt, _idx, ADPT, _flag)

#ifdef HAVE_NETDEV_STATS_IN_NETDEV
#define GET_NETDEV_STATS(_adpt)		&((_adpt)->netdev->stats);
#else
#define GET_NETDEV_STATS(_adpt)		&((_adpt)->net_stats);
#endif /* HAVE_NETDEV_STATS_IN_NETDEV */


/* default to trying for four seconds */
#define ALX_TRY_LINK_TIMEOUT (4 * HZ)
#define ALX_TRY_LINK_COUNT   20


#define ALX_OPEN_CTRL_IRQ_EN		BIT_0
#define ALX_OPEN_CTRL_RESET_MAC		BIT_1
#define ALX_OPEN_CTRL_RESET_PHY		BIT_2
#define ALX_OPEN_CTRL_RESET_PCIE	BIT_3

#define ALX_OPEN_CTRL_RESET_ALL		(\
		ALX_OPEN_CTRL_RESET_MAC	|\
		ALX_OPEN_CTRL_RESET_PHY	|\
		ALX_OPEN_CTRL_RESET_PCIE)


/* needed by alx_main.c */
extern void alx_get_user_settings(struct alx_adapter *adpt);

/* needed by alx_ethtool.c */
extern char alx_drv_name[];
extern const char alx_drv_version[];
extern int alx_open_internal(struct alx_adapter *adpt, u32 ctrl);
extern void alx_stop_internal(struct alx_adapter *adpt, u32 ctrl);
extern void alx_reinit_locked(struct alx_adapter *adpt);
extern void alx_set_ethtool_ops(struct net_device *netdev);
#ifdef ETHTOOL_OPS_COMPAT
extern int ethtool_ioctl(struct ifreq *ifr);
#endif

#endif /* _ALX_H_ */
