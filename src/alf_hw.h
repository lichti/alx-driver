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

#ifndef L1F_HW_H_
#define L1F_HW_H_

#ifdef __cplusplus
extern "C" {
#endif/*__cplusplus*/

/*********************************************************************
 * some reqs for l1f_sw.h
 *
 * 1. some basic type must be defined if there are not defined by
 *    your compiler:
 *    u8, u16, u32, bool
 *
 * 2. PETHCONTEXT difinition should be in l1x_sw.h and it must contain
 *    pci_devid & pci_venid
 *
 * 3. you must define MAC_FPGA , PHY_FPGA to 1 or o
 *   #define MAC_TYPE   1   (1:FPGA, 0:ASIC)
 *   #define PHY_TYPE   0   (2:F1, 1:FPGA, 0:ASIC)
 *
 *
 *
 *********************************************************************/

#include "alx_hwcom.h"

#if MAC_TYPE == MAC_TYPE_ASIC
#undef PHY_TYPE
#define PHY_TYPE PHY_TYPE_ASIC
#endif

/******************************************************************************/

#define L1F_PCI_VID                     0x0000  /* 16bit */
#define L1F_PCI_DID                     0x0002  /* 16bit */
#define L1F_PCI_DID_GB                  BIT_0S
#define L1F_DEV_ID                      0x1091
#define L2F_DEV_ID                      0x1090
#define L1F_DEV_BFID                    0xE091  /* for bigfoot */

#define L1F_PCI_CMD                     0x0004  /* 16bit */
#define L1F_PCI_CMD_DISINT              BIT_10S
#define L1F_PCI_CMD_MASTEREN            BIT_2S
#define L1F_PCI_CMD_MEMEN               BIT_1S
#define L1F_PCI_CMD_IOEN                BIT_0S

#define L1F_PCI_STAT                    0x0006  /* 16bit */
#define L1F_PCI_STAT_PERR               BIT_15S
#define L1F_PCI_STAT_SERR               BIT_14S
#define L1F_PCI_STAT_RMABT              BIT_13S
#define L1F_PCI_STAT_RTABT              BIT_12S
#define L1F_PCI_STAT_STABT              BIT_11S
#define L1F_PCI_STAT_MDPERR             BIT_8S
#define L1F_PCI_STAT_INTS               BIT_3S

#define L1F_PCI_REVID                   0x0008  /* 8bit */
#define L1F_PCI_REVID_WTH_CR            BIT_1S
#define L1F_PCI_REVID_WTH_XD            BIT_0S
#define L1F_PCI_REVID_MASK              SHIFT3(0x1FU)
#define L1F_PCI_REVID_SHIFT             3
#define L1F_REV_A0                      0
#define L1F_REV_A1                      1
#define L1F_REV_B0                      2


#define L1F_PIF                         0x0009  /* 8bit program interface */
#define L1F_SCC                         0x000A  /* 8bit sub-class */
#define L1F_BCC                         0x000B  /* 8bit base-class */

#define L1F_BAR1_LO                     0x0010  /* memory space */
#define L1F_BAR1_HI                     0x0014

#define L1F_BAR2_LO                     0x0018  /* io space */
#define L1F_BAR2_HI                     0x001C

#define L1F_PCI_SSVID                   0x002C  /* 16bit sub-vendor id */
#define L1F_PCI_SSDID                   0x002E  /* 16bit sub-device id */

#define L1F_EXPNSN_ROM                  0x0030

#define L1F_INT_LINE                    0x003C  /* 8bit */

#define L1F_PM_CSR                      0x0044  /* 16bit */
#define L1F_PM_CSR_PME_STAT             BIT_15S
#define L1F_PM_CSR_DSCAL_MASK           SHIFT13(3U)
#define L1F_PM_CSR_DSCAL_SHIFT          13
#define L1F_PM_CSR_DSEL_MASK            SHIFT9(0xFU)
#define L1F_PM_CSR_DSEL_SHIFT           9
#define L1F_PM_CSR_PME_EN               BIT_8S
#define L1F_PM_CSR_PWST_MASK            SHIFT0(3U)
#define L1F_PM_CSR_PWST_SHIFT           0

#define L1F_PM_DATA                     0x0047  /* 8bit */

#define L1F_DEV_CAP                     0x005C
#define L1F_DEV_CAP_SPLSL_MASK          SHIFT26(3UL)
#define L1F_DEV_CAP_SPLSL_SHIFT         26
#define L1F_DEV_CAP_SPLV_MASK           SHIFT18(0xFFUL)
#define L1F_DEV_CAP_SPLV_SHIFT          18
#define L1F_DEV_CAP_RBER                BIT_15
#define L1F_DEV_CAP_PIPRS               BIT_14
#define L1F_DEV_CAP_AIPRS               BIT_13
#define L1F_DEV_CAP_ABPRS               BIT_12
#define L1F_DEV_CAP_L1ACLAT_MASK        SHIFT9(7UL)
#define L1F_DEV_CAP_L1ACLAT_SHIFT       9
#define L1F_DEV_CAP_L0SACLAT_MASK       SHIFT6(7UL)
#define L1F_DEV_CAP_L0SACLAT_SHIFT      6
#define L1F_DEV_CAP_EXTAG               BIT_5
#define L1F_DEV_CAP_PHANTOM             BIT_4
#define L1F_DEV_CAP_MPL_MASK            SHIFT0(7UL)
#define L1F_DEV_CAP_MPL_SHIFT           0
#define L1F_DEV_CAP_MPL_128             1
#define L1F_DEV_CAP_MPL_256             2
#define L1F_DEV_CAP_MPL_512             3
#define L1F_DEV_CAP_MPL_1024            4
#define L1F_DEV_CAP_MPL_2048            5
#define L1F_DEV_CAP_MPL_4096            6

#define L1F_DEV_CTRL                    0x0060    /* 16bit */
#define L1F_DEV_CTRL_MAXRRS_MASK        SHIFT12(7U)
#define L1F_DEV_CTRL_MAXRRS_SHIFT       12
#define L1F_DEV_CTRL_MAXRRS_MIN         2
#define L1F_DEV_CTRL_NOSNP_EN           BIT_11S
#define L1F_DEV_CTRL_AUXPWR_EN          BIT_10S
#define L1F_DEV_CTRL_PHANTOM_EN         BIT_9S
#define L1F_DEV_CTRL_EXTAG_EN           BIT_8S
#define L1F_DEV_CTRL_MPL_MASK           SHIFT5(7U)
#define L1F_DEV_CTRL_MPL_SHIFT          5
#define L1F_DEV_CTRL_RELORD_EN          BIT_4S
#define L1F_DEV_CTRL_URR_EN             BIT_3S
#define L1F_DEV_CTRL_FERR_EN            BIT_2S
#define L1F_DEV_CTRL_NFERR_EN           BIT_1S
#define L1F_DEV_CTRL_CERR_EN            BIT_0S


#define L1F_DEV_STAT                    0x0062    /* 16bit */
#define L1F_DEV_STAT_XS_PEND            BIT_5S
#define L1F_DEV_STAT_AUXPWR             BIT_4S
#define L1F_DEV_STAT_UR                 BIT_3S
#define L1F_DEV_STAT_FERR               BIT_2S
#define L1F_DEV_STAT_NFERR              BIT_1S
#define L1F_DEV_STAT_CERR               BIT_0S

#define L1F_LNK_CAP                     0x0064
#define L1F_LNK_CAP_PRTNUM_MASK         SHIFT24(0xFFUL)
#define L1F_LNK_CAP_PRTNUM_SHIFT        24
#define L1F_LNK_CAP_CLK_PM              BIT_18
#define L1F_LNK_CAP_L1EXTLAT_MASK       SHIFT15(7UL)
#define L1F_LNK_CAP_L1EXTLAT_SHIFT      15
#define L1F_LNK_CAP_L0SEXTLAT_MASK      SHIFT12(7UL)
#define L1F_LNK_CAP_L0SEXTLAT_SHIFT     12
#define L1F_LNK_CAP_ASPM_SUP_MASK       SHIFT10(3UL)
#define L1F_LNK_CAP_ASPM_SUP_SHIFT      10
#define L1F_LNK_CAP_ASPM_SUP_L0S        1
#define L1F_LNK_CAP_ASPM_SUP_L0SL1      3
#define L1F_LNK_CAP_MAX_LWH_MASK        SHIFT4(0x3FUL)
#define L1F_LNK_CAP_MAX_LWH_SHIFT       4
#define L1F_LNK_CAP_MAX_LSPD_MASH       SHIFT0(0xFUL)
#define L1F_LNK_CAP_MAX_LSPD_SHIFT      0

#define L1F_LNK_CTRL                    0x0068  /* 16bit */
#define L1F_LNK_CTRL_CLK_PM_EN          BIT_8S
#define L1F_LNK_CTRL_EXTSYNC            BIT_7S
#define L1F_LNK_CTRL_CMNCLK_CFG         BIT_6S
#define L1F_LNK_CTRL_RCB_128B           BIT_3S  /* 0:64b,1:128b */
#define L1F_LNK_CTRL_ASPM_MASK          SHIFT0(3U)
#define L1F_LNK_CTRL_ASPM_SHIFT         0
#define L1F_LNK_CTRL_ASPM_DIS           0
#define L1F_LNK_CTRL_ASPM_ENL0S         1
#define L1F_LNK_CTRL_ASPM_ENL1          2
#define L1F_LNK_CTRL_ASPM_ENL0SL1       3

#define L1F_LNK_STAT                    0x006A  /* 16bit */
#define L1F_LNK_STAT_SCLKCFG            BIT_12S
#define L1F_LNK_STAT_LNKTRAIN           BIT_11S
#define L1F_LNK_STAT_TRNERR             BIT_10S
#define L1F_LNK_STAT_LNKSPD_MASK        SHIFT0(0xFU)
#define L1F_LNK_STAT_LNKSPD_SHIFT       0
#define L1F_LNK_STAT_NEGLW_MASK         SHIFT4(0x3FU)
#define L1F_LNK_STAT_NEGLW_SHIFT        4

#define L1F_MSIX_MASK                   0x0090
#define L1F_MSIX_PENDING                0x0094

#define L1F_UE_SVRT                     0x010C
#define L1F_UE_SVRT_UR                  BIT_20
#define L1F_UE_SVRT_ECRCERR             BIT_19
#define L1F_UE_SVRT_MTLP                BIT_18
#define L1F_UE_SVRT_RCVOVFL             BIT_17
#define L1F_UE_SVRT_UNEXPCPL            BIT_16
#define L1F_UE_SVRT_CPLABRT             BIT_15
#define L1F_UE_SVRT_CPLTO               BIT_14
#define L1F_UE_SVRT_FCPROTERR           BIT_13
#define L1F_UE_SVRT_PTLP                BIT_12
#define L1F_UE_SVRT_DLPROTERR           BIT_4
#define L1F_UE_SVRT_TRNERR              BIT_0

#define L1F_EFLD                        0x0204  /* eeprom/flash load */
#define L1F_EFLD_F_ENDADDR_MASK         SHIFT16(0x3FFUL)
#define L1F_EFLD_F_ENDADDR_SHIFT        16
#define L1F_EFLD_F_EXIST                BIT_10
#define L1F_EFLD_E_EXIST                BIT_9
#define L1F_EFLD_EXIST                  BIT_8
#define L1F_EFLD_STAT                   BIT_5   /* 0:finish,1:in progress */
#define L1F_EFLD_IDLE                   BIT_4
#define L1F_EFLD_START                  BIT_0

#define L1F_SLD                         0x0218  /* efuse load */
#define L1F_SLD_FREQ_MASK               SHIFT24(3UL)
#define L1F_SLD_FREQ_SHIFT              24
#define L1F_SLD_FREQ_100K               0
#define L1F_SLD_FREQ_200K               1
#define L1F_SLD_FREQ_300K               2
#define L1F_SLD_FREQ_400K               3
#define L1F_SLD_EXIST                   BIT_23
#define L1F_SLD_SLVADDR_MASK            SHIFT16(0x7FUL)
#define L1F_SLD_SLVADDR_SHIFT           16
#define L1F_SLD_IDLE                    BIT_13
#define L1F_SLD_STAT                    BIT_12  /* 0:finish,1:in progress */
#define L1F_SLD_START                   BIT_11
#define L1F_SLD_STARTADDR_MASK          SHIFT0(0xFFUL)
#define L1F_SLD_STARTADDR_SHIFT         0
#define L1F_SLD_MAX_TO                  100

#define L1F_PCIE_MSIC                   0x021C
#define L1F_PCIE_MSIC_MSIX_DIS          BIT_22
#define L1F_PCIE_MSIC_MSI_DIS           BIT_21

#define L1F_PPHY_MISC1                  0x1000
#define L1F_PPHY_MISC1_RCVDET           BIT_2
#define L1F_PPHY_MISC1_NFTS_MASK        SHIFT16(0xFFUL)
#define L1F_PPHY_MISC1_NFTS_SHIFT       16
#define L1F_PPHY_MISC1_NFTS_HIPERF      0xA0    /* ???? */

#define L1F_PPHY_MISC2                  0x1004
#define L1F_PPHY_MISC2_L0S_TH_MASK      SHIFT18(0x3UL)
#define L1F_PPHY_MISC2_L0S_TH_SHIFT     18
#define L1F_PPHY_MISC2_CDR_BW_MASK      SHIFT16(0x3UL)
#define L1F_PPHY_MISC2_CDR_BW_SHIFT     16

#define L1F_PDLL_TRNS1                  0x1104
#define L1F_PDLL_TRNS1_D3PLLOFF_EN      BIT_11
#define L1F_PDLL_TRNS1_REGCLK_SEL_NORM  BIT_10
#define L1F_PDLL_TRNS1_REPLY_TO_MASK    SHIFT0(0x3FFUL)
#define L1F_PDLL_TRNS1_REPLY_TO_SHIFT   0


#define L1F_TLEXTN_STATS                0x1208
#define L1F_TLEXTN_STATS_DEVNO_MASK     SHIFT16(0x1FUL)
#define L1F_TLEXTN_STATS_DEVNO_SHIFT    16
#define L1F_TLEXTN_STATS_BUSNO_MASK     SHIFT8(0xFFUL)
#define L1F_TLEXTN_STATS_BUSNO_SHIFT    8

#define L1F_EFUSE_CTRL                  0x12C0
#define L1F_EFUSE_CTRL_FLAG             BIT_31          /* 0:read,1:write */
#define L1F_EUFSE_CTRL_ACK              BIT_30
#define L1F_EFUSE_CTRL_ADDR_MASK        SHIFT16(0x3FFUL)
#define L1F_EFUSE_CTRL_ADDR_SHIFT       16

#define L1F_EFUSE_DATA                  0x12C4

#define L1F_SPI_OP1                     0x12C8
#define L1F_SPI_OP1_RDID_MASK           SHIFT24(0xFFUL)
#define L1F_SPI_OP1_RDID_SHIFT          24
#define L1F_SPI_OP1_CE_MASK             SHIFT16(0xFFUL)
#define L1F_SPI_OP1_CE_SHIFT            16
#define L1F_SPI_OP1_SE_MASK             SHIFT8(0xFFUL)
#define L1F_SPI_OP1_SE_SHIFT            8
#define L1F_SPI_OP1_PRGRM_MASK          SHIFT0(0xFFUL)
#define L1F_SPI_OP1_PRGRM_SHIFT         0

#define L1F_SPI_OP2                     0x12CC
#define L1F_SPI_OP2_READ_MASK           SHIFT24(0xFFUL)
#define L1F_SPI_OP2_READ_SHIFT          24
#define L1F_SPI_OP2_WRSR_MASK           SHIFT16(0xFFUL)
#define L1F_SPI_OP2_WRSR_SHIFT          16
#define L1F_SPI_OP2_RDSR_MASK           SHIFT8(0xFFUL)
#define L1F_SPI_OP2_RDSR_SHIFT          8
#define L1F_SPI_OP2_WREN_MASK           SHIFT0(0xFFUL)
#define L1F_SPI_OP2_WREN_SHIFT          0

#define L1F_SPI_OP3                     0x12E4
#define L1F_SPI_OP3_WRDI_MASK           SHIFT8(0xFFUL)
#define L1F_SPI_OP3_WRDI_SHIFT          8
#define L1F_SPI_OP3_EWSR_MASK           SHIFT0(0xFFUL)
#define L1F_SPI_OP3_EWSR_SHIFT          0

#define L1F_EF_CTRL                     0x12D0
#define L1F_EF_CTRL_FSTS_MASK           SHIFT20(0xFFUL)
#define L1F_EF_CTRL_FSTS_SHIFT          20
#define L1F_EF_CTRL_CLASS_MASK          SHIFT16(7UL)
#define L1F_EF_CTRL_CLASS_SHIFT         16
#define L1F_EF_CTRL_CLASS_F_UNKNOWN     0
#define L1F_EF_CTRL_CLASS_F_STD         1
#define L1F_EF_CTRL_CLASS_F_SST         2
#define L1F_EF_CTRL_CLASS_E_UNKNOWN     0
#define L1F_EF_CTRL_CLASS_E_1K          1
#define L1F_EF_CTRL_CLASS_E_4K          2
#define L1F_EF_CTRL_FRET                BIT_15          /* 0:OK,1:fail */
#define L1F_EF_CTRL_TYP_MASK            SHIFT12(3UL)
#define L1F_EF_CTRL_TYP_SHIFT           12
#define L1F_EF_CTRL_TYP_NONE            0
#define L1F_EF_CTRL_TYP_F               1
#define L1F_EF_CTRL_TYP_E               2
#define L1F_EF_CTRL_TYP_UNKNOWN         3
#define L1F_EF_CTRL_ONE_CLK             BIT_10
#define L1F_EF_CTRL_ECLK_MASK           SHIFT8(3UL)
#define L1F_EF_CTRL_ECLK_SHIFT          8
#define L1F_EF_CTRL_ECLK_125K           0
#define L1F_EF_CTRL_ECLK_250K           1
#define L1F_EF_CTRL_ECLK_500K           2
#define L1F_EF_CTRL_ECLK_1M             3
#define L1F_EF_CTRL_FBUSY               BIT_7
#define L1F_EF_CTRL_ACTION              BIT_6           /* 1:start,0:stop */
#define L1F_EF_CTRL_AUTO_OP             BIT_5
#define L1F_EF_CTRL_SST_MODE            BIT_4           /* force using sst */
#define L1F_EF_CTRL_INST_MASK           SHIFT0(0xFUL)
#define L1F_EF_CTRL_INST_SHIFT          0
#define L1F_EF_CTRL_INST_NONE           0
#define L1F_EF_CTRL_INST_READ           1               /* for flash & eeprom */
#define L1F_EF_CTRL_INST_RDID           2
#define L1F_EF_CTRL_INST_RDSR           3
#define L1F_EF_CTRL_INST_WREN           4
#define L1F_EF_CTRL_INST_PRGRM          5
#define L1F_EF_CTRL_INST_SE             6
#define L1F_EF_CTRL_INST_CE             7
#define L1F_EF_CTRL_INST_WRSR           10
#define L1F_EF_CTRL_INST_EWSR           11
#define L1F_EF_CTRL_INST_WRDI           12
#define L1F_EF_CTRL_INST_WRITE          2               /* only for eeprom */

#define L1F_EF_ADDR                     0x12D4
#define L1F_EF_DATA                     0x12D8
#define L1F_SPI_ID                      0x12DC

#define L1F_SPI_CFG_START               0x12E0

#define L1F_PMCTRL                      0x12F8
#define L1F_PMCTRL_HOTRST_WTEN          BIT_31
#define L1F_PMCTRL_ASPM_FCEN            BIT_30  /* L0s/L1 dis by MAC based on
						 * thrghput(setting in 15A0) */
#define L1F_PMCTRL_SADLY_EN             BIT_29
#define L1F_PMCTRL_L0S_BUFSRX_EN        BIT_28
#define L1F_PMCTRL_LCKDET_TIMER_MASK    SHIFT24(0xFUL)
#define L1F_PMCTRL_LCKDET_TIMER_SHIFT   24
#define L1F_PMCTRL_LCKDET_TIMER_DEF     0xC
#define L1F_PMCTRL_L1REQ_TO_MASK        SHIFT20(0xFUL)
#define L1F_PMCTRL_L1REQ_TO_SHIFT       20      /* pm_request_l1 time > @
						 * ->L0s not L1 */
#define L1F_PMCTRL_L1REG_TO_DEF         0xC
#define L1F_PMCTRL_TXL1_AFTER_L0S       BIT_19
#define L1F_PMCTRL_L1_TIMER_MASK        SHIFT16(7UL)
#define L1F_PMCTRL_L1_TIMER_SHIFT       16
#define L1F_PMCTRL_L1_TIMER_DIS         0
#define L1F_PMCTRL_L1_TIMER_2US         1
#define L1F_PMCTRL_L1_TIMER_4US         2
#define L1F_PMCTRL_L1_TIMER_8US         3
#define L1F_PMCTRL_L1_TIMER_16US        4
#define L1F_PMCTRL_L1_TIMER_24US        5
#define L1F_PMCTRL_L1_TIMER_32US        6
#define L1F_PMCTRL_L1_TIMER_63US        7
#define L1F_PMCTRL_RCVR_WT_1US          BIT_15  /* 1:1us, 0:2ms */
#define L1F_PMCTRL_PWM_VER_11           BIT_14  /* 0:1.0a,1:1.1 */
#define L1F_PMCTRL_L1_CLKSW_EN          BIT_13  /* en pcie clk sw in L1 */
#define L1F_PMCTRL_L0S_EN               BIT_12
#define L1F_PMCTRL_RXL1_AFTER_L0S       BIT_11
#define L1F_PMCTRL_L0S_TIMER_MASK       SHIFT8(7UL)
#define L1F_PMCTRL_L0S_TIMER_SHIFT      8
#define L1F_PMCTRL_L1_BUFSRX_EN         BIT_7
#define L1F_PMCTRL_L1_SRDSRX_PWD        BIT_6   /* power down serdes rx */
#define L1F_PMCTRL_L1_SRDSPLL_EN        BIT_5
#define L1F_PMCTRL_L1_SRDS_EN           BIT_4
#define L1F_PMCTRL_L1_EN                BIT_3
#define L1F_PMCTRL_CLKREQ_EN            BIT_2
#define L1F_PMCTRL_RBER_EN              BIT_1
#define L1F_PMCTRL_SPRSDWER_EN          BIT_0

#define L1F_LTSSM_CTRL                  0x12FC
#define L1F_LTSSM_WRO_EN                BIT_12


/******************************************************************************/

#define L1F_MASTER                      0x1400
#define L1F_MASTER_OTP_FLG              BIT_31
#define L1F_MASTER_DEV_NUM_MASK         SHIFT24(0x7FUL)
#define L1F_MASTER_DEV_NUM_SHIFT        24
#define L1F_MASTER_REV_NUM_MASK         SHIFT16(0xFFUL)
#define L1F_MASTER_REV_NUM_SHIFT        16
#define L1F_MASTER_DEASSRT              BIT_15      /*ISSUE DE-ASSERT MSG */
#define L1F_MASTER_RDCLR_INT            BIT_14
#define L1F_MASTER_DMA_RST              BIT_13
#define L1F_MASTER_PCLKSEL_SRDS         BIT_12      /* 1:alwys sel pclk from
						     * serdes, not sw to 25M */
#define L1F_MASTER_IRQMOD2_EN           BIT_11      /* IRQ MODURATION FOR RX */
#define L1F_MASTER_IRQMOD1_EN           BIT_10      /* MODURATION FOR TX/RX */
#define L1F_MASTER_MANU_INT             BIT_9       /* SOFT MANUAL INT */
#define L1F_MASTER_MANUTIMER_EN         BIT_8
#define L1F_MASTER_SYSALVTIMER_EN       BIT_7       /* SYS ALIVE TIMER EN */
#define L1F_MASTER_OOB_DIS              BIT_6       /* OUT OF BOX DIS */
#define L1F_MASTER_WAKEN_25M            BIT_5       /* WAKE WO. PCIE CLK */
#define L1F_MASTER_BERT_START           BIT_4
#define L1F_MASTER_PCIE_TSTMOD_MASK     SHIFT2(3UL)
#define L1F_MASTER_PCIE_TSTMOD_SHIFT    2
#define L1F_MASTER_PCIE_RST             BIT_1
#define L1F_MASTER_DMA_MAC_RST          BIT_0       /* RST MAC & DMA */
#define L1F_DMA_MAC_RST_TO              50

#define L1F_MANU_TIMER                  0x1404

#define L1F_IRQ_MODU_TIMER              0x1408
#define L1F_IRQ_MODU_TIMER2_MASK        SHIFT16(0xFFFFUL)
#define L1F_IRQ_MODU_TIMER2_SHIFT       16          /* ONLY FOR RX */
#define L1F_IRQ_MODU_TIMER1_MASK        SHIFT0(0xFFFFUL)
#define L1F_IRQ_MODU_TIMER1_SHIFT       0

#define L1F_PHY_CTRL                    0x140C
#define L1F_PHY_CTRL_ADDR_MASK          SHIFT19(0x1FUL)
#define L1F_PHY_CTRL_ADDR_SHIFT         19
#define L1F_PHY_CTRL_BP_VLTGSW          BIT_18
#define L1F_PHY_CTRL_100AB_EN           BIT_17
#define L1F_PHY_CTRL_10AB_EN            BIT_16
#define L1F_PHY_CTRL_PLL_BYPASS         BIT_15
#define L1F_PHY_CTRL_POWER_DOWN         BIT_14      /* affect MAC & PHY,
						     * go to low power sts */
#define L1F_PHY_CTRL_PLL_ON             BIT_13      /* 1:PLL ALWAYS ON
						     * 0:CAN SWITCH IN LPW */
#define L1F_PHY_CTRL_RST_ANALOG         BIT_12
#define L1F_PHY_CTRL_HIB_PULSE          BIT_11
#define L1F_PHY_CTRL_HIB_EN             BIT_10
#define L1F_PHY_CTRL_GIGA_DIS           BIT_9
#define L1F_PHY_CTRL_IDDQ_DIS           BIT_8       /* POWER ON RST */
#define L1F_PHY_CTRL_IDDQ               BIT_7       /* WHILE REBOOT, BIT8(1)
						     * EFFECTS BIT7 */
#define L1F_PHY_CTRL_LPW_EXIT           BIT_6
#define L1F_PHY_CTRL_GATE_25M           BIT_5
#define L1F_PHY_CTRL_RVRS_ANEG          BIT_4
#define L1F_PHY_CTRL_ANEG_NOW           BIT_3
#define L1F_PHY_CTRL_LED_MODE           BIT_2
#define L1F_PHY_CTRL_RTL_MODE           BIT_1
#define L1F_PHY_CTRL_DSPRST_OUT         BIT_0       /* OUT OF DSP RST STATE */
#define L1F_PHY_CTRL_DSPRST_TO          80
#define L1F_PHY_CTRL_CLS                (\
	L1F_PHY_CTRL_LED_MODE           |\
	L1F_PHY_CTRL_100AB_EN           |\
	L1F_PHY_CTRL_PLL_ON)

#define L1F_MAC_STS                     0x1410
#define L1F_MAC_STS_SFORCE_MASK         SHIFT14(0xFUL)
#define L1F_MAC_STS_SFORCE_SHIFT        14
#define L1F_MAC_STS_CALIB_DONE          BIT13
#define L1F_MAC_STS_CALIB_RES_MASK      SHIFT8(0x1FUL)
#define L1F_MAC_STS_CALIB_RES_SHIFT     8
#define L1F_MAC_STS_CALIBERR_MASK       SHIFT4(0xFUL)
#define L1F_MAC_STS_CALIBERR_SHIFT      4
#define L1F_MAC_STS_TXQ_BUSY            BIT_3
#define L1F_MAC_STS_RXQ_BUSY            BIT_2
#define L1F_MAC_STS_TXMAC_BUSY          BIT_1
#define L1F_MAC_STS_RXMAC_BUSY          BIT_0
#define L1F_MAC_STS_IDLE                (\
	L1F_MAC_STS_TXQ_BUSY            |\
	L1F_MAC_STS_RXQ_BUSY            |\
	L1F_MAC_STS_TXMAC_BUSY          |\
	L1F_MAC_STS_RXMAC_BUSY)

#define L1F_MDIO                        0x1414
#define L1F_MDIO_MODE_EXT               BIT_30      /* 0:normal,1:ext */
#define L1F_MDIO_POST_READ              BIT_29
#define L1F_MDIO_AUTO_POLLING           BIT_28
#define L1F_MDIO_BUSY                   BIT_27
#define L1F_MDIO_CLK_SEL_MASK           SHIFT24(7UL)
#define L1F_MDIO_CLK_SEL_SHIFT          24
#define L1F_MDIO_CLK_SEL_25MD4          0           /* 25M DIV 4 */
#define L1F_MDIO_CLK_SEL_25MD6          2
#define L1F_MDIO_CLK_SEL_25MD8          3
#define L1F_MDIO_CLK_SEL_25MD10         4
#define L1F_MDIO_CLK_SEL_25MD32         5
#define L1F_MDIO_CLK_SEL_25MD64         6
#define L1F_MDIO_CLK_SEL_25MD128        7
#define L1F_MDIO_START                  BIT_23
#define L1F_MDIO_SPRES_PRMBL            BIT_22
#define L1F_MDIO_OP_READ                BIT_21      /* 1:read,0:write */
#define L1F_MDIO_REG_MASK               SHIFT16(0x1FUL)
#define L1F_MDIO_REG_SHIFT              16
#define L1F_MDIO_DATA_MASK              SHIFT0(0xFFFFUL)
#define L1F_MDIO_DATA_SHIFT             0
#define L1F_MDIO_MAX_AC_TO              120

#define L1F_MDIO_EXTN                   0x1448
#define L1F_MDIO_EXTN_PORTAD_MASK       SHIFT21(0x1FUL)
#define L1F_MDIO_EXTN_PORTAD_SHIFT      21
#define L1F_MDIO_EXTN_DEVAD_MASK        SHIFT16(0x1FUL)
#define L1F_MDIO_EXTN_DEVAD_SHIFT       16
#define L1F_MDIO_EXTN_REG_MASK          SHIFT0(0xFFFFUL)
#define L1F_MDIO_EXTN_REG_SHIFT         0

#define L1F_PHY_STS                     0x1418
#define L1F_PHY_STS_LPW                 BIT_31
#define L1F_PHY_STS_LPI                 BIT_30
#define L1F_PHY_STS_PWON_STRIP_MASK     SHIFT16(0xFFFUL)
#define L1F_PHY_STS_PWON_STRIP_SHIFT    16

#define L1F_PHY_STS_DUPLEX              BIT_3
#define L1F_PHY_STS_LINKUP              BIT_2
#define L1F_PHY_STS_SPEED_MASK          SHIFT0(3UL)
#define L1F_PHY_STS_SPEED_SHIFT         0
#define L1F_PHY_STS_SPEED_1000M         2
#define L1F_PHY_STS_SPEED_100M          1
#define L1F_PHY_STS_SPEED_10M           0

#define L1F_BIST0                       0x141C
#define L1F_BIST0_COL_MASK              SHIFT24(0x3FUL)
#define L1F_BIST0_COL_SHIFT             24
#define L1F_BIST0_ROW_MASK              SHIFT12(0xFFFUL)
#define L1F_BIST0_ROW_SHIFT             12
#define L1F_BIST0_STEP_MASK             SHIFT8(0xFUL)
#define L1F_BIST0_STEP_SHIFT            8
#define L1F_BIST0_PATTERN_MASK          SHIFT4(7UL)
#define L1F_BIST0_PATTERN_SHIFT         4
#define L1F_BIST0_CRIT                  BIT_3
#define L1F_BIST0_FIXED                 BIT_2
#define L1F_BIST0_FAIL                  BIT_1
#define L1F_BIST0_START                 BIT_0

#define L1F_BIST1                       0x1420
#define L1F_BIST1_COL_MASK              SHIFT24(0x3FUL)
#define L1F_BIST1_COL_SHIFT             24
#define L1F_BIST1_ROW_MASK              SHIFT12(0xFFFUL)
#define L1F_BIST1_ROW_SHIFT             12
#define L1F_BIST1_STEP_MASK             SHIFT8(0xFUL)
#define L1F_BIST1_STEP_SHIFT            8
#define L1F_BIST1_PATTERN_MASK          SHIFT4(7UL)
#define L1F_BIST1_PATTERN_SHIFT         4
#define L1F_BIST1_CRIT                  BIT_3
#define L1F_BIST1_FIXED                 BIT_2
#define L1F_BIST1_FAIL                  BIT_1
#define L1F_BIST1_START                 BIT_0

#define L1F_SERDES                      0x1424
#define L1F_SERDES_PHYCLK_SLWDWN        BIT_18
#define L1F_SERDES_MACCLK_SLWDWN        BIT_17
#define L1F_SERDES_SELFB_PLL_MASK       SHIFT14(3UL)
#define L1F_SERDES_SELFB_PLL_SHIFT      14
#define L1F_SERDES_PHYCLK_SEL_GTX       BIT_13          /* 1:gtx_clk, 0:25M */
#define L1F_SERDES_PCIECLK_SEL_SRDS     BIT_12          /* 1:serdes,0:25M */
#define L1F_SERDES_BUFS_RX_EN           BIT_11
#define L1F_SERDES_PD_RX                BIT_10
#define L1F_SERDES_PLL_EN               BIT_9
#define L1F_SERDES_EN                   BIT_8
#define L1F_SERDES_SELFB_PLL_SEL_CSR    BIT_6       /* 0:state-machine,1:csr */
#define L1F_SERDES_SELFB_PLL_CSR_MASK   SHIFT4(3UL)
#define L1F_SERDES_SELFB_PLL_CSR_SHIFT  4
#define L1F_SERDES_SELFB_PLL_CSR_4      3           /* 4-12% OV-CLK */
#define L1F_SERDES_SELFB_PLL_CSR_0      2           /* 0-4% OV-CLK */
#define L1F_SERDES_SELFB_PLL_CSR_12     1           /* 12-18% OV-CLK */
#define L1F_SERDES_SELFB_PLL_CSR_18     0           /* 18-25% OV-CLK */
#define L1F_SERDES_VCO_SLOW             BIT_3
#define L1F_SERDES_VCO_FAST             BIT_2
#define L1F_SERDES_LOCKDCT_EN           BIT_1
#define L1F_SERDES_LOCKDCTED            BIT_0

#define L1F_LED_CTRL                    0x1428
#define L1F_LED_CTRL_PATMAP2_MASK       SHIFT8(3UL)
#define L1F_LED_CTRL_PATMAP2_SHIFT      8
#define L1F_LED_CTRL_PATMAP1_MASK       SHIFT6(3UL)
#define L1F_LED_CTRL_PATMAP1_SHIFT      6
#define L1F_LED_CTRL_PATMAP0_MASK       SHIFT4(3UL)
#define L1F_LED_CTRL_PATMAP0_SHIFT      4
#define L1F_LED_CTRL_D3_MODE_MASK       SHIFT2(3UL)
#define L1F_LED_CTRL_D3_MODE_SHIFT      2
#define L1F_LED_CTRL_D3_MODE_NORMAL     0
#define L1F_LED_CTRL_D3_MODE_WOL_DIS    1
#define L1F_LED_CTRL_D3_MODE_WOL_ANY    2
#define L1F_LED_CTRL_D3_MODE_WOL_EN     3
#define L1F_LED_CTRL_DUTY_CYCL_MASK     SHIFT0(3UL)
#define L1F_LED_CTRL_DUTY_CYCL_SHIFT    0
#define L1F_LED_CTRL_DUTY_CYCL_50       0           /* 50% */
#define L1F_LED_CTRL_DUTY_CYCL_125      1           /* 12.5% */
#define L1F_LED_CTRL_DUTY_CYCL_25       2           /* 25% */
#define L1F_LED_CTRL_DUTY_CYCL_75       3           /* 75% */

#define L1F_LED_PATN                    0x142C
#define L1F_LED_PATN1_MASK              SHIFT16(0xFFFFUL)
#define L1F_LED_PATN1_SHIFT             16
#define L1F_LED_PATN0_MASK              SHIFT0(0xFFFFUL)
#define L1F_LED_PATN0_SHIFT             0

#define L1F_LED_PATN2                   0x1430
#define L1F_LED_PATN2_MASK              SHIFT0(0xFFFFUL)
#define L1F_LED_PATN2_SHIFT             0

#define L1F_SYSALV                      0x1434
#define L1F_SYSALV_FLAG                 BIT_0

#define L1F_PCIERR_INST                 0x1438
#define L1F_PCIERR_INST_TX_RATE_MASK    SHIFT4(0xFUL)
#define L1F_PCIERR_INST_TX_RATE_SHIFT   4
#define L1F_PCIERR_INST_RX_RATE_MASK    SHIFT0(0xFUL)
#define L1F_PCIERR_INST_RX_RATE_SHIFT   0

#define L1F_LPI_DECISN_TIMER            0x143C

#define L1F_LPI_CTRL                    0x1440
#define L1F_LPI_CTRL_CHK_DA             BIT_31
#define L1F_LPI_CTRL_ENH_TO_MASK        SHIFT12(0x1FFFUL)
#define L1F_LPI_CTRL_ENH_TO_SHIFT       12
#define L1F_LPI_CTRL_ENH_TH_MASK        SHIFT6(0x1FUL)
#define L1F_LPI_CTRL_ENH_TH_SHIFT       6
#define L1F_LPI_CTRL_ENH_EN             BIT_5
#define L1F_LPI_CTRL_CHK_RX             BIT_4
#define L1F_LPI_CTRL_CHK_STATE          BIT_3
#define L1F_LPI_CTRL_GMII               BIT_2
#define L1F_LPI_CTRL_TO_PHY             BIT_1
#define L1F_LPI_CTRL_EN                 BIT_0

#define L1F_LPI_WAIT                    0x1444
#define L1F_LPI_WAIT_TIMER_MASK         SHIFT0(0xFFFFUL)
#define L1F_LPI_WAIT_TIMER_SHIFT        0

#define L1F_HRTBT_VLAN                  0x1450      /* HEARTBEAT, FOR CIFS */
#define L1F_HRTBT_VLANID_MASK           SHIFT0(0xFFFFUL) /* OR CLOUD */
#define L1F_HRRBT_VLANID_SHIFT          0

#define L1F_HRTBT_CTRL                  0x1454
#define L1F_HRTBT_CTRL_EN               BIT_31
#define L1F_HRTBT_CTRL_PERIOD_MASK      SHIFT25(0x3FUL)
#define L1F_HRTBT_CTRL_PERIOD_SHIFT     25
#define L1F_HRTBT_CTRL_HASVLAN          BIT_24
#define L1F_HRTBT_CTRL_HDRADDR_MASK     SHIFT12(0xFFFUL)    /* A0 */
#define L1F_HRTBT_CTRL_HDRADDR_SHIFT    12
#define L1F_HRTBT_CTRL_HDRADDRB0_MASK   SHIFT13(0x7FFUL)    /* B0 */
#define L1F_HRTBT_CTRL_HDRADDRB0_SHIFT  13
#define L1F_HRTBT_CTRL_PKT_FRAG         BIT_12              /* B0 */
#define L1F_HRTBT_CTRL_PKTLEN_MASK      SHIFT0(0xFFFUL)
#define L1F_HRTBT_CTRL_PKTLEN_SHIFT     0

#define L1F_HRTBT_EXT_CTRL                  0x1AD0      /* B0 */
#define L1F_HRTBT_EXT_CTRL_NS_EN            BIT_12
#define L1F_HRTBT_EXT_CTRL_FRAG_LEN_MASK    SHIFT4(0xFFUL)
#define L1F_HRTBT_EXT_CTRL_FRAG_LEN_SHIFT   4
#define L1F_HRTBT_EXT_CTRL_IS_8023          BIT_3
#define L1F_HRTBT_EXT_CTRL_IS_IPV6          BIT_2
#define L1F_HRTBT_EXT_CTRL_WAKEUP_EN        BIT_1
#define L1F_HRTBT_EXT_CTRL_ARP_EN           BIT_0

#define L1F_HRTBT_REM_IPV4_ADDR             0x1AD4
#define L1F_HRTBT_HOST_IPV4_ADDR            0x1478/*use L1F_TRD_BUBBLE_DA_IP4*/
#define L1F_HRTBT_REM_IPV6_ADDR3            0x1AD8
#define L1F_HRTBT_REM_IPV6_ADDR2            0x1ADC
#define L1F_HRTBT_REM_IPV6_ADDR1            0x1AE0
#define L1F_HRTBT_REM_IPV6_ADDR0            0x1AE4
/*SWOI_HOST_IPV6_ADDR reuse reg1a60-1a6c, 1a70-1a7c, 1aa0-1aac, 1ab0-1abc.*/
#define L1F_HRTBT_WAKEUP_PORT               0x1AE8
#define L1F_HRTBT_WAKEUP_PORT_SRC_MASK      SHIFT16(0xFFFFUL)
#define L1F_HRTBT_WAKEUP_PORT_SRC_SHIFT     16
#define L1F_HRTBT_WAKEUP_PORT_DEST_MASK     SHIFT0(0xFFFFUL)
#define L1F_HRTBT_WAKEUP_PORT_DEST_SHIFT    0

#define L1F_HRTBT_WAKEUP_DATA7              0x1AEC
#define L1F_HRTBT_WAKEUP_DATA6              0x1AF0
#define L1F_HRTBT_WAKEUP_DATA5              0x1AF4
#define L1F_HRTBT_WAKEUP_DATA4              0x1AF8
#define L1F_HRTBT_WAKEUP_DATA3              0x1AFC
#define L1F_HRTBT_WAKEUP_DATA2              0x1B80
#define L1F_HRTBT_WAKEUP_DATA1              0x1B84
#define L1F_HRTBT_WAKEUP_DATA0              0x1B88

#define L1F_RXPARSE                     0x1458
#define L1F_RXPARSE_FLT6_L4_MASK        SHIFT30(3UL)
#define L1F_RXPARSE_FLT6_L4_SHIFT       30
#define L1F_RXPARSE_FLT6_L3_MASK        SHIFT28(3UL)
#define L1F_RXPARSE_FLT6_L3_SHIFT       28
#define L1F_RXPARSE_FLT5_L4_MASK        SHIFT26(3UL)
#define L1F_RXPARSE_FLT5_L4_SHIFT       26
#define L1F_RXPARSE_FLT5_L3_MASK        SHIFT24(3UL)
#define L1F_RXPARSE_FLT5_L3_SHIFT       24
#define L1F_RXPARSE_FLT4_L4_MASK        SHIFT22(3UL)
#define L1F_RXPARSE_FLT4_L4_SHIFT       22
#define L1F_RXPARSE_FLT4_L3_MASK        SHIFT20(3UL)
#define L1F_RXPARSE_FLT4_L3_SHIFT       20
#define L1F_RXPARSE_FLT3_L4_MASK        SHIFT18(3UL)
#define L1F_RXPARSE_FLT3_L4_SHIFT       18
#define L1F_RXPARSE_FLT3_L3_MASK        SHIFT16(3UL)
#define L1F_RXPARSE_FLT3_L3_SHIFT       16
#define L1F_RXPARSE_FLT2_L4_MASK        SHIFT14(3UL)
#define L1F_RXPARSE_FLT2_L4_SHIFT       14
#define L1F_RXPARSE_FLT2_L3_MASK        SHIFT12(3UL)
#define L1F_RXPARSE_FLT2_L3_SHIFT       12
#define L1F_RXPARSE_FLT1_L4_MASK        SHIFT10(3UL)
#define L1F_RXPARSE_FLT1_L4_SHIFT       10
#define L1F_RXPARSE_FLT1_L3_MASK        SHIFT8(3UL)
#define L1F_RXPARSE_FLT1_L3_SHIFT       8
#define L1F_RXPARSE_FLT6_EN             BIT_5
#define L1F_RXPARSE_FLT5_EN             BIT_4
#define L1F_RXPARSE_FLT4_EN             BIT_3
#define L1F_RXPARSE_FLT3_EN             BIT_2
#define L1F_RXPARSE_FLT2_EN             BIT_1
#define L1F_RXPARSE_FLT1_EN             BIT_0
#define L1F_RXPARSE_FLT_L4_UDP          0
#define L1F_RXPARSE_FLT_L4_TCP          1
#define L1F_RXPARSE_FLT_L4_BOTH         2
#define L1F_RXPARSE_FLT_L4_NONE         3
#define L1F_RXPARSE_FLT_L3_IPV6         0
#define L1F_RXPARSE_FLT_L3_IPV4         1
#define L1F_RXPARSE_FLT_L3_BOTH         2

/* Terodo support */
#define L1F_TRD_CTRL                    0x145C
#define L1F_TRD_CTRL_EN                 BIT_31
#define L1F_TRD_CTRL_BUBBLE_WAKE_EN     BIT_30
#define L1F_TRD_CTRL_PREFIX_CMP_HW      BIT_28
#define L1F_TRD_CTRL_RSHDR_ADDR_MASK    SHIFT16(0xFFFUL)
#define L1F_TRD_CTRL_RSHDR_ADDR_SHIFT   16
#define L1F_TRD_CTRL_SINTV_MAX_MASK     SHIFT8(0xFFUL)
#define L1F_TRD_CTRL_SINTV_MAX_SHIFT    8
#define L1F_TRD_CTRL_SINTV_MIN_MASK     SHIFT0(0xFFUL)
#define L1F_TRD_CTRL_SINTV_MIN_SHIFT    0

#define L1F_TRD_RS                      0x1460
#define L1F_TRD_RS_SZ_MASK              SHIFT20(0xFFFUL)
#define L1F_TRD_RS_SZ_SHIFT             20
#define L1F_TRD_RS_NONCE_OFS_MASK       SHIFT8(0xFFFUL)
#define L1F_TRD_RS_NONCE_OFS_SHIFT      8
#define L1F_TRD_RS_SEQ_OFS_MASK         SHIFT0(0xFFUL)
#define L1F_TRD_RS_SEQ_OFS_SHIFT        0

#define L1F_TRD_SRV_IP4                 0x1464

#define L1F_TRD_CLNT_EXTNL_IP4          0x1468

#define L1F_TRD_PORT                    0x146C
#define L1F_TRD_PORT_CLNT_EXTNL_MASK    SHIFT16(0xFFFFUL)
#define L1F_TRD_PORT_CLNT_EXTNL_SHIFT   16
#define L1F_TRD_PORT_SRV_MASK           SHIFT0(0xFFFFUL)
#define L1F_TRD_PORT_SRV_SHIFT          0

#define L1F_TRD_PREFIX                  0x1470

#define L1F_TRD_BUBBLE_DA_IP4           0x1478

#define L1F_TRD_BUBBLE_DA_PORT          0x147C


#define L1F_IDLE_DECISN_TIMER           0x1474  /* B0 */
#define L1F_IDLE_DECISN_TIMER_DEF       0x400   /* 1ms */


#define L1F_MAC_CTRL                    0x1480
#define L1F_MAC_CTRL_FAST_PAUSE         BIT_31
#define L1F_MAC_CTRL_WOLSPED_SWEN       BIT_30
#define L1F_MAC_CTRL_MHASH_ALG_HI5B     BIT_29  /* 1:legacy, 0:marvl(low5b)*/
#define L1F_MAC_CTRL_SPAUSE_EN          BIT_28
#define L1F_MAC_CTRL_DBG_EN             BIT_27
#define L1F_MAC_CTRL_BRD_EN             BIT_26
#define L1F_MAC_CTRL_MULTIALL_EN        BIT_25
#define L1F_MAC_CTRL_RX_XSUM_EN         BIT_24
#define L1F_MAC_CTRL_THUGE              BIT_23
#define L1F_MAC_CTRL_MBOF               BIT_22
#define L1F_MAC_CTRL_SPEED_MASK         SHIFT20(3UL)
#define L1F_MAC_CTRL_SPEED_SHIFT        20
#define L1F_MAC_CTRL_SPEED_10_100       1
#define L1F_MAC_CTRL_SPEED_1000         2
#define L1F_MAC_CTRL_SIMR               BIT_19
#define L1F_MAC_CTRL_SSTCT              BIT_17
#define L1F_MAC_CTRL_TPAUSE             BIT_16
#define L1F_MAC_CTRL_PROMISC_EN         BIT_15
#define L1F_MAC_CTRL_VLANSTRIP          BIT_14
#define L1F_MAC_CTRL_PRMBLEN_MASK       SHIFT10(0xFUL)
#define L1F_MAC_CTRL_PRMBLEN_SHIFT      10
#define L1F_MAC_CTRL_RHUGE_EN           BIT_9
#define L1F_MAC_CTRL_FLCHK              BIT_8
#define L1F_MAC_CTRL_PCRCE              BIT_7
#define L1F_MAC_CTRL_CRCE               BIT_6
#define L1F_MAC_CTRL_FULLD              BIT_5
#define L1F_MAC_CTRL_LPBACK_EN          BIT_4
#define L1F_MAC_CTRL_RXFC_EN            BIT_3
#define L1F_MAC_CTRL_TXFC_EN            BIT_2
#define L1F_MAC_CTRL_RX_EN              BIT_1
#define L1F_MAC_CTRL_TX_EN              BIT_0

#define L1F_GAP                         0x1484
#define L1F_GAP_IPGR2_MASK              SHIFT24(0x7FUL)
#define L1F_GAP_IPGR2_SHIFT             24
#define L1F_GAP_IPGR1_MASK              SHIFT16(0x7FUL)
#define L1F_GAP_IPGR1_SHIFT             16
#define L1F_GAP_MIN_IFG_MASK            SHIFT8(0xFFUL)
#define L1F_GAP_MIN_IFG_SHIFT           8
#define L1F_GAP_IPGT_MASK               SHIFT0(0x7FUL)  /* A0 diff with B0 */
#define L1F_GAP_IPGT_SHIFT              0

#define L1F_STAD0                       0x1488
#define L1F_STAD1                       0x148C

#define L1F_HASH_TBL0                   0x1490
#define L1F_HASH_TBL1                   0x1494

#define L1F_HALFD                       0x1498
#define L1F_HALFD_JAM_IPG_MASK          SHIFT24(0xFUL)
#define L1F_HALFD_JAM_IPG_SHIFT         24
#define L1F_HALFD_ABEBT_MASK            SHIFT20(0xFUL)
#define L1F_HALFD_ABEBT_SHIFT           20
#define L1F_HALFD_ABEBE                 BIT_19
#define L1F_HALFD_BPNB                  BIT_18
#define L1F_HALFD_NOBO                  BIT_17
#define L1F_HALFD_EDXSDFR               BIT_16
#define L1F_HALFD_RETRY_MASK            SHIFT12(0xFUL)
#define L1F_HALFD_RETRY_SHIFT           12
#define L1F_HALFD_LCOL_MASK             SHIFT0(0x3FFUL)
#define L1F_HALFD_LCOL_SHIFT            0

#define L1F_MTU                         0x149C
#define L1F_MTU_JUMBO_TH                1514
#define L1F_MTU_STD_ALGN                1536
#define L1F_MTU_MIN                     64

#define L1F_SRAM0                       0x1500
#define L1F_SRAM_RFD_TAIL_ADDR_MASK     SHIFT16(0xFFFUL)
#define L1F_SRAM_RFD_TAIL_ADDR_SHIFT    16
#define L1F_SRAM_RFD_HEAD_ADDR_MASK     SHIFT0(0xFFFUL)
#define L1F_SRAM_RFD_HEAD_ADDR_SHIFT    0

#define L1F_SRAM1                       0x1510
#define L1F_SRAM_RFD_LEN_MASK           SHIFT0(0xFFFUL) /* 8BYTES UNIT */
#define L1F_SRAM_RFD_LEN_SHIFT          0

#define L1F_SRAM2                       0x1518
#define L1F_SRAM_TRD_TAIL_ADDR_MASK     SHIFT16(0xFFFUL)
#define L1F_SRAM_TRD_TAIL_ADDR_SHIFT    16
#define L1F_SRMA_TRD_HEAD_ADDR_MASK     SHIFT0(0xFFFUL)
#define L1F_SRAM_TRD_HEAD_ADDR_SHIFT    0

#define L1F_SRAM3                       0x151C
#define L1F_SRAM_TRD_LEN_MASK           SHIFT0(0xFFFUL) /* 8BYTES UNIT */
#define L1F_SRAM_TRD_LEN_SHIFT          0

#define L1F_SRAM4                       0x1520
#define L1F_SRAM_RXF_TAIL_ADDR_MASK     SHIFT16(0xFFFUL)
#define L1F_SRAM_RXF_TAIL_ADDR_SHIFT    16
#define L1F_SRAM_RXF_HEAD_ADDR_MASK     SHIFT0(0xFFFUL)
#define L1F_SRAM_RXF_HEAD_ADDR_SHIFT    0

#define L1F_SRAM5                       0x1524
#define L1F_SRAM_RXF_LEN_MASK           SHIFT0(0xFFFUL) /* 8BYTES UNIT */
#define L1F_SRAM_RXF_LEN_SHIFT          0
#define L1F_SRAM_RXF_LEN_8K             (8*1024)

#define L1F_SRAM6                       0x1528
#define L1F_SRAM_TXF_TAIL_ADDR_MASK     SHIFT16(0xFFFUL)
#define L1F_SRAM_TXF_TAIL_ADDR_SHIFT    16
#define L1F_SRAM_TXF_HEAD_ADDR_MASK     SHIFT0(0xFFFUL)
#define L1F_SRAM_TXF_HEAD_ADDR_SHIFT    0

#define L1F_SRAM7                       0x152C
#define L1F_SRAM_TXF_LEN_MASK           SHIFT0(0xFFFUL) /* 8BYTES UNIT */
#define L1F_SRAM_TXF_LEN_SHIFT          0

#define L1F_SRAM8                       0x1530
#define L1F_SRAM_PATTERN_ADDR_MASK      SHIFT16(0xFFFUL)
#define L1F_SRAM_PATTERN_ADDR_SHIFT     16
#define L1F_SRAM_TSO_ADDR_MASK          SHIFT0(0xFFFUL)
#define L1F_SRAM_TSO_ADDR_SHIFT         0

#define L1F_SRAM9                       0x1534
#define L1F_SRAM_LOAD_PTR               BIT_0

#define L1F_RX_BASE_ADDR_HI             0x1540

#define L1F_TX_BASE_ADDR_HI             0x1544

#define L1F_RFD_ADDR_LO                 0x1550
#define L1F_RFD_RING_SZ                 0x1560
#define L1F_RFD_BUF_SZ                  0x1564
#define L1F_RFD_BUF_SZ_MASK             SHIFT0(0xFFFFUL)
#define L1F_RFD_BUF_SZ_SHIFT            0

#define L1F_RRD_ADDR_LO                 0x1568
#define L1F_RRD_RING_SZ                 0x1578
#define L1F_RRD_RING_SZ_MASK            SHIFT0(0xFFFUL)
#define L1F_RRD_RING_SZ_SHIFT           0

#define L1F_TPD_PRI3_ADDR_LO            0x14E4      /* HIGHEST PRIORITY */
#define L1F_TPD_PRI2_ADDR_LO            0x14E0
#define L1F_TPD_PRI1_ADDR_LO            0x157C
#define L1F_TPD_PRI0_ADDR_LO            0x1580      /* LOWEST PRORITY */

#define L1F_TPD_PRI3_PIDX               0x1618      /* 16BIT */
#define L1F_TPD_PRI2_PIDX               0x161A      /* 16BIT */
#define L1F_TPD_PRI1_PIDX               0x15F0      /* 16BIT */
#define L1F_TPD_PRI0_PIDX               0x15F2      /* 16BIT */

#define L1F_TPD_PRI3_CIDX               0x161C      /* 16BIT */
#define L1F_TPD_PRI2_CIDX               0x161E      /* 16BIT */
#define L1F_TPD_PRI1_CIDX               0x15F4      /* 16BIT */
#define L1F_TPD_PRI0_CIDX               0x15F6      /* 16BIT */

#define L1F_TPD_RING_SZ                 0x1584
#define L1F_TPD_RING_SZ_MASK            SHIFT0(0xFFFFUL)
#define L1F_TPD_RING_SZ_SHIFT           0

#define L1F_CMB_ADDR_LO                 0x1588      /* NOT USED */

#define L1F_TXQ0                        0x1590
#define L1F_TXQ0_TXF_BURST_PREF_MASK    SHIFT16(0xFFFFUL)
#define L1F_TXQ0_TXF_BURST_PREF_SHIFT   16
#define L1F_TXQ_TXF_BURST_PREF_DEF      0x200
#define L1F_TXQ0_PEDING_CLR             BIT_8
#define L1F_TXQ0_LSO_8023_EN            BIT_7
#define L1F_TXQ0_MODE_ENHANCE           BIT_6
#define L1F_TXQ0_EN                     BIT_5
#define L1F_TXQ0_SUPT_IPOPT             BIT_4
#define L1F_TXQ0_TPD_BURSTPREF_MASK     SHIFT0(0xFUL)
#define L1F_TXQ0_TPD_BURSTPREF_SHIFT    0
#define L1F_TXQ_TPD_BURSTPREF_DEF       5

#define L1F_TXQ1                        0x1594
#define L1F_TXQ1_ERRLGPKT_DROP_EN       BIT_11          /* drop error large
							 * (>rfd buf) packet */
#define L1F_TXQ1_JUMBO_TSOTHR_MASK      SHIFT0(0x7FFUL) /* 8BYTES UNIT */
#define L1F_TXQ1_JUMBO_TSOTHR_SHIFT     0
#define L1F_TXQ1_JUMBO_TSO_TH           (7*1024)    /* byte */

#define L1F_TXQ2                        0x1598          /* ENTER L1 CONTROL */
#define L1F_TXQ2_BURST_EN               BIT_31
#define L1F_TXQ2_BURST_HI_WM_MASK       SHIFT16(0xFFFUL)
#define L1F_TXQ2_BURST_HI_WM_SHIFT      16
#define L1F_TXQ2_BURST_LO_WM_MASK       SHIFT0(0xFFFUL)
#define L1F_TXQ2_BURST_LO_WM_SHIFT      0

#define L1F_RXQ0                        0x15A0
#define L1F_RXQ0_EN                     BIT_31
#define L1F_RXQ0_CUT_THRU_EN            BIT_30
#define L1F_RXQ0_RSS_HASH_EN            BIT_29
#define L1F_RXQ0_NON_IP_QTBL            BIT_28  /* 0:q0,1:table */
#define L1F_RXQ0_RSS_MODE_MASK          SHIFT26(3UL)
#define L1F_RXQ0_RSS_MODE_SHIFT         26
#define L1F_RXQ0_RSS_MODE_DIS           0
#define L1F_RXQ0_RSS_MODE_SQSI          1
#define L1F_RXQ0_RSS_MODE_MQSI          2
#define L1F_RXQ0_RSS_MODE_MQMI          3
#define L1F_RXQ0_NUM_RFD_PREF_MASK      SHIFT20(0x3FUL)
#define L1F_RXQ0_NUM_RFD_PREF_SHIFT     20
#define L1F_RXQ0_NUM_RFD_PREF_DEF       8
#define L1F_RXQ0_IDT_TBL_SIZE_MASK      SHIFT8(0x1FFUL)
#define L1F_RXQ0_IDT_TBL_SIZE_SHIFT     8
#define L1F_RXQ0_IDT_TBL_SIZE_DEF       0x100
#define L1F_RXQ0_IPV6_PARSE_EN          BIT_7
#define L1F_RXQ0_RSS_HSTYP_IPV6_TCP_EN  BIT_5
#define L1F_RXQ0_RSS_HSTYP_IPV6_EN      BIT_4
#define L1F_RXQ0_RSS_HSTYP_IPV4_TCP_EN  BIT_3
#define L1F_RXQ0_RSS_HSTYP_IPV4_EN      BIT_2
#define L1F_RXQ0_RSS_HSTYP_ALL          (\
	L1F_RXQ0_RSS_HSTYP_IPV6_TCP_EN  |\
	L1F_RXQ0_RSS_HSTYP_IPV4_TCP_EN  |\
	L1F_RXQ0_RSS_HSTYP_IPV6_EN      |\
	L1F_RXQ0_RSS_HSTYP_IPV4_EN)
#define L1F_RXQ0_ASPM_THRESH_MASK       SHIFT0(3UL)
#define L1F_RXQ0_ASPM_THRESH_SHIFT      0
#define L1F_RXQ0_ASPM_THRESH_NO         0
#define L1F_RXQ0_ASPM_THRESH_1M         1
#define L1F_RXQ0_ASPM_THRESH_10M        2
#define L1F_RXQ0_ASPM_THRESH_100M       3

#define L1F_RXQ1                        0x15A4
#define L1F_RXQ1_JUMBO_LKAH_MASK        SHIFT12(0xFUL)      /* 32BYTES UNIT */
#define L1F_RXQ1_JUMBO_LKAH_SHIFT       12
#define L1F_RXQ1_RFD_PREF_DOWN_MASK     SHIFT6(0x3FUL)
#define L1F_RXQ1_RFD_PREF_DOWN_SHIFT    6
#define L1F_RXQ1_RFD_PREF_UP_MASK       SHIFT0(0x3FUL)
#define L1F_RXQ1_RFD_PREF_UP_SHIFT      0

#define L1F_RXQ2                        0x15A8
/* XOFF: USED SRAM LOWER THAN IT, THEN NOTIFY THE PEER TO SEND AGAIN */
#define L1F_RXQ2_RXF_XOFF_THRESH_MASK   SHIFT16(0xFFFUL)
#define L1F_RXQ2_RXF_XOFF_THRESH_SHIFT  16
#define L1F_RXQ2_RXF_XON_THRESH_MASK    SHIFT0(0xFFFUL)
#define L1F_RXQ2_RXF_XON_THRESH_SHIFT   0

#define L1F_RXQ3                        0x15AC
#define L1F_RXQ3_RXD_TIMER_MASK         SHIFT16(0x7FFFUL)
#define L1F_RXQ3_RXD_TIMER_SHIFT        16
#define L1F_RXQ3_RXD_THRESH_MASK        SHIFT0(0xFFFUL) /* 8BYTES UNIT */
#define L1F_RXQ3_RXD_THRESH_SHIFT       0

#define L1F_DMA                         0x15C0
#define L1F_DMA_SMB_NOW                 BIT_31
#define L1F_DMA_WPEND_CLR               BIT_30
#define L1F_DMA_RPEND_CLR               BIT_29
#define L1F_DMA_WSRAM_RDCTRL            BIT_28
#define L1F_DMA_RCHNL_SEL_MASK          SHIFT26(3UL)
#define L1F_DMA_RCHNL_SEL_SHIFT         26
#define L1F_DMA_RCHNL_SEL_1             0
#define L1F_DMA_RCHNL_SEL_2             1
#define L1F_DMA_RCHNL_SEL_3             2
#define L1F_DMA_RCHNL_SEL_4             3
#define L1F_DMA_SMB_EN                  BIT_21      /* smb dma enable */
#define L1F_DMA_WDLY_CNT_MASK           SHIFT16(0xFUL)
#define L1F_DMA_WDLY_CNT_SHIFT          16
#define L1F_DMA_WDLY_CNT_DEF            4
#define L1F_DMA_RDLY_CNT_MASK           SHIFT11(0x1FUL)
#define L1F_DMA_RDLY_CNT_SHIFT          11
#define L1F_DMA_RDLY_CNT_DEF            15
#define L1F_DMA_RREQ_PRI_DATA           BIT_10      /* 0:tpd, 1:data */
#define L1F_DMA_WREQ_BLEN_MASK          SHIFT7(7UL)
#define L1F_DMA_WREQ_BLEN_SHIFT         7
#define L1F_DMA_RREQ_BLEN_MASK          SHIFT4(7UL)
#define L1F_DMA_RREQ_BLEN_SHIFT         4
#define L1F_DMA_PENDING_AUTO_RST        BIT_3
#define L1F_DMA_RORDER_MODE_MASK        SHIFT0(7UL)
#define L1F_DMA_RORDER_MODE_SHIFT       0
#define L1F_DMA_RORDER_MODE_OUT         4
#define L1F_DMA_RORDER_MODE_ENHANCE     2
#define L1F_DMA_RORDER_MODE_IN          1

#define L1F_WOL0                        0x14A0
#define L1F_WOL0_PT7_MATCH              BIT_31
#define L1F_WOL0_PT6_MATCH              BIT_30
#define L1F_WOL0_PT5_MATCH              BIT_29
#define L1F_WOL0_PT4_MATCH              BIT_28
#define L1F_WOL0_PT3_MATCH              BIT_27
#define L1F_WOL0_PT2_MATCH              BIT_26
#define L1F_WOL0_PT1_MATCH              BIT_25
#define L1F_WOL0_PT0_MATCH              BIT_24
#define L1F_WOL0_PT7_EN                 BIT_23
#define L1F_WOL0_PT6_EN                 BIT_22
#define L1F_WOL0_PT5_EN                 BIT_21
#define L1F_WOL0_PT4_EN                 BIT_20
#define L1F_WOL0_PT3_EN                 BIT_19
#define L1F_WOL0_PT2_EN                 BIT_18
#define L1F_WOL0_PT1_EN                 BIT_17
#define L1F_WOL0_PT0_EN                 BIT_16
#define L1F_WOL0_IPV4_SYNC_EVT          BIT_14
#define L1F_WOL0_IPV6_SYNC_EVT          BIT_13
#define L1F_WOL0_LINK_EVT               BIT_10
#define L1F_WOL0_MAGIC_EVT              BIT_9
#define L1F_WOL0_PATTERN_EVT            BIT_8
#define L1F_WOL0_OOB_EN                 BIT_6
#define L1F_WOL0_PME_LINK               BIT_5
#define L1F_WOL0_LINK_EN                BIT_4
#define L1F_WOL0_PME_MAGIC_EN           BIT_3
#define L1F_WOL0_MAGIC_EN               BIT_2
#define L1F_WOL0_PME_PATTERN_EN         BIT_1
#define L1F_WOL0_PATTERN_EN             BIT_0

#define L1F_WOL1                        0x14A4
#define L1F_WOL1_PT3_LEN_MASK           SHIFT24(0xFFUL)
#define L1F_WOL1_PT3_LEN_SHIFT          24
#define L1F_WOL1_PT2_LEN_MASK           SHIFT16(0xFFUL)
#define L1F_WOL1_PT2_LEN_SHIFT          16
#define L1F_WOL1_PT1_LEN_MASK           SHIFT8(0xFFUL)
#define L1F_WOL1_PT1_LEN_SHIFT          8
#define L1F_WOL1_PT0_LEN_MASK           SHIFT0(0xFFUL)
#define L1F_WOL1_PT0_LEN_SHIFT          0

#define L1F_WOL2                        0x14A8
#define L1F_WOL2_PT7_LEN_MASK           SHIFT24(0xFFUL)
#define L1F_WOL2_PT7_LEN_SHIFT          24
#define L1F_WOL2_PT6_LEN_MASK           SHIFT16(0xFFUL)
#define L1F_WOL2_PT6_LEN_SHIFT          16
#define L1F_WOL2_PT5_LEN_MASK           SHIFT8(0xFFUL)
#define L1F_WOL2_PT5_LEN_SHIFT          8
#define L1F_WOL2_PT4_LEN_MASK           SHIFT0(0xFFUL)
#define L1F_WOL2_PT4_LEN_SHIFT          0

#define L1F_RFD_PIDX                    0x15E0
#define L1F_RFD_PIDX_MASK               SHIFT0(0xFFFUL)
#define L1F_RFD_PIDX_SHIFT              0

#define L1F_RFD_CIDX                    0x15F8
#define L1F_RFD_CIDX_MASK               SHIFT0(0xFFFUL)
#define L1F_RFD_CIDX_SHIFT              0

/* MIB */
#define L1F_MIB_BASE                    0x1700
#define L1F_MIB_RX_OK                   (L1F_MIB_BASE + 0)
#define L1F_MIB_RX_BC                   (L1F_MIB_BASE + 4)
#define L1F_MIB_RX_MC                   (L1F_MIB_BASE + 8)
#define L1F_MIB_RX_PAUSE                (L1F_MIB_BASE + 12)
#define L1F_MIB_RX_CTRL                 (L1F_MIB_BASE + 16)
#define L1F_MIB_RX_FCS                  (L1F_MIB_BASE + 20)
#define L1F_MIB_RX_LENERR               (L1F_MIB_BASE + 24)
#define L1F_MIB_RX_BYTCNT               (L1F_MIB_BASE + 28)
#define L1F_MIB_RX_RUNT                 (L1F_MIB_BASE + 32)
#define L1F_MIB_RX_FRAGMENT             (L1F_MIB_BASE + 36)
#define L1F_MIB_RX_64B                  (L1F_MIB_BASE + 40)
#define L1F_MIB_RX_127B                 (L1F_MIB_BASE + 44)
#define L1F_MIB_RX_255B                 (L1F_MIB_BASE + 48)
#define L1F_MIB_RX_511B                 (L1F_MIB_BASE + 52)
#define L1F_MIB_RX_1023B                (L1F_MIB_BASE + 56)
#define L1F_MIB_RX_1518B                (L1F_MIB_BASE + 60)
#define L1F_MIB_RX_SZMAX                (L1F_MIB_BASE + 64)
#define L1F_MIB_RX_OVSZ                 (L1F_MIB_BASE + 68)
#define L1F_MIB_RXF_OV                  (L1F_MIB_BASE + 72)
#define L1F_MIB_RRD_OV                  (L1F_MIB_BASE + 76)
#define L1F_MIB_RX_ALIGN                (L1F_MIB_BASE + 80)
#define L1F_MIB_RX_BCCNT                (L1F_MIB_BASE + 84)
#define L1F_MIB_RX_MCCNT                (L1F_MIB_BASE + 88)
#define L1F_MIB_RX_ERRADDR              (L1F_MIB_BASE + 92)
#define L1F_MIB_TX_OK                   (L1F_MIB_BASE + 96)
#define L1F_MIB_TX_BC                   (L1F_MIB_BASE + 100)
#define L1F_MIB_TX_MC                   (L1F_MIB_BASE + 104)
#define L1F_MIB_TX_PAUSE                (L1F_MIB_BASE + 108)
#define L1F_MIB_TX_EXCDEFER             (L1F_MIB_BASE + 112)
#define L1F_MIB_TX_CTRL                 (L1F_MIB_BASE + 116)
#define L1F_MIB_TX_DEFER                (L1F_MIB_BASE + 120)
#define L1F_MIB_TX_BYTCNT               (L1F_MIB_BASE + 124)
#define L1F_MIB_TX_64B                  (L1F_MIB_BASE + 128)
#define L1F_MIB_TX_127B                 (L1F_MIB_BASE + 132)
#define L1F_MIB_TX_255B                 (L1F_MIB_BASE + 136)
#define L1F_MIB_TX_511B                 (L1F_MIB_BASE + 140)
#define L1F_MIB_TX_1023B                (L1F_MIB_BASE + 144)
#define L1F_MIB_TX_1518B                (L1F_MIB_BASE + 148)
#define L1F_MIB_TX_SZMAX                (L1F_MIB_BASE + 152)
#define L1F_MIB_TX_1COL                 (L1F_MIB_BASE + 156)
#define L1F_MIB_TX_2COL                 (L1F_MIB_BASE + 160)
#define L1F_MIB_TX_LATCOL               (L1F_MIB_BASE + 164)
#define L1F_MIB_TX_ABRTCOL              (L1F_MIB_BASE + 168)
#define L1F_MIB_TX_UNDRUN               (L1F_MIB_BASE + 172)
#define L1F_MIB_TX_TRDBEOP              (L1F_MIB_BASE + 176)
#define L1F_MIB_TX_LENERR               (L1F_MIB_BASE + 180)
#define L1F_MIB_TX_TRUNC                (L1F_MIB_BASE + 184)
#define L1F_MIB_TX_BCCNT                (L1F_MIB_BASE + 188)
#define L1F_MIB_TX_MCCNT                (L1F_MIB_BASE + 192)
#define L1F_MIB_UPDATE                  (L1F_MIB_BASE + 196)

/******************************************************************************/

#define L1F_ISR                         0x1600
#define L1F_ISR_DIS                     BIT_31
#define L1F_ISR_RX_Q7                   BIT_30
#define L1F_ISR_RX_Q6                   BIT_29
#define L1F_ISR_RX_Q5                   BIT_28
#define L1F_ISR_RX_Q4                   BIT_27
#define L1F_ISR_PCIE_LNKDOWN            BIT_26
#define L1F_ISR_PCIE_CERR               BIT_25
#define L1F_ISR_PCIE_NFERR              BIT_24
#define L1F_ISR_PCIE_FERR               BIT_23
#define L1F_ISR_PCIE_UR                 BIT_22
#define L1F_ISR_MAC_TX                  BIT_21
#define L1F_ISR_MAC_RX                  BIT_20
#define L1F_ISR_RX_Q3                   BIT_19
#define L1F_ISR_RX_Q2                   BIT_18
#define L1F_ISR_RX_Q1                   BIT_17
#define L1F_ISR_RX_Q0                   BIT_16
#define L1F_ISR_TX_Q0                   BIT_15
#define L1F_ISR_TXQ_TO                  BIT_14
#define L1F_ISR_PHY_LPW                 BIT_13
#define L1F_ISR_PHY                     BIT_12
#define L1F_ISR_TX_CREDIT               BIT_11
#define L1F_ISR_DMAW                    BIT_10
#define L1F_ISR_DMAR                    BIT_9
#define L1F_ISR_TXF_UR                  BIT_8
#define L1F_ISR_TX_Q3                   BIT_7
#define L1F_ISR_TX_Q2                   BIT_6
#define L1F_ISR_TX_Q1                   BIT_5
#define L1F_ISR_RFD_UR                  BIT_4
#define L1F_ISR_RXF_OV                  BIT_3
#define L1F_ISR_MANU                    BIT_2
#define L1F_ISR_TIMER                   BIT_1
#define L1F_ISR_SMB                     BIT_0

#define L1F_IMR                         0x1604

#define L1F_INT_RETRIG                  0x1608  /* re-send deassrt/assert
						 * if sw no reflect */
#define L1F_INT_RETRIG_TIMER_MASK       SHIFT0(0xFFFFUL)
#define L1F_INT_RETRIG_TIMER_SHIFT      0
#define L1F_INT_RETRIG_TO               20000   /* 40ms */

#define L1F_INT_DEASST_TIMER            0x1614  /* re-send deassert
						 * if sw no reflect */

#define L1F_PATTERN_MASK                0x1620  /* 128bytes, sleep state */
#define L1F_PATTERN_MASK_LEN            128


#define L1F_FLT1_SRC_IP0                0x1A00
#define L1F_FLT1_SRC_IP1                0x1A04
#define L1F_FLT1_SRC_IP2                0x1A08
#define L1F_FLT1_SRC_IP3                0x1A0C
#define L1F_FLT1_DST_IP0                0x1A10
#define L1F_FLT1_DST_IP1                0x1A14
#define L1F_FLT1_DST_IP2                0x1A18
#define L1F_FLT1_DST_IP3                0x1A1C
#define L1F_FLT1_PORT                   0x1A20
#define L1F_FLT1_PORT_DST_MASK          SHIFT16(0xFFFFUL)
#define L1F_FLT1_PORT_DST_SHIFT         16
#define L1F_FLT1_PORT_SRC_MASK          SHIFT0(0xFFFFUL)
#define L1F_FLT1_PORT_SRC_SHIFT         0

#define L1F_FLT2_SRC_IP0                0x1A24
#define L1F_FLT2_SRC_IP1                0x1A28
#define L1F_FLT2_SRC_IP2                0x1A2C
#define L1F_FLT2_SRC_IP3                0x1A30
#define L1F_FLT2_DST_IP0                0x1A34
#define L1F_FLT2_DST_IP1                0x1A38
#define L1F_FLT2_DST_IP2                0x1A40
#define L1F_FLT2_DST_IP3                0x1A44
#define L1F_FLT2_PORT                   0x1A48
#define L1F_FLT2_PORT_DST_MASK          SHIFT16(0xFFFFUL)
#define L1F_FLT2_PORT_DST_SHIFT         16
#define L1F_FLT2_PORT_SRC_MASK          SHIFT0(0xFFFFUL)
#define L1F_FLT2_PORT_SRC_SHIFT         0

#define L1F_FLT3_SRC_IP0                0x1A4C
#define L1F_FLT3_SRC_IP1                0x1A50
#define L1F_FLT3_SRC_IP2                0x1A54
#define L1F_FLT3_SRC_IP3                0x1A58
#define L1F_FLT3_DST_IP0                0x1A5C
#define L1F_FLT3_DST_IP1                0x1A60
#define L1F_FLT3_DST_IP2                0x1A64
#define L1F_FLT3_DST_IP3                0x1A68
#define L1F_FLT3_PORT                   0x1A6C
#define L1F_FLT3_PORT_DST_MASK          SHIFT16(0xFFFFUL)
#define L1F_FLT3_PORT_DST_SHIFT         16
#define L1F_FLT3_PORT_SRC_MASK          SHIFT0(0xFFFFUL)
#define L1F_FLT3_PORT_SRC_SHIFT         0

#define L1F_FLT4_SRC_IP0                0x1A70
#define L1F_FLT4_SRC_IP1                0x1A74
#define L1F_FLT4_SRC_IP2                0x1A78
#define L1F_FLT4_SRC_IP3                0x1A7C
#define L1F_FLT4_DST_IP0                0x1A80
#define L1F_FLT4_DST_IP1                0x1A84
#define L1F_FLT4_DST_IP2                0x1A88
#define L1F_FLT4_DST_IP3                0x1A8C
#define L1F_FLT4_PORT                   0x1A90
#define L1F_FLT4_PORT_DST_MASK          SHIFT16(0xFFFFUL)
#define L1F_FLT4_PORT_DST_SHIFT         16
#define L1F_FLT4_PORT_SRC_MASK          SHIFT0(0xFFFFUL)
#define L1F_FLT4_PORT_SRC_SHIFT         0

#define L1F_FLT5_SRC_IP0                0x1A94
#define L1F_FLT5_SRC_IP1                0x1A98
#define L1F_FLT5_SRC_IP2                0x1A9C
#define L1F_FLT5_SRC_IP3                0x1AA0
#define L1F_FLT5_DST_IP0                0x1AA4
#define L1F_FLT5_DST_IP1                0x1AA8
#define L1F_FLT5_DST_IP2                0x1AAC
#define L1F_FLT5_DST_IP3                0x1AB0
#define L1F_FLT5_PORT                   0x1AB4
#define L1F_FLT5_PORT_DST_MASK          SHIFT16(0xFFFFUL)
#define L1F_FLT5_PORT_DST_SHIFT         16
#define L1F_FLT5_PORT_SRC_MASK          SHIFT0(0xFFFFUL)
#define L1F_FLT5_PORT_SRC_SHIFT         0

#define L1F_FLT6_SRC_IP0                0x1AB8
#define L1F_FLT6_SRC_IP1                0x1ABC
#define L1F_FLT6_SRC_IP2                0x1AC0
#define L1F_FLT6_SRC_IP3                0x1AC8
#define L1F_FLT6_DST_IP0                0x1620  /* only S0 state */
#define L1F_FLT6_DST_IP1                0x1624
#define L1F_FLT6_DST_IP2                0x1628
#define L1F_FLT6_DST_IP3                0x162C
#define L1F_FLT6_PORT                   0x1630
#define L1F_FLT6_PORT_DST_MASK          SHIFT16(0xFFFFUL)
#define L1F_FLT6_PORT_DST_SHIFT         16
#define L1F_FLT6_PORT_SRC_MASK          SHIFT0(0xFFFFUL)
#define L1F_FLT6_PORT_SRC_SHIFT         0

#define L1F_FLTCTRL                     0x1634
#define L1F_FLTCTRL_PSTHR_TIMER_MASK    SHIFT24(0xFFUL)
#define L1F_FLTCTRL_PSTHR_TIMER_SHIFT   24
#define L1F_FLTCTRL_CHK_DSTPRT6         BIT_23
#define L1F_FLTCTRL_CHK_SRCPRT6         BIT_22
#define L1F_FLTCTRL_CHK_DSTIP6          BIT_21
#define L1F_FLTCTRL_CHK_SRCIP6          BIT_20
#define L1F_FLTCTRL_CHK_DSTPRT5         BIT_19
#define L1F_FLTCTRL_CHK_SRCPRT5         BIT_18
#define L1F_FLTCTRL_CHK_DSTIP5          BIT_17
#define L1F_FLTCTRL_CHK_SRCIP5          BIT_16
#define L1F_FLTCTRL_CHK_DSTPRT4         BIT_15
#define L1F_FLTCTRL_CHK_SRCPRT4         BIT_14
#define L1F_FLTCTRL_CHK_DSTIP4          BIT_13
#define L1F_FLTCTRL_CHK_SRCIP4          BIT_12
#define L1F_FLTCTRL_CHK_DSTPRT3         BIT_11
#define L1F_FLTCTRL_CHK_SRCPRT3         BIT_10
#define L1F_FLTCTRL_CHK_DSTIP3          BIT_9
#define L1F_FLTCTRL_CHK_SRCIP3          BIT_8
#define L1F_FLTCTRL_CHK_DSTPRT2         BIT_7
#define L1F_FLTCTRL_CHK_SRCPRT2         BIT_6
#define L1F_FLTCTRL_CHK_DSTIP2          BIT_5
#define L1F_FLTCTRL_CHK_SRCIP2          BIT_4
#define L1F_FLTCTRL_CHK_DSTPRT1         BIT_3
#define L1F_FLTCTRL_CHK_SRCPRT1         BIT_2
#define L1F_FLTCTRL_CHK_DSTIP1          BIT_1
#define L1F_FLTCTRL_CHK_SRCIP1          BIT_0

#define L1F_DROP_ALG1                   0x1638
#define L1F_DROP_ALG1_BWCHGVAL_MASK     SHIFT12(0xFFFFFUL)
#define L1F_DROP_ALG1_BWCHGVAL_SHIFT    12
#define L1F_DROP_ALG1_BWCHGSCL_6        BIT_11      /* 0:3.125%, 1:6.25% */
#define L1F_DROP_ALG1_ASUR_LWQ_EN       BIT_10
#define L1F_DROP_ALG1_BWCHGVAL_EN       BIT_9
#define L1F_DROP_ALG1_BWCHGSCL_EN       BIT_8
#define L1F_DROP_ALG1_PSTHR_AUTO        BIT_7       /* 0:manual, 1:auto */
#define L1F_DROP_ALG1_MIN_PSTHR_MASK    SHIFT5(3UL)
#define L1F_DROP_ALG1_MIN_PSTHR_SHIFT   5
#define L1F_DROP_ALG1_MIN_PSTHR_1_16    0
#define L1F_DROP_ALG1_MIN_PSTHR_1_8     1
#define L1F_DROP_ALG1_MIN_PSTHR_1_4     2
#define L1F_DROP_ALG1_MIN_PSTHR_1_2     3
#define L1F_DROP_ALG1_PSCL_MASK         SHIFT3(3UL)
#define L1F_DROP_ALG1_PSCL_SHIFT        3
#define L1F_DROP_ALG1_PSCL_1_4          0
#define L1F_DROP_ALG1_PSCL_1_8          1
#define L1F_DROP_ALG1_PSCL_1_16         2
#define L1F_DROP_ALG1_PSCL_1_32         3
#define L1F_DROP_ALG1_TIMESLOT_MASK     SHIFT0(7UL)
#define L1F_DROP_ALG1_TIMESLOT_SHIFT    0
#define L1F_DROP_ALG1_TIMESLOT_4MS      0
#define L1F_DROP_ALG1_TIMESLOT_8MS      1
#define L1F_DROP_ALG1_TIMESLOT_16MS     2
#define L1F_DROP_ALG1_TIMESLOT_32MS     3
#define L1F_DROP_ALG1_TIMESLOT_64MS     4
#define L1F_DROP_ALG1_TIMESLOT_128MS    5
#define L1F_DROP_ALG1_TIMESLOT_256MS    6
#define L1F_DROP_ALG1_TIMESLOT_512MS    7

#define L1F_DROP_ALG2                   0x163C
#define L1F_DROP_ALG2_SMPLTIME_MASK     SHIFT24(0xFUL)
#define L1F_DROP_ALG2_SMPLTIME_SHIFT    24
#define L1F_DROP_ALG2_LWQBW_MASK        SHIFT0(0xFFFFFFUL)
#define L1F_DROP_ALG2_LWQBW_SHIFT       0

#define L1F_SMB_TIMER                   0x15C4

#define L1F_TINT_TPD_THRSHLD            0x15C8

#define L1F_TINT_TIMER                  0x15CC

#define L1F_CLK_GATE                    0x1814
#define L1F_CLK_GATE_125M_SW_DIS_CR     BIT_8       /* B0 */
#define L1F_CLK_GATE_125M_SW_AZ         BIT_7       /* B0 */
#define L1F_CLK_GATE_125M_SW_IDLE       BIT_6       /* B0 */
#define L1F_CLK_GATE_RXMAC              BIT_5
#define L1F_CLK_GATE_TXMAC              BIT_4
#define L1F_CLK_GATE_RXQ                BIT_3
#define L1F_CLK_GATE_TXQ                BIT_2
#define L1F_CLK_GATE_DMAR               BIT_1
#define L1F_CLK_GATE_DMAW               BIT_0
#define L1F_CLK_GATE_ALL_A0         (\
	L1F_CLK_GATE_RXMAC          |\
	L1F_CLK_GATE_TXMAC          |\
	L1F_CLK_GATE_RXQ            |\
	L1F_CLK_GATE_TXQ            |\
	L1F_CLK_GATE_DMAR           |\
	L1F_CLK_GATE_DMAW)
#define L1F_CLK_GATE_ALL_B0         (\
	L1F_CLK_GATE_ALL_A0         |\
	L1F_CLK_GATE_125M_SW_AZ     |\
	L1F_CLK_GATE_125M_SW_IDLE)





#define L1F_BTROM_CFG                   0x1800          /* pwon rst */

#define L1F_DRV                         0x1804
/* bit definition is in lx_hwcomm.h */

#define L1F_DRV_ERR1                    0x1808          /* perst */
#define L1F_DRV_ERR1_GEN                BIT_31          /* geneneral err */
#define L1F_DRV_ERR1_NOR                BIT_30          /* rrd.nor */
#define L1F_DRV_ERR1_TRUNC              BIT_29
#define L1F_DRV_ERR1_RES                BIT_28
#define L1F_DRV_ERR1_INTFATAL           BIT_27
#define L1F_DRV_ERR1_TXQPEND            BIT_26
#define L1F_DRV_ERR1_DMAW               BIT_25
#define L1F_DRV_ERR1_DMAR               BIT_24
#define L1F_DRV_ERR1_PCIELNKDWN         BIT_23
#define L1F_DRV_ERR1_PKTSIZE            BIT_22
#define L1F_DRV_ERR1_FIFOFUL            BIT_21
#define L1F_DRV_ERR1_RFDUR              BIT_20
#define L1F_DRV_ERR1_RRDSI              BIT_19
#define L1F_DRV_ERR1_UPDATE             BIT_18

#define L1F_DRV_ERR2                    0x180C

#define L1F_DBG_ADDR                    0x1900  /* DWORD reg */
#define L1F_DBG_DATA                    0x1904  /* DWORD reg */

#define L1F_SYNC_IPV4_SA                0x1A00
#define L1F_SYNC_IPV4_DA                0x1A04

#define L1F_SYNC_V4PORT                 0x1A08
#define L1F_SYNC_V4PORT_DST_MASK        SHIFT16(0xFFFFUL)
#define L1F_SYNC_V4PORT_DST_SHIFT       16
#define L1F_SYNC_V4PORT_SRC_MASK        SHIFT0(0xFFFFUL)
#define L1F_SYNC_V4PORT_SRC_SHIFT       0

#define L1F_SYNC_IPV6_SA0               0x1A0C
#define L1F_SYNC_IPV6_SA1               0x1A10
#define L1F_SYNC_IPV6_SA2               0x1A14
#define L1F_SYNC_IPV6_SA3               0x1A18
#define L1F_SYNC_IPV6_DA0               0x1A1C
#define L1F_SYNC_IPV6_DA1               0x1A20
#define L1F_SYNC_IPV6_DA2               0x1A24
#define L1F_SYNC_IPV6_DA3               0x1A28

#define L1F_SYNC_V6PORT                 0x1A2C
#define L1F_SYNC_V6PORT_DST_MASK        SHIFT16(0xFFFFUL)
#define L1F_SYNC_V6PORT_DST_SHIFT       16
#define L1F_SYNC_V6PORT_SRC_MASK        SHIFT0(0xFFFFUL)
#define L1F_SYNC_V6PORT_SRC_SHIFT       0

#define L1F_ARP_REMOTE_IPV4             0x1A30
#define L1F_ARP_HOST_IPV4               0x1A34
#define L1F_ARP_MAC0                    0x1A38
#define L1F_ARP_MAC1                    0x1A3C

#define L1F_1ST_REMOTE_IPV6_0           0x1A40
#define L1F_1ST_REMOTE_IPV6_1           0x1A44
#define L1F_1ST_REMOTE_IPV6_2           0x1A48
#define L1F_1ST_REMOTE_IPV6_3           0x1A4C

#define L1F_1ST_SN_IPV6_0               0x1A50
#define L1F_1ST_SN_IPV6_1               0x1A54
#define L1F_1ST_SN_IPV6_2               0x1A58
#define L1F_1ST_SN_IPV6_3               0x1A5C

#define L1F_1ST_TAR_IPV6_1_0            0x1A60
#define L1F_1ST_TAR_IPV6_1_1            0x1A64
#define L1F_1ST_TAR_IPV6_1_2            0x1A68
#define L1F_1ST_TAR_IPV6_1_3            0x1A6C
#define L1F_1ST_TAR_IPV6_2_0            0x1A70
#define L1F_1ST_TAR_IPV6_2_1            0x1A74
#define L1F_1ST_TAR_IPV6_2_2            0x1A78
#define L1F_1ST_TAR_IPV6_2_3            0x1A7C

#define L1F_2ND_REMOTE_IPV6_0           0x1A80
#define L1F_2ND_REMOTE_IPV6_1           0x1A84
#define L1F_2ND_REMOTE_IPV6_2           0x1A88
#define L1F_2ND_REMOTE_IPV6_3           0x1A8C

#define L1F_2ND_SN_IPV6_0               0x1A90
#define L1F_2ND_SN_IPV6_1               0x1A94
#define L1F_2ND_SN_IPV6_2               0x1A98
#define L1F_2ND_SN_IPV6_3               0x1A9C

#define L1F_2ND_TAR_IPV6_1_0            0x1AA0
#define L1F_2ND_TAR_IPV6_1_1            0x1AA4
#define L1F_2ND_TAR_IPV6_1_2            0x1AA8
#define L1F_2ND_TAR_IPV6_1_3            0x1AAC
#define L1F_2ND_TAR_IPV6_2_0            0x1AB0
#define L1F_2ND_TAR_IPV6_2_1            0x1AB4
#define L1F_2ND_TAR_IPV6_2_2            0x1AB8
#define L1F_2ND_TAR_IPV6_2_3            0x1ABC

#define L1F_1ST_NS_MAC0                 0x1AC0
#define L1F_1ST_NS_MAC1                 0x1AC4

#define L1F_2ND_NS_MAC0                 0x1AC8
#define L1F_2ND_NS_MAC1                 0x1ACC

#define L1F_PMOFLD                      0x144C
#define L1F_PMOFLD_ECMA_IGNR_FRG_SSSR   BIT_11  /* B0 */
#define L1F_PMOFLD_ARP_CNFLCT_WAKEUP    BIT_10  /* B0 */
#define L1F_PMOFLD_MULTI_SOLD           BIT_9
#define L1F_PMOFLD_ICMP_XSUM            BIT_8
#define L1F_PMOFLD_GARP_REPLY           BIT_7
#define L1F_PMOFLD_SYNCV6_ANY           BIT_6
#define L1F_PMOFLD_SYNCV4_ANY           BIT_5
#define L1F_PMOFLD_BY_HW                BIT_4
#define L1F_PMOFLD_NS_EN                BIT_3
#define L1F_PMOFLD_ARP_EN               BIT_2
#define L1F_PMOFLD_SYNCV6_EN            BIT_1
#define L1F_PMOFLD_SYNCV4_EN            BIT_0

#define L1F_RSS_KEY0                    0x14B0
#define L1F_RSS_KEY1                    0x14B4
#define L1F_RSS_KEY2                    0x14B8
#define L1F_RSS_KEY3                    0x14BC
#define L1F_RSS_KEY4                    0x14C0
#define L1F_RSS_KEY5                    0x14C4
#define L1F_RSS_KEY6                    0x14C8
#define L1F_RSS_KEY7                    0x14CC
#define L1F_RSS_KEY8                    0x14D0
#define L1F_RSS_KEY9                    0x14D4

#define L1F_RSS_IDT_TBL0                0x1B00
#define L1F_RSS_IDT_TBL1                0x1B04
#define L1F_RSS_IDT_TBL2                0x1B08
#define L1F_RSS_IDT_TBL3                0x1B0C
#define L1F_RSS_IDT_TBL4                0x1B10
#define L1F_RSS_IDT_TBL5                0x1B14
#define L1F_RSS_IDT_TBL6                0x1B18
#define L1F_RSS_IDT_TBL7                0x1B1C
#define L1F_RSS_IDT_TBL8                0x1B20
#define L1F_RSS_IDT_TBL9                0x1B24
#define L1F_RSS_IDT_TBL10               0x1B28
#define L1F_RSS_IDT_TBL11               0x1B2C
#define L1F_RSS_IDT_TBL12               0x1B30
#define L1F_RSS_IDT_TBL13               0x1B34
#define L1F_RSS_IDT_TBL14               0x1B38
#define L1F_RSS_IDT_TBL15               0x1B3C
#define L1F_RSS_IDT_TBL16               0x1B40
#define L1F_RSS_IDT_TBL17               0x1B44
#define L1F_RSS_IDT_TBL18               0x1B48
#define L1F_RSS_IDT_TBL19               0x1B4C
#define L1F_RSS_IDT_TBL20               0x1B50
#define L1F_RSS_IDT_TBL21               0x1B54
#define L1F_RSS_IDT_TBL22               0x1B58
#define L1F_RSS_IDT_TBL23               0x1B5C
#define L1F_RSS_IDT_TBL24               0x1B60
#define L1F_RSS_IDT_TBL25               0x1B64
#define L1F_RSS_IDT_TBL26               0x1B68
#define L1F_RSS_IDT_TBL27               0x1B6C
#define L1F_RSS_IDT_TBL28               0x1B70
#define L1F_RSS_IDT_TBL29               0x1B74
#define L1F_RSS_IDT_TBL30               0x1B78
#define L1F_RSS_IDT_TBL31               0x1B7C

#define L1F_RSS_HASH_VAL                0x15B0
#define L1F_RSS_HASH_FLAG               0x15B4

#define L1F_RSS_BASE_CPU_NUM            0x15B8

#define L1F_MSI_MAP_TBL1                0x15D0
#define L1F_MSI_MAP_TBL1_ALERT_MASK     SHIFT28(0xFUL)
#define L1F_MSI_MAP_TBL1_ALERT_SHIFT    28
#define L1F_MSI_MAP_TBL1_TIMER_MASK     SHIFT24(0xFUL)
#define L1F_MSI_MAP_TBL1_TIMER_SHIFT    24
#define L1F_MSI_MAP_TBL1_TXQ1_MASK      SHIFT20(0xFUL)
#define L1F_MSI_MAP_TBL1_TXQ1_SHIFT     20
#define L1F_MSI_MAP_TBL1_TXQ0_MASK      SHIFT16(0xFUL)
#define L1F_MSI_MAP_TBL1_TXQ0_SHIFT     16
#define L1F_MSI_MAP_TBL1_RXQ3_MASK      SHIFT12(0xFUL)
#define L1F_MSI_MAP_TBL1_RXQ3_SHIFT     12
#define L1F_MSI_MAP_TBL1_RXQ2_MASK      SHIFT8(0xFUL)
#define L1F_MSI_MAP_TBL1_RXQ2_SHIFT     8
#define L1F_MSI_MAP_TBL1_RXQ1_MASK      SHIFT4(0xFUL)
#define L1F_MSI_MAP_TBL1_RXQ1_SHIFT     4
#define L1F_MSI_MAP_TBL1_RXQ0_MASK      SHIFT0(0xFUL)
#define L1F_MSI_MAP_TBL1_RXQ0_SHIFT     0

#define L1F_MSI_MAP_TBL2                0x15D8
#define L1F_MSI_MAP_TBL2_PHY_MASK       SHIFT28(0xFUL)
#define L1F_MSI_MAP_TBL2_PHY_SHIFT      28
#define L1F_MSI_MAP_TBL2_SMB_MASK       SHIFT24(0xFUL)
#define L1F_MSI_MAP_TBL2_SMB_SHIFT      24
#define L1F_MSI_MAP_TBL2_TXQ3_MASK      SHIFT20(0xFUL)
#define L1F_MSI_MAP_TBL2_TXQ3_SHIFT     20
#define L1F_MSI_MAP_TBL2_TXQ2_MASK      SHIFT16(0xFUL)
#define L1F_MSI_MAP_TBL2_TXQ2_SHIFT     16
#define L1F_MSI_MAP_TBL2_RXQ7_MASK      SHIFT12(0xFUL)
#define L1F_MSI_MAP_TBL2_RXQ7_SHIFT     12
#define L1F_MSI_MAP_TBL2_RXQ6_MASK      SHIFT8(0xFUL)
#define L1F_MSI_MAP_TBL2_RXQ6_SHIFT     8
#define L1F_MSI_MAP_TBL2_RXQ5_MASK      SHIFT4(0xFUL)
#define L1F_MSI_MAP_TBL2_RXQ5_SHIFT     4
#define L1F_MSI_MAP_TBL2_RXQ4_MASK      SHIFT0(0xFUL)
#define L1F_MSI_MAP_TBL2_RXQ4_SHIFT     0

#define L1F_MSI_ID_MAP                  0x15D4
#define L1F_MSI_ID_MAP_RXQ7             BIT_30
#define L1F_MSI_ID_MAP_RXQ6             BIT_29
#define L1F_MSI_ID_MAP_RXQ5             BIT_28
#define L1F_MSI_ID_MAP_RXQ4             BIT_27
#define L1F_MSI_ID_MAP_PCIELNKDW        BIT_26  /* 0:common,1:timer */
#define L1F_MSI_ID_MAP_PCIECERR         BIT_25
#define L1F_MSI_ID_MAP_PCIENFERR        BIT_24
#define L1F_MSI_ID_MAP_PCIEFERR         BIT_23
#define L1F_MSI_ID_MAP_PCIEUR           BIT_22
#define L1F_MSI_ID_MAP_MACTX            BIT_21
#define L1F_MSI_ID_MAP_MACRX            BIT_20
#define L1F_MSI_ID_MAP_RXQ3             BIT_19
#define L1F_MSI_ID_MAP_RXQ2             BIT_18
#define L1F_MSI_ID_MAP_RXQ1             BIT_17
#define L1F_MSI_ID_MAP_RXQ0             BIT_16
#define L1F_MSI_ID_MAP_TXQ0             BIT_15
#define L1F_MSI_ID_MAP_TXQTO            BIT_14
#define L1F_MSI_ID_MAP_LPW              BIT_13
#define L1F_MSI_ID_MAP_PHY              BIT_12
#define L1F_MSI_ID_MAP_TXCREDIT         BIT_11
#define L1F_MSI_ID_MAP_DMAW             BIT_10
#define L1F_MSI_ID_MAP_DMAR             BIT_9
#define L1F_MSI_ID_MAP_TXFUR            BIT_8
#define L1F_MSI_ID_MAP_TXQ3             BIT_7
#define L1F_MSI_ID_MAP_TXQ2             BIT_6
#define L1F_MSI_ID_MAP_TXQ1             BIT_5
#define L1F_MSI_ID_MAP_RFDUR            BIT_4
#define L1F_MSI_ID_MAP_RXFOV            BIT_3
#define L1F_MSI_ID_MAP_MANU             BIT_2
#define L1F_MSI_ID_MAP_TIMER            BIT_1
#define L1F_MSI_ID_MAP_SMB              BIT_0

#define L1F_MSI_RETRANS_TIMER           0x1920
#define L1F_MSI_MASK_SEL_LINE           BIT_16  /* 1:line,0:standard*/
#define L1F_MSI_RETRANS_TM_MASK         SHIFT0(0xFFFFUL)
#define L1F_MSI_RETRANS_TM_SHIFT        0

#define L1F_CR_DMA_CTRL                 0x1930
#define L1F_CR_DMA_CTRL_PRI             BIT_22
#define L1F_CR_DMA_CTRL_RRDRXD_JOINT    BIT_21
#define L1F_CR_DMA_CTRL_BWCREDIT_MASK   SHIFT_19(0x3UL)
#define L1F_CR_DMA_CTRL_BWCREDIT_SHIFT  19
#define L1F_CR_DMA_CTRL_BWCREDIT_2KB    0
#define L1F_CR_DMA_CTRL_BWCREDIT_1KB    1
#define L1F_CR_DMA_CTRL_BWCREDIT_4KB    2
#define L1F_CR_DMA_CTRL_BWCREDIT_8KB    3
#define L1F_CR_DMA_CTRL_BW_EN           BIT_18
#define L1F_CR_DMA_CTRL_BW_RATIO_MASK   SHIFT_16(0x3UL)
#define L1F_CR_DMA_CTRL_BW_RATIO_1_2    0
#define L1F_CR_DMA_CTRL_BW_RATIO_1_4    1
#define L1F_CR_DMA_CTRL_BW_RATIO_1_8    2
#define L1F_CR_DMA_CTRL_BW_RATIO_2_1    3
#define L1F_CR_DMA_CTRL_SOFT_RST        BIT_11
#define L1F_CR_DMA_CTRL_TXEARLY_EN      BIT_10
#define L1F_CR_DMA_CTRL_RXEARLY_EN      BIT_9
#define L1F_CR_DMA_CTRL_WEARLY_EN       BIT_8
#define L1F_CR_DMA_CTRL_RXTH_MASK       SHIFT_4(0xFUL)
#define L1F_CR_DMA_CTRL_WTH_MASK        SHIFT_0(0xFUL)


#define L1F_EFUSE_BIST                  0x1934
#define L1F_EFUSE_BIST_COL_MASK         SHIFT24(0x3FUL)
#define L1F_EFUSE_BIST_COL_SHIFT        24
#define L1F_EFUSE_BIST_ROW_MASK         SHIFT12(0x7FUL)
#define L1F_EFUSE_BIST_ROW_SHIFT        12
#define L1F_EFUSE_BIST_STEP_MASK        SHIFT8(0xFUL)
#define L1F_EFUSE_BIST_STEP_SHIFT       8
#define L1F_EFUSE_BIST_PAT_MASK         SHIFT4(0x7UL)
#define L1F_EFUSE_BIST_PAT_SHIFT        4
#define L1F_EFUSE_BIST_CRITICAL         BIT_3
#define L1F_EFUSE_BIST_FIXED            BIT_2
#define L1F_EFUSE_BIST_FAIL             BIT_1
#define L1F_EFUSE_BIST_NOW              BIT_0

/* CR DMA ctrl */

/* TX QoS */
#define L1F_WRR                         0x1938
#define L1F_WRR_PRI_MASK                SHIFT29(3UL)
#define L1F_WRR_PRI_SHIFT               29
#define L1F_WRR_PRI_RESTRICT_ALL        0
#define L1F_WRR_PRI_RESTRICT_HI         1
#define L1F_WRR_PRI_RESTRICT_HI2        2
#define L1F_WRR_PRI_RESTRICT_NONE       3
#define L1F_WRR_PRI3_MASK               SHIFT24(0x1FUL)
#define L1F_WRR_PRI3_SHIFT              24
#define L1F_WRR_PRI2_MASK               SHIFT16(0x1FUL)
#define L1F_WRR_PRI2_SHIFT              16
#define L1F_WRR_PRI1_MASK               SHIFT8(0x1FUL)
#define L1F_WRR_PRI1_SHIFT              8
#define L1F_WRR_PRI0_MASK               SHIFT0(0x1FUL)
#define L1F_WRR_PRI0_SHIFT              0

#define L1F_HQTPD                       0x193C
#define L1F_HQTPD_BURST_EN              BIT_31
#define L1F_HQTPD_Q3_NUMPREF_MASK       SHIFT8(0xFUL)
#define L1F_HQTPD_Q3_NUMPREF_SHIFT      8
#define L1F_HQTPD_Q2_NUMPREF_MASK       SHIFT4(0xFUL)
#define L1F_HQTPD_Q2_NUMPREF_SHIFT      4
#define L1F_HQTPD_Q1_NUMPREF_MASK       SHIFT0(0xFUL)
#define L1F_HQTPD_Q1_NUMPREF_SHIFT      0

#define L1F_CPUMAP1                     0x19A0
#define L1F_CPUMAP1_VCT7_MASK           SHIFT28(0xFUL)
#define L1F_CPUMAP1_VCT7_SHIFT          28
#define L1F_CPUMAP1_VCT6_MASK           SHIFT24(0xFUL)
#define L1F_CPUMAP1_VCT6_SHIFT          24
#define L1F_CPUMAP1_VCT5_MASK           SHIFT20(0xFUL)
#define L1F_CPUMAP1_VCT5_SHIFT          20
#define L1F_CPUMAP1_VCT4_MASK           SHIFT16(0xFUL)
#define L1F_CPUMAP1_VCT4_SHIFT          16
#define L1F_CPUMAP1_VCT3_MASK           SHIFT12(0xFUL)
#define L1F_CPUMAP1_VCT3_SHIFT          12
#define L1F_CPUMAP1_VCT2_MASK           SHIFT8(0xFUL)
#define L1F_CPUMAP1_VCT2_SHIFT          8
#define L1F_CPUMAP1_VCT1_MASK           SHIFT4(0xFUL)
#define L1F_CPUMAP1_VCT1_SHIFT          4
#define L1F_CPUMAP1_VCT0_MASK           SHIFT0(0xFUL)
#define L1F_CPUMAP1_VCT0_SHIFT          0

#define L1F_CPUMAP2                     0x19A4
#define L1F_CPUMAP2_VCT15_MASK          SHIFT28(0xFUL)
#define L1F_CPUMAP2_VCT15_SHIFT         28
#define L1F_CPUMAP2_VCT14_MASK          SHIFT24(0xFUL)
#define L1F_CPUMAP2_VCT14_SHIFT         24
#define L1F_CPUMAP2_VCT13_MASK          SHIFT20(0xFUL)
#define L1F_CPUMAP2_VCT13_SHIFT         20
#define L1F_CPUMAP2_VCT12_MASK          SHIFT16(0xFUL)
#define L1F_CPUMAP2_VCT12_SHIFT         16
#define L1F_CPUMAP2_VCT11_MASK          SHIFT12(0xFUL)
#define L1F_CPUMAP2_VCT11_SHIFT         12
#define L1F_CPUMAP2_VCT10_MASK          SHIFT8(0xFUL)
#define L1F_CPUMAP2_VCT10_SHIFT         8
#define L1F_CPUMAP2_VCT9_MASK           SHIFT4(0xFUL)
#define L1F_CPUMAP2_VCT9_SHIFT          4
#define L1F_CPUMAP2_VCT8_MASK           SHIFT0(0xFUL)
#define L1F_CPUMAP2_VCT8_SHIFT          0

#define L1F_MISC                        0x19C0
#define L1F_MISC_MODU                   BIT_31  /* 0:vector,1:cpu */
#define L1F_MISC_OVERCUR                BIT_29
#define L1F_MISC_PSWR_EN                BIT_28
#define L1F_MISC_PSW_CTRL_MASK          SHIFT24(0xFUL)
#define L1F_MISC_PSW_CTRL_SHIFT         24
#define L1F_MISC_PSW_OCP_MASK           SHIFT21(7UL)
#define L1F_MISC_PSW_OCP_SHIFT          21
#define L1F_MISC_V18_HIGH               BIT_20
#define L1F_MISC_LPO_CTRL_MASK          SHIFT16(0xFUL)
#define L1F_MISC_LPO_CTRL_SHIFT         16
#define L1F_MISC_ISO_EN                 BIT_12
#define L1F_MISC_XSTANA_ALWAYS_ON       BIT_11
#define L1F_MISC_SYS25M_SEL_ADAPTIVE    BIT_10
#define L1F_MISC_SPEED_SIM              BIT_9
#define L1F_MISC_S1_LWP_EN              BIT_8
#define L1F_MISC_MACLPW                 BIT_7   /* pcie/mac do pwsaving
						 * as phy in lpw state */
#define L1F_MISC_125M_SW                BIT_6
#define L1F_MISC_INTNLOSC_OFF_EN        BIT_5
#define L1F_MISC_EXTN25M_SEL            BIT_4   /* 0:chipset,1:cystle */
#define L1F_MISC_INTNLOSC_OPEN          BIT_3
#define L1F_MISC_SMBUS_AT_LED           BIT_2
#define L1F_MISC_PPS_AT_LED_MASK        SHIFT0(3UL)
#define L1F_MISC_PPS_AT_LED_SHIFT       0
#define L1F_MISC_PPS_AT_LED_ACT         1
#define L1F_MISC_PPS_AT_LED_10_100      2
#define L1F_MISC_PPS_AT_LED_1000        3

#define L1F_MISC1                       0x19C4
#define L1F_MSC1_BLK_CRASPM_REQ         BIT_15

#define L1F_MISC3                       0x19CC
#define L1F_MISC3_25M_BY_SW             BIT_1   /* 1:Software control 25M */
#define L1F_MISC3_25M_NOTO_INTNL        BIT_0   /* 0:25M switch to intnl OSC */



/***************************** IO mapping registers ***************************/
#define L1F_IO_ADDR                     0x00    /* DWORD reg */
#define L1F_IO_DATA                     0x04    /* DWORD reg */
#define L1F_IO_MASTER                   0x08    /* DWORD same as reg0x1400 */
#define L1F_IO_MAC_CTRL                 0x0C    /* DWORD same as reg0x1480*/
#define L1F_IO_ISR                      0x10    /* DWORD same as reg0x1600 */
#define L1F_IO_IMR                      0x14    /* DWORD same as reg0x1604 */
#define L1F_IO_TPD_PRI1_PIDX            0x18    /* WORD same as reg0x15F0 */
#define L1F_IO_TPD_PRI0_PIDX            0x1A    /* WORD same as reg0x15F2 */
#define L1F_IO_TPD_PRI1_CIDX            0x1C    /* WORD same as reg0x15F4 */
#define L1F_IO_TPD_PRI0_CIDX            0x1E    /* WORD same as reg0x15F6 */
#define L1F_IO_RFD_PIDX                 0x20    /* WORD same as reg0x15E0 */
#define L1F_IO_RFD_CIDX                 0x30    /* WORD same as reg0x15F8 */
#define L1F_IO_MDIO                     0x38    /* WORD same as reg0x1414 */
#define L1F_IO_PHY_CTRL                 0x3C    /* DWORD same as reg0x140C */


/********************* PHY regs definition ***************************/

/* PHY Control Register */
#define L1F_MII_BMCR                        0x00
#define L1F_BMCR_SPEED_SELECT_MSB           0x0040
#define L1F_BMCR_COLL_TEST_ENABLE           0x0080
#define L1F_BMCR_FULL_DUPLEX                0x0100
#define L1F_BMCR_RESTART_AUTO_NEG           0x0200
#define L1F_BMCR_ISOLATE                    0x0400
#define L1F_BMCR_POWER_DOWN                 0x0800
#define L1F_BMCR_AUTO_NEG_EN                0x1000
#define L1F_BMCR_SPEED_SELECT_LSB           0x2000
#define L1F_BMCR_LOOPBACK                   0x4000
#define L1F_BMCR_RESET                      0x8000
#define L1F_BMCR_SPEED_MASK                 0x2040
#define L1F_BMCR_SPEED_1000                 0x0040
#define L1F_BMCR_SPEED_100                  0x2000
#define L1F_BMCR_SPEED_10                   0x0000

/* PHY Status Register */
#define L1F_MII_BMSR                        0x01
#define L1F_BMSR_EXTENDED_CAPS              0x0001
#define L1F_BMSR_JABBER_DETECT              0x0002
#define L1F_BMSR_LINK_STATUS                0x0004
#define L1F_BMSR_AUTONEG_CAPS               0x0008
#define L1F_BMSR_REMOTE_FAULT               0x0010
#define L1F_BMSR_AUTONEG_COMPLETE           0x0020
#define L1F_BMSR_PREAMBLE_SUPPRESS          0x0040
#define L1F_BMSR_EXTENDED_STATUS            0x0100
#define L1F_BMSR_100T2_HD_CAPS              0x0200
#define L1F_BMSR_100T2_FD_CAPS              0x0400
#define L1F_BMSR_10T_HD_CAPS                0x0800
#define L1F_BMSR_10T_FD_CAPS                0x1000
#define L1F_BMSR_100X_HD_CAPS               0x2000
#define L1F_BMMII_SR_100X_FD_CAPS           0x4000
#define L1F_BMMII_SR_100T4_CAPS             0x8000

#define L1F_MII_PHYSID1                     0x02
#define L1F_MII_PHYSID2                     0x03


/* Autoneg Advertisement Register */
#define L1F_MII_ADVERTISE                   0x04
#define L1F_ADVERTISE_SELECTOR_FIELD        0x0001
#define L1F_ADVERTISE_10T_HD_CAPS           0x0020
#define L1F_ADVERTISE_10T_FD_CAPS           0x0040
#define L1F_ADVERTISE_100TX_HD_CAPS         0x0080
#define L1F_ADVERTISE_100TX_FD_CAPS         0x0100
#define L1F_ADVERTISE_100T4_CAPS            0x0200
#define L1F_ADVERTISE_PAUSE                 0x0400
#define L1F_ADVERTISE_ASM_DIR               0x0800
#define L1F_ADVERTISE_REMOTE_FAULT          0x2000
#define L1F_ADVERTISE_NEXT_PAGE             0x8000
#define L1F_ADVERTISE_SPEED_MASK            0x01E0
#define L1F_ADVERTISE_DEFAULT_CAP           0x1DE0 /* diff with L1C */

/* Link partner ability register */
#define L1F_MII_LPA                         0x05
#define L1F_LPA_SLCT_MASK                   0x001F
#define L1F_LPA_10HALF                      0x0020
#define L1F_LPA_10FULL                      0x0040
#define L1F_LPA_100HALF                     0x0080
#define L1F_LPA_100FULL                     0x0100
#define L1F_LPA_100BASE4                    0x0200
#define L1F_LPA_PAUSE                       0x0400
#define L1F_LPA_ASYPAUSE                    0x0800
#define L1F_LPA_RFAULT                      0x2000
#define L1F_LPA_LPACK                       0x4000
#define L1F_LPA_NPAGE                       0x8000

/* Expansion register          */
#define L1F_MII_EXPANSION                   0x06
#define L1F_EXPANSION_NWAY                  0x0001
#define L1F_EXPANSION_LCWP                  0x0002
#define L1F_EXPANSION_ENABLENPAGE           0x0004
#define L1F_EXPANSION_NPCAPABLE             0x0008
#define L1F_EXPANSION_MFAULTS               0x0010
#define L1F_EXPANSION_RESV                  0xffe0

/* 1000BASE-T Control Register */
#define L1F_MII_GIGA_CR                     0x09
#define L1F_GIGA_CR_1000T_HD_CAPS           0x0100
#define L1F_GIGA_CR_1000T_FD_CAPS           0x0200
#define L1F_GIGA_CR_1000T_REPEATER_DTE      0x0400

#define L1F_GIGA_CR_1000T_MS_VALUE          0x0800

#define L1F_GIGA_CR_1000T_MS_ENABLE         0x1000

#define L1F_GIGA_CR_1000T_TEST_MODE_NORMAL  0x0000
#define L1F_GIGA_CR_1000T_TEST_MODE_1       0x2000
#define L1F_GIGA_CR_1000T_TEST_MODE_2       0x4000
#define L1F_GIGA_CR_1000T_TEST_MODE_3       0x6000
#define L1F_GIGA_CR_1000T_TEST_MODE_4       0x8000
#define L1F_GIGA_CR_1000T_SPEED_MASK        0x0300
#define L1F_GIGA_CR_1000T_DEFAULT_CAP       0x0300

/* 1000BASE-T Status Register */
#define L1F_MII_GIGA_SR                     0x0A

/* PHY Specific Status Register */
#define L1F_MII_GIGA_PSSR                   0x11
#define L1F_GIGA_PSSR_FC_RXEN               0x0004
#define L1F_GIGA_PSSR_FC_TXEN               0x0008
#define L1F_GIGA_PSSR_SPD_DPLX_RESOLVED     0x0800
#define L1F_GIGA_PSSR_DPLX                  0x2000
#define L1F_GIGA_PSSR_SPEED                 0xC000
#define L1F_GIGA_PSSR_10MBS                 0x0000
#define L1F_GIGA_PSSR_100MBS                0x4000
#define L1F_GIGA_PSSR_1000MBS               0x8000

/* PHY Interrupt Enable Register */
#define L1F_MII_IER                         0x12
#define L1F_IER_LINK_UP                     0x0400
#define L1F_IER_LINK_DOWN                   0x0800

/* PHY Interrupt Status Register */
#define L1F_MII_ISR                         0x13
#define L1F_ISR_LINK_UP                     0x0400
#define L1F_ISR_LINK_DOWN                   0x0800

/* Cable-Detect-Test Control Register */
#define L1F_MII_CDTC                        0x16
#define L1F_CDTC_EN                         1       /* sc */
#define L1F_CDTC_PAIR_MASK                  SHIFT8(3U)
#define L1F_CDTC_PAIR_SHIFT                 8


/* Cable-Detect-Test Status Register */
#define L1F_MII_CDTS                        0x1C
#define L1F_CDTS_STATUS_MASK                SHIFT8(3U)
#define L1F_CDTS_STATUS_SHIFT               8
#define L1F_CDTS_STATUS_NORMAL              0
#define L1F_CDTS_STATUS_SHORT               1
#define L1F_CDTS_STATUS_OPEN                2
#define L1F_CDTS_STATUS_INVALID             3

#define L1F_MII_DBG_ADDR                    0x1D
#define L1F_MII_DBG_DATA                    0x1E

/***************************** debug port *************************************/

#define L1F_MIIDBG_ANACTRL                  0x00
#define L1F_ANACTRL_CLK125M_DELAY_EN        BIT_15S
#define L1F_ANACTRL_VCO_FAST                BIT_14S
#define L1F_ANACTRL_VCO_SLOW                BIT_13S
#define L1F_ANACTRL_AFE_MODE_EN             BIT_12S
#define L1F_ANACTRL_LCKDET_PHY              BIT_11S
#define L1F_ANACTRL_LCKDET_EN               BIT_10S
#define L1F_ANACTRL_OEN_125M                BIT_9S
#define L1F_ANACTRL_HBIAS_EN                BIT_8S
#define L1F_ANACTRL_HB_EN                   BIT_7S
#define L1F_ANACTRL_SEL_HSP                 BIT_6S
#define L1F_ANACTRL_CLASSA_EN               BIT_5S
#define L1F_ANACTRL_MANUSWON_SWR_MASK       SHIFT2(3U)
#define L1F_ANACTRL_MANUSWON_SWR_SHIFT      2
#define L1F_ANACTRL_MANUSWON_SWR_2V         0
#define L1F_ANACTRL_MANUSWON_SWR_1P9V       1
#define L1F_ANACTRL_MANUSWON_SWR_1P8V       2
#define L1F_ANACTRL_MANUSWON_SWR_1P7V       3
#define L1F_ANACTRL_MANUSWON_BW3_4M         BIT_1S
#define L1F_ANACTRL_RESTART_CAL             BIT_0S
#define L1F_ANACTRL_DEF                     0x02EF
#if 0
(\
	L1F_ANACTRL_RESTART_CAL             |\
	L1F_ANACTRL_MANUSWON_BW3_4M         |\
	FIELDS(L1F_ANACTRL_MANUSWON_SWR, L1F_ANACTRL_MANUSWON_SWR_1P7V) |\
	L1F_ANACTRL_CLASSA_EN               |\
	L1F_ANACTRL_SEL_HSP                 |\
	L1F_ANACTRL_HB_EN                   |\
	L1F_ANACTRL_OEN_125M)
#endif


#define L1F_MIIDBG_SYSMODCTRL               0x04
#define L1F_SYSMODCTRL_IECHOADJ_PFMH_PHY    BIT_15S
#define L1F_SYSMODCTRL_IECHOADJ_BIASGEN     BIT_14S
#define L1F_SYSMODCTRL_IECHOADJ_PFML_PHY    BIT_13S
#define L1F_SYSMODCTRL_IECHOADJ_PS_MASK     SHIFT10(3U)
#define L1F_SYSMODCTRL_IECHOADJ_PS_SHIFT    10
#define L1F_SYSMODCTRL_IECHOADJ_PS_40       3
#define L1F_SYSMODCTRL_IECHOADJ_PS_20       2
#define L1F_SYSMODCTRL_IECHOADJ_PS_0        1
#define L1F_SYSMODCTRL_IECHOADJ_10BT_100MV  BIT_6S /* 1:100mv, 0:200mv */
#define L1F_SYSMODCTRL_IECHOADJ_HLFAP_MASK  SHIFT4(3U)
#define L1F_SYSMODCTRL_IECHOADJ_HLFAP_SHIFT 4
#define L1F_SYSMODCTRL_IECHOADJ_VDFULBW     BIT_3S
#define L1F_SYSMODCTRL_IECHOADJ_VDBIASHLF   BIT_2S
#define L1F_SYSMODCTRL_IECHOADJ_VDAMPHLF    BIT_1S
#define L1F_SYSMODCTRL_IECHOADJ_VDLANSW     BIT_0S
#define L1F_SYSMODCTRL_IECHOADJ_DEF         0xBB8B /* en half bias */
#if 0
(\
	L1F_SYSMODCTRL_IECHOADJ_VDLANSW     |\
	L1F_SYSMODCTRL_IECHOADJ_VDAMPHLF    |\
	L1F_SYSMODCTRL_IECHOADJ_VDFULBW     |\
	FIELDS(L1F_SYSMODCTRL_IECHOADJ_HLFAP, 3) |\
	FIELDS(L1F_SYSMODCTRL_IECHOADJ_PS, L1F_SYSMODCTRL_IECHOADJ_PS_20) |\
	L1F_SYSMODCTRL_IECHOADJ_PFMH_PHY)
#endif


#define L1F_MIIDBG_SRDSYSMOD                0x05
#define L1F_SRDSYSMOD_LCKDET_EN             BIT_13S
#define L1F_SRDSYSMOD_PLL_EN                BIT_11S
#define L1F_SRDSYSMOD_SEL_HSP               BIT_10S
#define L1F_SRDSYSMOD_HLFTXDR               BIT_9S
#define L1F_SRDSYSMOD_TXCLK_DELAY_EN        BIT_8S
#define L1F_SRDSYSMOD_TXELECIDLE            BIT_7S
#define L1F_SRDSYSMOD_DEEMP_EN              BIT_6S
#define L1F_SRDSYSMOD_MS_PAD                BIT_2S
#define L1F_SRDSYSMOD_CDR_ADC_VLTG          BIT_1S
#define L1F_SRDSYSMOD_CDR_DAC_1MA           BIT_0S
#define L1F_SRDSYSMOD_DEF                   0x2C46


#define L1F_MIIDBG_HIBNEG                   0x0B
#define L1F_HIBNEG_PSHIB_EN                 BIT_15S
#define L1F_HIBNEG_WAKE_BOTH                BIT_14S
#define L1F_HIBNEG_ONOFF_ANACHG_SUDEN       BIT_13S
#define L1F_HIBNEG_HIB_PULSE                BIT_12S
#define L1F_HIBNEG_GATE_25M_EN              BIT_11S
#define L1F_HIBNEG_RST_80U                  BIT_10S
#define L1F_HIBNEG_RST_TIMER_MASK           SHIFT8(3U)
#define L1F_HIBNEG_RST_TIMER_SHIFT          8
#define L1F_HIBNEG_GTX_CLK_DELAY_MASK       SHIFT5(3U)
#define L1F_HIBNEG_GTX_CLK_DELAY_SHIFT      5
#define L1F_HIBNEG_BYPSS_BRKTIMER           BIT_4S
#define L1F_HIBNEG_DEF                      0xBC40

#define L1F_MIIDBG_TST10BTCFG               0x12
#define L1F_TST10BTCFG_INTV_TIMER_MASK      SHIFT14(3U)
#define L1F_TST10BTCFG_INTV_TIMER_SHIFT     SHIFT14
#define L1F_TST10BTCFG_TRIGER_TIMER_MASK    SHIFT12(3U)
#define L1F_TST10BTCFG_TRIGER_TIMER_SHIFT   12
#define L1F_TST10BTCFG_DIV_MAN_MLT3_EN      BIT_11S
#define L1F_TST10BTCFG_OFF_DAC_IDLE         BIT_10S
#define L1F_TST10BTCFG_LPBK_DEEP            BIT_2S /* 1:deep,0:shallow */
#define L1F_TST10BTCFG_DEF                  0x4C04

#define L1F_MIIDBG_AZ_ANADECT               0x15
#define L1F_AZ_ANADECT_10BTRX_TH            BIT_15S
#define L1F_AZ_ANADECT_BOTH_01CHNL          BIT_14S
#define L1F_AZ_ANADECT_INTV_MASK            SHIFT8(0x3FU)
#define L1F_AZ_ANADECT_INTV_SHIFT           8
#define L1F_AZ_ANADECT_THRESH_MASK          SHIFT4(0xFU)
#define L1F_AZ_ANADECT_THRESH_SHIFT         4
#define L1F_AZ_ANADECT_CHNL_MASK            SHIFT0(0xFU)
#define L1F_AZ_ANADECT_CHNL_SHIFT           0
#define L1F_AZ_ANADECT_DEF                  0x3220
#define L1F_AZ_ANADECT_LONG                 0x3210

#define L1F_MIIDBG_AGC                      0x23
#define L1F_AGC_2_VGA_MASK                  SHIFT8(0x3FU)
#define L1F_AGC_2_VGA_SHIFT                 8
#define L1F_AGC_LONG1G_LIMT                 40
#define L1F_AGC_LONG100M_LIMT               44

#define L1F_MIIDBG_LEGCYPS                  0x29
#define L1F_LEGCYPS_EN                      BIT_15S
#define L1F_LEGCYPS_DAC_AMP1000_MASK        SHIFT12(7U)
#define L1F_LEGCYPS_DAC_AMP1000_SHIFT       12
#define L1F_LEGCYPS_DAC_AMP100_MASK         SHIFT9(7U)
#define L1F_LEGCYPS_DAC_AMP100_SHIFT        9
#define L1F_LEGCYPS_DAC_AMP10_MASK          SHIFT6(7U)
#define L1F_LEGCYPS_DAC_AMP10_SHIFT         6
#define L1F_LEGCYPS_UNPLUG_TIMER_MASK       SHIFT3(7U)
#define L1F_LEGCYPS_UNPLUG_TIMER_SHIFT      3
#define L1F_LEGCYPS_UNPLUG_DECT_EN          BIT_2S
#define L1F_LEGCYPS_ECNC_PS_EN              BIT_0S
#define L1F_LEGCYPS_DEF                     0x129D

#define L1F_MIIDBG_TST100BTCFG              0x36
#define L1F_TST100BTCFG_NORMAL_BW_EN        BIT_15S
#define L1F_TST100BTCFG_BADLNK_BYPASS       BIT_14S
#define L1F_TST100BTCFG_SHORTCABL_TH_MASK   SHIFT8(0x3FU)
#define L1F_TST100BTCFG_SHORTCABL_TH_SHIFT  8
#define L1F_TST100BTCFG_LITCH_EN            BIT_7S
#define L1F_TST100BTCFG_VLT_SW              BIT_6S
#define L1F_TST100BTCFG_LONGCABL_TH_MASK    SHIFT0(0x3FU)
#define L1F_TST100BTCFG_LONGCABL_TH_SHIFT   0
#define L1F_TST100BTCFG_DEF                 0xE12C

#define L1F_MIIDBG_GREENCFG                 0x3B
#define L1F_GREENCFG_MSTPS_MSETH2_MASK      SHIFT8(0xFFU)
#define L1F_GREENCFG_MSTPS_MSETH2_SHIFT     8
#define L1F_GREENCFG_MSTPS_MSETH1_MASK      SHIFT0(0xFFU)
#define L1F_GREENCFG_MSTPS_MSETH1_SHIFT     0
#define L1F_GREENCFG_DEF                    0x7078

#define L1F_MIIDBG_GREENCFG2                0x3D
#define L1F_GREENCFG2_GATE_DFSE_EN          BIT_7S


/***************************** extension **************************************/

/******* dev 3 *********/
#define L1F_MIIEXT_PCS                      3

#define L1F_MIIEXT_CLDCTRL6                 0x8006
#define L1F_CLDCTRL6_CAB_LEN_MASK           SHIFT0(0xFFU)
#define L1F_CLDCTRL6_CAB_LEN_SHIFT          0
#define L1F_CLDCTRL6_CAB_LEN_SHORT1G        116
#define L1F_CLDCTRL6_CAB_LEN_SHORT100M      152

#define L1F_MIIEXT_CLDCTRL7                 0x8007
#define L1F_CLDCTRL7_VDHLF_BIAS_TH_MASK     SHIFT9(0x7FU)
#define L1F_CLDCTRL7_VDHLF_BIAS_TH_SHIFT    9
#define L1F_CLDCTRL7_AFE_AZ_MASK            SHIFT4(0x1FU)
#define L1F_CLDCTRL7_AFE_AZ_SHIFT           4
#define L1F_CLDCTRL7_SIDE_PEAK_TH_MASK      SHIFT0(0xFU)
#define L1F_CLDCTRL7_SIDE_PEAK_TH_SHIFT     0
#define L1F_CLDCTRL7_DEF                    0x6BF6 /* ???? */

#define L1F_MIIEXT_AZCTRL                   0x8008
#define L1F_AZCTRL_SHORT_TH_MASK            SHIFT8(0xFFU)
#define L1F_AZCTRL_SHORT_TH_SHIFT           8
#define L1F_AZCTRL_LONG_TH_MASK             SHIFT0(0xFFU)
#define L1F_AZCTRL_LONG_TH_SHIFT            0
#define L1F_AZCTRL_DEF                      0x1629

#define L1F_MIIEXT_AZCTRL2                  0x8009
#define L1F_AZCTRL2_WAKETRNING_MASK         SHIFT8(0xFFU)
#define L1F_AZCTRL2_WAKETRNING_SHIFT        8
#define L1F_AZCTRL2_QUIET_TIMER_MASH        SHIFT6(3U)
#define L1F_AZCTRL2_QUIET_TIMER_SHIFT       6
#define L1F_AZCTRL2_PHAS_JMP2               BIT_4S
#define L1F_AZCTRL2_CLKTRCV_125MD16         BIT_3S
#define L1F_AZCTRL2_GATE1000_EN             BIT_2S
#define L1F_AZCTRL2_AVRG_FREQ               BIT_1S
#define L1F_AZCTRL2_PHAS_JMP4               BIT_0S
#define L1F_AZCTRL2_DEF                     0x32C0

#define L1F_MIIEXT_AZCTRL6                  0x800D

#define L1F_MIIEXT_VDRVBIAS                 0x8062
#define L1F_VDRVBIAS_SEL_MASK               SHIFT0(0x3U)
#define L1F_VDRVBIAS_SEL_SHIFT              0
#define L1F_VDRVBIAS_DEF                    0x3

/********* dev 7 **********/
#define L1F_MIIEXT_ANEG                     7

#define L1F_MIIEXT_LOCAL_EEEADV             0x3C
#define L1F_LOCAL_EEEADV_1000BT             BIT_2S
#define L1F_LOCAL_EEEADV_100BT              BIT_1S

#define L1F_MIIEXT_REMOTE_EEEADV            0x3D
#define L1F_REMOTE_EEEADV_1000BT            BIT_2S
#define L1F_REMOTE_EEEADV_100BT             BIT_1S

#define L1F_MIIEXT_EEE_ANEG                 0x8000
#define L1F_EEE_ANEG_1000M                  BIT_2S
#define L1F_EEE_ANEG_100M                   BIT_1S

#define L1F_MIIEXT_AFE                      0x801A
#define L1F_AFE_10BT_100M_TH                BIT_6S


#define L1F_MIIEXT_NLP34                    0x8025
#define L1F_MIIEXT_NLP34_DEF                0x1010  /* for 160m */

#define L1F_MIIEXT_NLP56                    0x8026
#define L1F_MIIEXT_NLP56_DEF                0x1010  /* for 160m */

#define L1F_MIIEXT_NLP78                    0x8027
#define L1F_MIIEXT_NLP78_160M_DEF           0x8D05  /* for 160m */
#define L1F_MIIEXT_NLP78_120M_DEF           0x8A05  /* for 120m */



/******************************************************************************/

/* functions */

#if 0
/* check if the mac address is valid */
bool macaddr_valid(u8 *addr);
#endif

/* get permanent mac address from
 * return
 *    0: success
 *    non-0:fail
 */
u16 l1f_get_perm_macaddr(PETHCONTEXT ctx, u8 *addr);


/* reset mac & dma
 * return
 *     0: success
 *     non-0:fail
 */
u16 l1f_reset_mac(PETHCONTEXT ctx);

/* reset phy
 * return
 *    0: success
 *    non-0:fail
 */
u16 l1f_reset_phy(PETHCONTEXT ctx, bool pws_en, bool az_en, bool ptp_en);


/* reset pcie
 * just reset pcie relative registers (pci command, clk, aspm...)
 * return
 *    0:success
 *    non-0:fail
 */
u16 l1f_reset_pcie(PETHCONTEXT ctx, bool l0s_en, bool l1_en);


/* disable/enable MAC/RXQ/TXQ
 * en
 *    true:enable
 *    false:disable
 * return
 *    0:success
 *    non-0-fail
 */
u16 l1f_enable_mac(PETHCONTEXT ctx, bool en, u16 en_ctrl);


/* enable/disable aspm support
 * that will change settings for phy/mac/pcie
 */
u16 l1f_enable_aspm(PETHCONTEXT ctx, bool l0s_en, bool l1_en, u8 lnk_stat);


/* initialize phy for speed / flow control
 * lnk_cap
 *    if autoNeg, is link capability to tell the peer
 *    if force mode, is forced speed/duplex
 */
u16 l1f_init_phy_spdfc(PETHCONTEXT ctx, bool auto_neg,
		       u8 lnk_cap, bool fc_en);

/* do post setting on phy if link up/down event occur
 */
u16 l1f_post_phy_link(PETHCONTEXT ctx, bool linkon, u8 wire_spd);


/* do power saving setting befor enter suspend mode
 * NOTE:
 *    1. phy link must be established before calling this function
 *    2. wol option (pattern,magic,link,etc.) is configed before call it.
 */
u16 l1f_powersaving(PETHCONTEXT ctx, u8 wire_spd, bool wol_en,
		    bool mactx_en, bool macrx_en, bool pws_en);

/* read phy register */
u16 l1f_read_phy(PETHCONTEXT ctx, bool ext, u8 dev, bool fast, u16 reg,
		 u16 *data);

/* write phy register */
u16 l1f_write_phy(PETHCONTEXT ctx, bool ext, u8 dev,  bool fast, u16 reg,
		  u16 data);

/* phy debug port */
u16 l1f_read_phydbg(PETHCONTEXT ctx, bool fast, u16 reg, u16 *data);
u16 l1f_write_phydbg(PETHCONTEXT ctx, bool fast, u16 reg, u16 data);


/* check the configuration of the PHY */
u16 l1f_get_phy_config(PETHCONTEXT ctx);

/*
 * initialize mac basically
 *  most of hi-feature no init
 *      MAC/PHY should be reset before call this function
 */
u16 l1f_init_mac(PETHCONTEXT ctx, u8 *addr, u32 txmem_hi,
		 u32 *tx_mem_lo, u8 tx_qnum, u16 txring_sz,
		 u32 rxmem_hi, u32 rfdmem_lo, u32 rrdmem_lo,
		 u16 rxring_sz, u16 rxbuf_sz, u16 smb_timer,
		 u16 mtu, u16 int_mod, bool hash_legacy);




#ifdef __cplusplus
}
#endif/*__cplusplus*/

#endif/*L1F_HW_H_*/

