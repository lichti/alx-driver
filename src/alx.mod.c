#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xc60edb3e, "module_layout" },
	{ 0x5a34a45c, "__kmalloc" },
	{ 0x7ee91c1d, "_spin_trylock" },
	{ 0xf9a482f9, "msleep" },
	{ 0x6980fe91, "param_get_int" },
	{ 0xeb548f00, "qdisc_reset" },
	{ 0xcd800551, "dev_set_drvdata" },
	{ 0x950ffff2, "cpu_online_mask" },
	{ 0x670b33a9, "dma_set_mask" },
	{ 0xba1b52e5, "malloc_sizes" },
	{ 0x2293ff56, "pci_disable_device" },
	{ 0x3110d859, "pci_disable_msix" },
	{ 0x46495b8a, "netif_carrier_on" },
	{ 0x973873ab, "_spin_lock" },
	{ 0x58ac86f9, "ethtool_op_get_sg" },
	{ 0xa28e76e6, "schedule_work" },
	{ 0x43ab66c3, "param_array_get" },
	{ 0x7462069d, "netif_carrier_off" },
	{ 0x8d8708f, "cancel_work_sync" },
	{ 0x5f248409, "x86_dma_fallback_dev" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0x6a9f26c9, "init_timer_key" },
	{ 0x8e7285b5, "pci_enable_wake" },
	{ 0xff964b25, "param_set_int" },
	{ 0x712aa29b, "_spin_lock_irqsave" },
	{ 0x3c2c5af5, "sprintf" },
	{ 0x45947727, "param_array_set" },
	{ 0x7d11c268, "jiffies" },
	{ 0x27c33efe, "csum_ipv6_magic" },
	{ 0xeefa1ac, "netif_rx" },
	{ 0x9629486a, "per_cpu__cpu_number" },
	{ 0xfe7c4287, "nr_cpu_ids" },
	{ 0xc0b0b5d5, "pci_set_master" },
	{ 0xe83fea1, "del_timer_sync" },
	{ 0xde0bdcff, "memset" },
	{ 0xcbc91802, "alloc_etherdev_mq" },
	{ 0x1a7431fc, "pci_enable_pcie_error_reporting" },
	{ 0x9096aa2f, "dev_alloc_skb" },
	{ 0x35774ddd, "pci_enable_msix" },
	{ 0xa2940602, "pci_restore_state" },
	{ 0xea147363, "printk" },
	{ 0x178abc7e, "ethtool_op_get_link" },
	{ 0x2fa5a500, "memcmp" },
	{ 0xbc169eaa, "free_netdev" },
	{ 0x7ec9bfbc, "strncpy" },
	{ 0x18377a53, "register_netdev" },
	{ 0xb4390f9a, "mcount" },
	{ 0x16305289, "warn_slowpath_null" },
	{ 0x15436973, "pci_bus_write_config_dword" },
	{ 0x6dcaeb88, "per_cpu__kernel_stack" },
	{ 0x92ea4ae4, "crc32_le" },
	{ 0x4b07e779, "_spin_unlock_irqrestore" },
	{ 0x45450063, "mod_timer" },
	{ 0x1902adf, "netpoll_trap" },
	{ 0x859c6dc7, "request_threaded_irq" },
	{ 0xe1d80f76, "dev_kfree_skb_any" },
	{ 0xe523ad75, "synchronize_irq" },
	{ 0x5524bfa6, "dev_kfree_skb_irq" },
	{ 0x1f6a4802, "pci_select_bars" },
	{ 0x7dceceac, "capable" },
	{ 0x3ff62317, "local_bh_disable" },
	{ 0x7c74af10, "netif_device_attach" },
	{ 0x78764f4e, "pv_irq_ops" },
	{ 0xc1afab3d, "netif_device_detach" },
	{ 0x42c8de35, "ioremap_nocache" },
	{ 0x8d5f4cec, "ethtool_op_set_sg" },
	{ 0x5285d8bf, "pci_bus_read_config_dword" },
	{ 0x799aca4, "local_bh_enable" },
	{ 0x2a2db5e5, "eth_type_trans" },
	{ 0x8ead20b4, "dev_driver_string" },
	{ 0x93c27fbd, "pskb_expand_head" },
	{ 0x7ca6c43a, "pci_unregister_driver" },
	{ 0x343eb9ee, "kmem_cache_alloc_trace" },
	{ 0xfaf98462, "bitrev32" },
	{ 0xe52947e7, "__phys_addr" },
	{ 0xaca166f4, "pci_set_power_state" },
	{ 0x5da82d78, "eth_validate_addr" },
	{ 0xe016611, "pci_disable_pcie_error_reporting" },
	{ 0x3aa1dbcf, "_spin_unlock_bh" },
	{ 0x37a0cba, "kfree" },
	{ 0x236c8c64, "memcpy" },
	{ 0xf8bbcfe0, "___pskb_trim" },
	{ 0xf42b8636, "pci_disable_msi" },
	{ 0xedc03953, "iounmap" },
	{ 0x6dac8a6e, "__pci_register_driver" },
	{ 0x4cbbd171, "__bitmap_weight" },
	{ 0xe130d83c, "unregister_netdev" },
	{ 0xbf058923, "ethtool_op_get_tso" },
	{ 0x1c85b536, "pci_enable_msi_block" },
	{ 0x910cecdd, "pci_choose_state" },
	{ 0x7a2dc7ec, "__netif_schedule" },
	{ 0x48a7089b, "consume_skb" },
	{ 0xb0413b82, "pci_enable_device_mem" },
	{ 0x93cbd1ec, "_spin_lock_bh" },
	{ 0xedd8a48, "skb_put" },
	{ 0x67b5f53b, "pci_set_consistent_dma_mask" },
	{ 0x9f7eb031, "pci_release_selected_regions" },
	{ 0xbca29332, "pci_request_selected_regions" },
	{ 0xd5f1439c, "dev_get_drvdata" },
	{ 0x17e81c74, "dma_ops" },
	{ 0xf20dabd8, "free_irq" },
	{ 0x63d8c00f, "pci_save_state" },
	{ 0xce9e9b7d, "__vlan_hwaccel_rx" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("pci:v00001969d00001063sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001969d00001062sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001969d00001073sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001969d00001083sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001969d00002060sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001969d00002062sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001969d00001091sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001969d00001090sv*sd*bc*sc*i*");

MODULE_INFO(srcversion, "4656D3E31911D483960A3EF");

static const struct rheldata _rheldata __used
__attribute__((section(".rheldata"))) = {
	.rhel_major = 6,
	.rhel_minor = 4,
};
