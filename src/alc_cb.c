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

#include "alc_hw.h"


/* NIC */
int alc_identify_nic(struct alx_hw *hw)
{
	return 0;
}

/* PHY */
int alc_read_phy_reg(struct alx_hw *hw, u32 device_type,
		     u16 reg_addr, u16 *phy_data)
{
	bool fast = false;
	bool ext = false;
	u16 error;
	int retval = 0;

	ALX_MDIO_LOCK(&hw->mdio_lock);

	if (device_type != ALX_MDIO_NORM_DEV)
		ext = true;

	error = l1c_read_phy(hw, ext, device_type, fast,
			     reg_addr, phy_data);
	if (error) {
		alx_hw_err(hw, "Error when reading phy reg (%d).", error);
		retval = ALX_ERR_PHY_READ_REG;
	}

	ALX_MDIO_UNLOCK(&hw->mdio_lock);

	return retval;
}

int alc_write_phy_reg(struct alx_hw *hw, u32 device_type,
		      u16 reg_addr, u16 phy_data)
{
	bool fast = false;
	bool ext = false;
	u16 error;
	int retval = 0;

	ALX_MDIO_LOCK(&hw->mdio_lock);

	if (device_type != ALX_MDIO_NORM_DEV)
		ext = true;

	error = l1c_write_phy(hw, ext, device_type, fast, reg_addr, phy_data);
	if (error) {
		alx_hw_err(hw, "Error when writting phy reg (%d).", error);
		retval = ALX_ERR_PHY_WRITE_REG;
	}

	ALX_MDIO_UNLOCK(&hw->mdio_lock);

	return retval;
}


int alc_init_phy(struct alx_hw *hw)
{
	u16 phy_id[2];
	int retval;

	/* 1. init mdio spin lock */
	ALX_MDIO_LOCK_INIT(&hw->mdio_lock);

	/* 2. read phy id */
	retval = alc_read_phy_reg(hw, ALX_MDIO_NORM_DEV,
				  L1C_MII_PHYSID1, &phy_id[0]);
	if (retval)
		return retval;
	retval = alc_read_phy_reg(hw, ALX_MDIO_NORM_DEV,
				  L1C_MII_PHYSID1, &phy_id[1]);
	if (retval)
		return retval;

	memcpy(&hw->phy_id, phy_id, sizeof(hw->phy_id));

	hw->autoneg_advertised = ALX_LINK_SPEED_1GB_FULL |
				 ALX_LINK_SPEED_10_HALF  |
				 ALX_LINK_SPEED_10_FULL  |
				 ALX_LINK_SPEED_100_HALF |
				 ALX_LINK_SPEED_100_FULL;
	return retval;
}


int alc_reset_phy(struct alx_hw *hw)
{
	int retval = 0;
	bool pws_en, az_en, ptp_en;

	pws_en = az_en = ptp_en = false;
	CLI_HW_FLAG(PWSAVE_EN);
	CLI_HW_FLAG(AZ_EN);
	CLI_HW_FLAG(PTP_EN);

	if (CHK_HW_FLAG(PWSAVE_CAP)) {
		pws_en = true;
		SET_HW_FLAG(PWSAVE_EN);
	}

	if (CHK_HW_FLAG(AZ_CAP)) {
		az_en = true;
		SET_HW_FLAG(AZ_EN);
	}

	if (CHK_HW_FLAG(PTP_CAP)) {
		ptp_en = true;
		SET_HW_FLAG(PTP_EN);
	}

	alx_hw_info(hw, "reset PHY, pws = %d, az = %d, ptp = %d\n",
		    pws_en, az_en, ptp_en);

	if (l1c_reset_phy(hw, pws_en, az_en, ptp_en))
		retval = ALX_ERR_PHY_RESET;

	return retval;
}

/* LINK */
int alc_setup_phy_link(struct alx_hw *hw, u32 speed, bool autoneg, bool fc)
{
	u8 link_cap = 0;
	int retval = 0;

	alx_hw_info(hw, "speed = 0x%x, autoneg = %d\n", speed, autoneg);
	if (speed & ALX_LINK_SPEED_1GB_FULL)
		link_cap |= LX_LC_1000F;

	if (speed & ALX_LINK_SPEED_100_FULL)
		link_cap |= LX_LC_100F;

	if (speed & ALX_LINK_SPEED_100_HALF)
		link_cap |= LX_LC_100H;

	if (speed & ALX_LINK_SPEED_10_FULL)
		link_cap |= LX_LC_10F;

	if (speed & ALX_LINK_SPEED_10_HALF)
		link_cap |= LX_LC_10H;

	if (l1c_init_phy_spdfc(hw, autoneg, link_cap, fc))
		retval = ALX_ERR_PHY_SETUP_LNK;

	return retval;
}



int alc_setup_phy_link_speed(struct alx_hw *hw, u32 speed,
			     bool autoneg, bool fc)
{
	int retval = 0;

	/*
	 * Clear autoneg_advertised and set new values based on input link
	 * speed.
	 */
	hw->autoneg_advertised = 0;

	if (speed & ALX_LINK_SPEED_1GB_FULL)
		hw->autoneg_advertised |= ALX_LINK_SPEED_1GB_FULL;

	if (speed & ALX_LINK_SPEED_100_FULL)
		hw->autoneg_advertised |= ALX_LINK_SPEED_100_FULL;

	if (speed & ALX_LINK_SPEED_100_HALF)
		hw->autoneg_advertised |= ALX_LINK_SPEED_100_HALF;

	if (speed & ALX_LINK_SPEED_10_FULL)
		hw->autoneg_advertised |= ALX_LINK_SPEED_10_FULL;

	if (speed & ALX_LINK_SPEED_10_HALF)
		hw->autoneg_advertised |= ALX_LINK_SPEED_10_HALF;

	retval = alc_setup_phy_link(hw, hw->autoneg_advertised,
				    autoneg, fc);
	return retval;


}



int alc_check_phy_link(struct alx_hw *hw, u32 *speed, bool *link_up)
{
	u16 bmsr, giga;
	int retval;

	alc_read_phy_reg(hw, ALX_MDIO_NORM_DEV, L1C_MII_BMSR, &bmsr);
	retval = alc_read_phy_reg(hw, ALX_MDIO_NORM_DEV,
				  L1C_MII_BMSR, &bmsr);
	if (retval)
		return retval;


	*link_up = true;
	if (!(bmsr & L1C_BMSR_LINK_STATUS)) {
		*link_up = false;
		*speed = ALX_LINK_SPEED_UNKNOWN;
		return retval;
	}


	/* Read PHY Specific Status Register (17) */
	retval = alc_read_phy_reg(hw, ALX_MDIO_NORM_DEV,
				  L1C_MII_GIGA_PSSR, &giga);
	if (retval)
		return retval;


	if (!(giga & L1C_GIGA_PSSR_SPD_DPLX_RESOLVED))
		return ALX_ERR_PHY_RESOLVED;

	switch (giga & L1C_GIGA_PSSR_SPEED) {
	case L1C_GIGA_PSSR_1000MBS:
		if (giga & L1C_GIGA_PSSR_DPLX)
			*speed = ALX_LINK_SPEED_1GB_FULL;
		else
			alx_hw_err(hw, "1000M half is invalid");
		break;
	case L1C_GIGA_PSSR_100MBS:
		if (giga & L1C_GIGA_PSSR_DPLX)
			*speed = ALX_LINK_SPEED_100_FULL;
		else
			*speed = ALX_LINK_SPEED_100_HALF;
		break;
	case L1C_GIGA_PSSR_10MBS:
		if (giga & L1C_GIGA_PSSR_DPLX)
			*speed = ALX_LINK_SPEED_10_FULL;
		else
			*speed = ALX_LINK_SPEED_10_HALF;
		break;
	default:
		*speed = ALX_LINK_SPEED_UNKNOWN;
		retval = ALX_ERR_PHY_CHECK_LNK;
		break;
	}

	return retval;
}

/* INTR */
int alc_ack_phy_intr(struct alx_hw *hw)
{
	u16 isr;
	return alc_read_phy_reg(hw, ALX_MDIO_NORM_DEV, L1C_MII_ISR, &isr);
}


/*
 * 1. stop_mac
 * 2. reset mac & dma by reg1400(MASTER)
 * 3. control speed/duplex, hash-alg
 * 4. clock switch setting
 */
int alc_reset_mac(struct alx_hw *hw)
{
	int retval = 0;

	if (l1c_reset_mac(hw))
		retval = ALX_ERR_MAC_RESET;

	return retval;
}


int alc_start_mac(struct alx_hw *hw)
{
	u16 en_ctrl = 0;
	int retval = 0;

	/* set link speed param */
	switch (hw->link_speed) {
	case ALX_LINK_SPEED_1GB_FULL:
		en_ctrl |= LX_MACSPEED_1000;
		/* fall through */
	case ALX_LINK_SPEED_100_FULL:
	case ALX_LINK_SPEED_10_FULL:
		en_ctrl |= LX_MACDUPLEX_FULL;
		break;
	}

	/* set fc param*/
	switch (hw->cur_fc_mode) {
	case alx_fc_full:
		en_ctrl |= LX_FC_RXEN; /* Flow Control RX Enable */
		en_ctrl |= LX_FC_TXEN; /* Flow Control TX Enable */
		break;
	case alx_fc_rx_pause:
		en_ctrl |= LX_FC_RXEN; /* Flow Control RX Enable */
		break;
	case alx_fc_tx_pause:
		en_ctrl |= LX_FC_TXEN; /* Flow Control TX Enable */
		break;
	default:
		break;
	}

	if (hw->fc_single_pause)
		en_ctrl |= LX_SINGLE_PAUSE;


	en_ctrl |= LX_FLT_DIRECT; /* RX Enable; and TX Always Enable */
	en_ctrl |= LX_FLT_BROADCAST; /* RX Broadcast Enable */
	en_ctrl |= LX_ADD_FCS;

	if (CHK_HW_FLAG(VLANSTRIP_EN))
		en_ctrl |= LX_VLAN_STRIP;

	if (CHK_HW_FLAG(PROMISC_EN))
		en_ctrl |=  LX_FLT_PROMISC;

	if (CHK_HW_FLAG(MULTIALL_EN))
		en_ctrl |= LX_FLT_MULTI_ALL;

	if (CHK_HW_FLAG(LOOPBACK_EN))
		en_ctrl |= LX_LOOPBACK;

	if (l1c_enable_mac(hw, true, en_ctrl))
		retval = ALX_ERR_MAC_START;
	return retval;
}


/*
 * 1. stop RXQ (reg15A0) and TXQ (reg1590)
 * 2. stop MAC (reg1480)
 */
int alc_stop_mac(struct alx_hw *hw)
{
	int retval = 0;

	if (l1c_enable_mac(hw, false, 0))
		retval = ALX_ERR_MAC_STOP;
	return retval;
}


int alc_config_mac(struct alx_hw *hw, u16 rxbuf_sz, u16 rx_qnum,
		   u16 rxring_sz, u16 tx_qnum,  u16 txring_sz)
{
	u8 *addr;

	u32 txmem_hi, txmem_lo[4];

	u32 rxmem_hi, rfdmem_lo, rrdmem_lo;

	u16 smb_timer, mtu_with_eth, int_mod;
	bool hash_legacy;

	int i;
	int retval = 0;
#if MAC_TYPE_FPGA == MAC_TYPE
	u32 phy;
#endif

	addr = hw->mac_addr;

	txmem_hi = ALX_DMA_ADDR_HI(hw->tpdma[0]);
	for (i = 0; i < tx_qnum; i++)
		txmem_lo[i] = ALX_DMA_ADDR_LO(hw->tpdma[i]);


	rxmem_hi = ALX_DMA_ADDR_HI(hw->rfdma[0]);
	rfdmem_lo = ALX_DMA_ADDR_LO(hw->rfdma[0]);
	rrdmem_lo = ALX_DMA_ADDR_LO(hw->rrdma[0]);


	smb_timer = (u16)hw->smb_timer;
	mtu_with_eth = hw->mtu + ALX_ETH_LENGTH_OF_HEADER;
	int_mod = hw->imt;

	hash_legacy = true;

	if (l1c_init_mac(hw, addr, txmem_hi, txmem_lo, tx_qnum, txring_sz,
			 rxmem_hi, rfdmem_lo, rrdmem_lo, rxring_sz, rxbuf_sz,
			 smb_timer, mtu_with_eth, int_mod, hash_legacy)) {
		retval = ALX_ERR_MAC_CONFIGURE;
	}

#if MAC_TYPE_FPGA == MAC_TYPE
	MEM_R32(hw, L1C_MDIO, &phy);
	phy |= 0x10000000;
	MEM_W32(hw, L1C_MDIO, phy);
#endif
	return retval;
}



/**
 *  alc_get_mac_addr
 *  @hw: pointer to hardware structure
 **/
int alc_get_mac_addr(struct alx_hw *hw, u8 *addr)
{
	int retval = 0;

	if (l1c_get_perm_macaddr(hw, addr))
		retval = ALX_ERR_MAC_ADDR;

	return retval;
}


int alc_reset_pcie(struct alx_hw *hw, bool l0s_en, bool l1_en)
{
	int retval = 0;

	if (!CHK_HW_FLAG(L0S_CAP))
		l0s_en = false;

	if (l0s_en)
		SET_HW_FLAG(L0S_EN);
	else
		CLI_HW_FLAG(L0S_EN);


	if (!CHK_HW_FLAG(L1_CAP))
		l1_en = false;

	if (l1_en)
		SET_HW_FLAG(L1_EN);
	else
		CLI_HW_FLAG(L1_EN);

	if (l1c_reset_pcie(hw, l0s_en, l1_en))
		retval = ALX_ERR_PCIE_RESET;

	return retval;
}



int alc_config_aspm(struct alx_hw *hw, bool l0s_en, bool l1_en)
{
	int retval = 0;

	if (!CHK_HW_FLAG(L0S_CAP))
		l0s_en = false;

	if (l0s_en)
		SET_HW_FLAG(L0S_EN);
	else
		CLI_HW_FLAG(L0S_EN);


	if (!CHK_HW_FLAG(L1_CAP))
		l1_en = false;

	if (l1_en)
		SET_HW_FLAG(L1_EN);
	else
		CLI_HW_FLAG(L1_EN);


	if (l1c_enable_aspm(hw, l0s_en, l1_en, 0))
		retval = ALX_ERR_ASPM;

	return retval;
}



/* RAR, Multicast, VLAN */
int alc_set_mac_addr(struct alx_hw *hw, u8 *addr)
{
	u32 sta;
	int retval = 0;

	/*
	 * for example: 00-0B-6A-F6-00-DC
	 * 0<-->6AF600DC, 1<-->000B.
	 */

	 /* low dword */
	sta = (((u32)addr[2]) << 24) | (((u32)addr[3]) << 16) |
	      (((u32)addr[4]) << 8)  | (((u32)addr[5])) ;
	MEM_W32(hw, L1C_STAD0, sta);
	/* hight dword */
	sta = (((u32)addr[0]) << 8) | (((u32)addr[1])) ;
	MEM_W32(hw, L1C_STAD1, sta);

	return retval;
}


int alc_set_mc_addr(struct alx_hw *hw, u8 *addr)
{
	u32 crc32;
	u32 bit, reg;
	u32 mta;

	/*
	* set hash value for a multicast address hash calcu processing.
	*   1. calcu 32bit CRC for multicast address
	*   2. reverse crc with MSB to LSB
	*/
	crc32 = ALX_ETH_CRC(addr, ALX_ETH_LENGTH_OF_ADDRESS);

	/*
	 * The HASH Table  is a register array of 2 32-bit registers.
	 * It is treated like an array of 64 bits.  We want to set
	 * bit BitArray[hash_value]. So we figure out what register
	 * the bit is in, read it, OR in the new bit, then write
	 * back the new value.  The register is determined by the
	 * upper 7 bits of the hash value and the bit within that
	 * register are determined by the lower 5 bits of the value.
	 */
	reg = (crc32 >> 31) & 0x1;
	bit = (crc32 >> 26) & 0x1F;

	MEM_R32(hw, L1C_HASH_TBL0 + (reg<<2), &mta);
	mta |= (0x1 << bit);
	MEM_W32(hw, L1C_HASH_TBL0 + (reg<<2), mta);

	return 0;
}

int alc_clear_mc_addr(struct alx_hw *hw)
{
	MEM_W32(hw, L1C_HASH_TBL0, 0);
	MEM_W32(hw, L1C_HASH_TBL1, 0);
	return 0;
}


/* RTX, IRQ */
int alc_config_tx(struct alx_hw *hw)
{
	return 0;
}


int alc_enable_legacy_intr(struct alx_hw *hw)
{
	MEM_W32(hw, L1C_ISR, ~L1C_ISR_DIS);
	MEM_W32(hw, L1C_IMR, hw->intr_mask);
	return 0;
}

int alc_disable_legacy_intr(struct alx_hw *hw)
{
	MEM_W32(hw, L1C_ISR, L1C_ISR_DIS);
	MEM_W32(hw, L1C_IMR, 0);
	MEM_FLUSH(hw);
	return 0;
}


int alc_config_wol(struct alx_hw *hw, u32 wufc)
{
	u32 wol;
	int retval = 0;

	wol = 0;
	/* turn on magic packet event */
	if (wufc & ALX_WOL_MAGIC) {
		wol |= L1C_WOL0_MAGIC_EN | L1C_WOL0_PME_MAGIC_EN;
		/* magic packet maybe Broadcast&multicast&Unicast frame
		 * move to l1c_powersaving
		 */
	}

	/* turn on link up event */
	if (wufc & ALX_WOL_PHY) {
		wol |=  L1C_WOL0_LINK_EN | L1C_WOL0_PME_LINK;
		/* only link up can wake up */
		retval = alc_write_phy_reg(hw, ALX_MDIO_NORM_DEV,
					   L1C_MII_IER, L1C_IER_LINK_UP);
	}

	MEM_W32(hw, L1C_WOL0, wol);

	return retval;
}


int alc_config_mac_ctrl(struct alx_hw *hw)
{
	u32 mac;

	MEM_R32(hw, L1C_MAC_CTRL, &mac);

	/* enable/disable VLAN tag insert,strip */
	if (CHK_HW_FLAG(VLANSTRIP_EN))
		mac |= L1C_MAC_CTRL_VLANSTRIP;
	else
		mac &= ~L1C_MAC_CTRL_VLANSTRIP;


	if (CHK_HW_FLAG(PROMISC_EN))
		mac |= L1C_MAC_CTRL_PROMISC_EN;
	else
		mac &= ~L1C_MAC_CTRL_PROMISC_EN;


	if (CHK_HW_FLAG(MULTIALL_EN))
		mac |= L1C_MAC_CTRL_MULTIALL_EN;
	else
		mac &= ~L1C_MAC_CTRL_MULTIALL_EN;

	if (CHK_HW_FLAG(LOOPBACK_EN))
		mac |= L1C_MAC_CTRL_LPBACK_EN;
	else
		mac &= ~L1C_MAC_CTRL_LPBACK_EN;


	MEM_W32(hw, L1C_MAC_CTRL, mac);
	return 0;
}

int alc_config_pow_save(struct alx_hw *hw, u32 speed, bool wol_en,
			bool tx_en, bool rx_en, bool pws_en)
{
	u8 wire_spd = LX_LC_10H;
	int retval = 0;

	switch (speed) {
	case ALX_LINK_SPEED_UNKNOWN:
	case ALX_LINK_SPEED_10_HALF:
		wire_spd = LX_LC_10H;
		break;
	case ALX_LINK_SPEED_10_FULL:
		wire_spd = LX_LC_10F;
		break;
	case ALX_LINK_SPEED_100_HALF:
		wire_spd = LX_LC_100H;
		break;
	case ALX_LINK_SPEED_100_FULL:
		wire_spd = LX_LC_100F;
		break;
	case ALX_LINK_SPEED_1GB_FULL:
		wire_spd = LX_LC_1000F;
		break;
	}

	if (l1c_powersaving(hw, wire_spd, wol_en, tx_en, rx_en, pws_en))
		retval = ALX_ERR_PWR_SAVING;
	return retval;
}

/*
 * NV Ram
 */
int alc_check_nvram(struct alx_hw *hw, bool *exist)
{
	*exist = false;
	return 0;
}

int alc_read_nvram(struct alx_hw *hw, u16 offset, u32 *data)
{
	int i;
	u32 ectrl1, ectrl2, edata;
	int retval = 0;

	if (offset & 0x3)
		return retval; /* address do not align */

	MEM_R32(hw, L1C_EFUSE_CTRL2, &ectrl2);
	if (!(ectrl2 & L1C_EFUSE_CTRL2_CLK_EN))
		MEM_W32(hw, L1C_EFUSE_CTRL2, ectrl2|L1C_EFUSE_CTRL2_CLK_EN);

	MEM_W32(hw, L1C_EFUSE_DATA, 0);
	ectrl1 = FIELDL(L1C_EFUSE_CTRL_ADDR, offset);
	MEM_W32(hw, L1C_EFUSE_CTRL, ectrl1);

	for (i = 0; i < 10; i++) {
		__US_DELAY(100);
		MEM_R32(hw, L1C_EFUSE_CTRL, &ectrl1);
		if (ectrl1 & L1C_EFUSE_CTRL_FLAG)
			break;
	}
	if (ectrl1 & L1C_EFUSE_CTRL_FLAG) {
		MEM_R32(hw, L1C_EFUSE_CTRL, &ectrl1);
		MEM_R32(hw, L1C_EFUSE_DATA, &edata);
		*data = LX_SWAP_DW((ectrl1 << 16) | (edata >> 16));
		return retval;
	}

	if (!(ectrl2 & L1C_EFUSE_CTRL2_CLK_EN))
		MEM_W32(hw, L1C_EFUSE_CTRL2, ectrl2);

	return retval;
}


int alc_write_nvram(struct alx_hw *hw, u16 offset, u32 data)
{
	return 0;
}


/* fc */
static int alc_get_fc_mode(struct alx_hw *hw, enum alx_fc_mode *mode)
{
	u16 bmsr, giga;
	int i;
	int retval = 0;

	for (i = 0; i < ALX_MAX_SETUP_LNK_CYCLE; i++) {
		__MS_DELAY(100);
		alc_read_phy_reg(hw, ALX_MDIO_NORM_DEV, L1C_MII_BMSR, &bmsr);
		alc_read_phy_reg(hw, ALX_MDIO_NORM_DEV, L1C_MII_BMSR, &bmsr);
		if (bmsr & L1C_BMSR_LINK_STATUS) {
			/* Read phy Specific Status Register (17) */
			retval = alc_read_phy_reg(hw, ALX_MDIO_NORM_DEV,
						  L1C_MII_GIGA_PSSR, &giga);
			if (retval)
				return retval;

			if (!(giga & L1C_GIGA_PSSR_SPD_DPLX_RESOLVED))
				return ALX_ERR_PHY_RESOLVED;

			if ((giga & L1C_GIGA_PSSR_FC_TXEN) &&
			    (giga & L1C_GIGA_PSSR_FC_RXEN)) {
				*mode = alx_fc_full;
			} else if (giga & L1C_GIGA_PSSR_FC_TXEN) {
				*mode = alx_fc_tx_pause;
			} else if (giga & L1C_GIGA_PSSR_FC_RXEN) {
				*mode = alx_fc_rx_pause;
			} else {
				*mode = alx_fc_none;
			}
			break;
		}
	}

	if (i == ALX_MAX_SETUP_LNK_CYCLE)
		retval = ALX_ERR_PHY_SETUP_LNK;
	return retval;
}


int alc_config_fc(struct alx_hw *hw)
{
	u32 mac;
	int retval = 0;

	if (hw->disable_fc_autoneg) {
		hw->fc_was_autonegged = false;
		hw->cur_fc_mode = hw->req_fc_mode;
	} else {
		hw->fc_was_autonegged = true;
		retval = alc_get_fc_mode(hw, &hw->cur_fc_mode);
		if (retval)
			return retval;
	}

	MEM_R32(hw, L1C_MAC_CTRL, &mac);

	switch (hw->cur_fc_mode) {
	case alx_fc_none: /* 0 */
		mac &= ~(L1C_MAC_CTRL_RXFC_EN | L1C_MAC_CTRL_TXFC_EN);
		break;
	case alx_fc_rx_pause: /* 1 */
		mac &= ~L1C_MAC_CTRL_TXFC_EN;
		mac |= L1C_MAC_CTRL_RXFC_EN;
		break;
	case alx_fc_tx_pause: /* 2 */
		mac |= L1C_MAC_CTRL_TXFC_EN;
		mac &= ~L1C_MAC_CTRL_RXFC_EN;
		break;
	case alx_fc_full: /* 3 */
	case alx_fc_default: /* 4 */
		mac |= (L1C_MAC_CTRL_TXFC_EN | L1C_MAC_CTRL_RXFC_EN);
		break;
	default:
		alx_hw_err(hw, "Flow control param set incorrectly\n");
		return -1;
	}

	MEM_W32(hw, L1C_MAC_CTRL, mac);

	return retval;
}


/* ethtool */
int alc_get_ethtool_regs(struct alx_hw *hw, void *buff)
{
	u32 *regs = buff;
	int retval = 0;

	MEM_R32(hw, L1C_LNK_CAP,        &regs[0]);
	MEM_R32(hw, L1C_PMCTRL,         &regs[1]);
	MEM_R32(hw, L1C_HALFD,          &regs[2]);
	MEM_R32(hw, L1C_SLD,            &regs[3]);
	MEM_R32(hw, L1C_MASTER,         &regs[4]);
	MEM_R32(hw, L1C_MANU_TIMER,     &regs[5]);
	MEM_R32(hw, L1C_IRQ_MODU_TIMER, &regs[6]);
	MEM_R32(hw, L1C_PHY_CTRL,       &regs[7]);
	MEM_R32(hw, L1C_LNK_CTRL,       &regs[8]);
	MEM_R32(hw, L1C_MAC_STS,        &regs[9]);

	MEM_R32(hw, L1C_MDIO,      &regs[10]);
	MEM_R32(hw, L1C_SERDES,    &regs[11]);
	MEM_R32(hw, L1C_MAC_CTRL,  &regs[12]);
	MEM_R32(hw, L1C_GAP,       &regs[13]);
	MEM_R32(hw, L1C_STAD0,     &regs[14]);
	MEM_R32(hw, L1C_STAD1,     &regs[15]);
	MEM_R32(hw, L1C_HASH_TBL0, &regs[16]);
	MEM_R32(hw, L1C_HASH_TBL1, &regs[17]);
	MEM_R32(hw, L1C_RXQ0,      &regs[18]);
	MEM_R32(hw, L1C_RXQ1,      &regs[19]);

	MEM_R32(hw, L1C_RXQ2, &regs[20]);
	MEM_R32(hw, L1C_RXQ3, &regs[21]);
	MEM_R32(hw, L1C_TXQ0, &regs[22]);
	MEM_R32(hw, L1C_TXQ1, &regs[23]);
	MEM_R32(hw, L1C_TXQ2, &regs[24]);
	MEM_R32(hw, L1C_MTU,  &regs[25]);
	MEM_R32(hw, L1C_WOL0, &regs[26]);
	MEM_R32(hw, L1C_WOL1, &regs[27]);
	MEM_R32(hw, L1C_WOL2, &regs[28]);
	return retval;
}


/******************************************************************************/

static int alc_get_hw_capabilities(struct alx_hw *hw)
{
	u32 link;

	MEM_R32(hw, L1C_LNK_CTRL, &link);
	if (link & L1C_LNK_CTRL_ASPM_ENL0S)
		SET_HW_FLAG(L0S_CAP);
	if (link & L1C_LNK_CTRL_ASPM_ENL1)
		SET_HW_FLAG(L1_CAP);

	if ((hw->mac_type == alx_mac_l1c) ||
	    (hw->mac_type == alx_mac_l1d_v1) ||
	    (hw->mac_type == alx_mac_l1d_v2))
		SET_HW_FLAG(GIGA_CAP);

	SET_HW_FLAG(PWSAVE_CAP);
	return 0;
}

/* alc_set_hw_info */
static int alc_set_hw_infos(struct alx_hw *hw)
{
	hw->rxstat_reg = 0x1700;
	hw->rxstat_sz  = 0x60;
	hw->txstat_reg = 0x1760;
	hw->txstat_sz  = 0x68;

	hw->rx_prod_reg[0] = L1C_RFD_PIDX;
	hw->rx_cons_reg[0] = L1C_RFD_CIDX;

	hw->tx_prod_reg[0] = L1C_TPD_PRI0_PIDX;
	hw->tx_cons_reg[0] = L1C_TPD_PRI0_CIDX;
	hw->tx_prod_reg[1] = L1C_TPD_PRI1_PIDX;
	hw->tx_cons_reg[1] = L1C_TPD_PRI1_CIDX;

	hw->hwreg_sz = 0x80;
	hw->eeprom_sz = 0;

	return 0;
}


/**
 *  alc_init_hw_callbacks - Inits func ptrs and MAC type
 *  @hw: pointer to hardware structure
 **/
int alc_init_hw_callbacks(struct alx_hw *hw)
{
	/* NIC */
	hw->cbs.identify_nic   = &alc_identify_nic;
	/* MAC*/
	hw->cbs.reset_mac      = &alc_reset_mac;
	hw->cbs.start_mac      = &alc_start_mac;
	hw->cbs.stop_mac       = &alc_stop_mac;
	hw->cbs.config_mac     = &alc_config_mac;
	hw->cbs.get_mac_addr   = &alc_get_mac_addr;
	hw->cbs.set_mac_addr   = &alc_set_mac_addr;
	hw->cbs.set_mc_addr    = &alc_set_mc_addr;
	hw->cbs.clear_mc_addr  = &alc_clear_mc_addr;

	/* PHY */
	hw->cbs.init_phy       = &alc_init_phy;
	hw->cbs.reset_phy      = &alc_reset_phy;
	hw->cbs.read_phy_reg   = &alc_read_phy_reg;
	hw->cbs.write_phy_reg  = &alc_write_phy_reg;
	hw->cbs.check_phy_link = &alc_check_phy_link;
	hw->cbs.setup_phy_link = &alc_setup_phy_link;
	hw->cbs.setup_phy_link_speed = &alc_setup_phy_link_speed;

	/* Interrupt */
	hw->cbs.ack_phy_intr	= &alc_ack_phy_intr;
	hw->cbs.enable_legacy_intr  = &alc_enable_legacy_intr;
	hw->cbs.disable_legacy_intr = &alc_disable_legacy_intr;

	/* Configure */
	hw->cbs.config_tx	= &alc_config_tx;
	hw->cbs.config_fc	= &alc_config_fc;
	hw->cbs.config_aspm	= &alc_config_aspm;
	hw->cbs.config_wol	= &alc_config_wol;
	hw->cbs.config_mac_ctrl	= &alc_config_mac_ctrl;
	hw->cbs.config_pow_save	= &alc_config_pow_save;
	hw->cbs.reset_pcie	= &alc_reset_pcie;

	/* NVRam */
	hw->cbs.check_nvram	= &alc_check_nvram;
	hw->cbs.read_nvram	= &alc_read_nvram;
	hw->cbs.write_nvram	= &alc_write_nvram;

	/* Others */
	hw->cbs.get_ethtool_regs = alc_get_ethtool_regs;

	/* get hw capabilitites to HW->flags */
	alc_get_hw_capabilities(hw);
	alc_set_hw_infos(hw);

	alx_hw_info(hw, "HW Flags = 0x%x\n", hw->flags);
	return 0;
}

