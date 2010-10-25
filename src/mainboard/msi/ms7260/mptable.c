/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2007 AMD
 * Written by Yinghai Lu <yinghailu@amd.com> for AMD.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#include <console/console.h>
#include <arch/smp/mpspec.h>
#include <device/pci.h>
#include <string.h>
#include <stdint.h>
#include <cpu/amd/amdk8_sysconf.h>

extern unsigned char bus_isa;
extern unsigned char bus_mcp55[8];	// 1
extern unsigned apicid_mcp55;
extern unsigned bus_type[256];

static void *smp_write_config_table(void *v)
{
	struct mp_config_table *mc;
	unsigned int sbdn;
	int i, j;

	mc = (void *)(((char *)v) + SMP_FLOATING_TABLE_LEN);

	mptable_init(mc, "MS-7260     ", LAPIC_ADDR);

	smp_write_processors(mc);

	get_bus_conf();
	sbdn = sysconf.sbdn;

	/* Bus:	Bus ID	Type */
	/* Define bus and ISA numbers. */
	for (j = 0; j < 256; j++) {
		if (bus_type[j])
			smp_write_bus(mc, j, "PCI   ");
	}
	smp_write_bus(mc, bus_isa, "ISA   ");

	/* I/O APICs: APIC ID	Version	State		Address */
	{
		device_t dev;
		struct resource *res;
		uint32_t dword;

		dev = dev_find_slot(bus_mcp55[0], PCI_DEVFN(sbdn + 0x1, 0));
		if (dev) {
			res = find_resource(dev, PCI_BASE_ADDRESS_1);
			if (res)
				smp_write_ioapic(mc, apicid_mcp55, 0x11, res->base);

			dword = 0x43c6c643;
			pci_write_config32(dev, 0x7c, dword);

			dword = 0x81001a00;
			pci_write_config32(dev, 0x80, dword);

			dword = 0xd0001202;
			pci_write_config32(dev, 0x84, dword);
		}
	}

	mptable_add_isa_interrupts(mc, bus_isa, apicid_mcp55, 0);

	/* I/O Ints:         Type       Trigger                Polarity              Bus ID        IRQ                    APIC ID       PIN# */
	smp_write_intsrc(mc, mp_INT,    MP_IRQ_TRIGGER_LEVEL | MP_IRQ_POLARITY_LOW,  bus_mcp55[0], ((sbdn + 1) << 2) | 1, apicid_mcp55, 0xa);
	smp_write_intsrc(mc, mp_INT,    MP_IRQ_TRIGGER_LEVEL | MP_IRQ_POLARITY_LOW,  bus_mcp55[0], ((sbdn + 2) << 2) | 0, apicid_mcp55, 0x16);	// 22
	smp_write_intsrc(mc, mp_INT,    MP_IRQ_TRIGGER_LEVEL | MP_IRQ_POLARITY_LOW,  bus_mcp55[0], ((sbdn + 2) << 2) | 1, apicid_mcp55, 0x17);	// 23
	smp_write_intsrc(mc, mp_INT,    MP_IRQ_TRIGGER_LEVEL | MP_IRQ_POLARITY_LOW,  bus_mcp55[0], ((sbdn + 6) << 2) | 1, apicid_mcp55, 0x17);	// 23
	smp_write_intsrc(mc, mp_INT,    MP_IRQ_TRIGGER_LEVEL | MP_IRQ_POLARITY_LOW,  bus_mcp55[0], ((sbdn + 5) << 2) | 0, apicid_mcp55, 0x14);	// 20
	smp_write_intsrc(mc, mp_INT,    MP_IRQ_TRIGGER_LEVEL | MP_IRQ_POLARITY_LOW,  bus_mcp55[0], ((sbdn + 5) << 2) | 1, apicid_mcp55, 0x17);	// 23
	smp_write_intsrc(mc, mp_INT,    MP_IRQ_TRIGGER_LEVEL | MP_IRQ_POLARITY_LOW,  bus_mcp55[0], ((sbdn + 5) << 2) | 2, apicid_mcp55, 0x15);	// 21
	smp_write_intsrc(mc, mp_INT,    MP_IRQ_TRIGGER_LEVEL | MP_IRQ_POLARITY_LOW,  bus_mcp55[0], ((sbdn + 8) << 2) | 0, apicid_mcp55, 0x16);	// 22

	for (j = 7; j >= 2; j--) {
		if (!bus_mcp55[j])
			continue;
		for (i = 0; i < 4; i++)
			smp_write_intsrc(mc, mp_INT, MP_IRQ_TRIGGER_LEVEL | MP_IRQ_POLARITY_LOW, bus_mcp55[j], (0x00 << 2) | i, apicid_mcp55, 0x10 + (2 + j + i + 4 - sbdn % 4) % 4);
	}

	for (j = 0; j < 2; j++) {
		for (i = 0; i < 4; i++)
			smp_write_intsrc(mc, mp_INT, MP_IRQ_TRIGGER_LEVEL | MP_IRQ_POLARITY_LOW, bus_mcp55[1], ((0x06 + j) << 2) | i, apicid_mcp55, 0x10 + (2 + i + j) % 4);
	}

	/* Local Ints:       Type       Trigger               Polarity              Bus ID   IRQ  APIC ID      PIN# */
	smp_write_intsrc(mc, mp_ExtINT, MP_IRQ_TRIGGER_EDGE | MP_IRQ_POLARITY_HIGH, bus_isa, 0x0, MP_APIC_ALL, 0x0);
	smp_write_intsrc(mc, mp_NMI,    MP_IRQ_TRIGGER_EDGE | MP_IRQ_POLARITY_HIGH, bus_isa, 0x0, MP_APIC_ALL, 0x1);

	/* There is no extension information... */

	/* Compute the checksums. */
	mc->mpe_checksum =
	    smp_compute_checksum(smp_next_mpc_entry(mc), mc->mpe_length);
	mc->mpc_checksum = smp_compute_checksum(mc, mc->mpc_length);
	printk(BIOS_DEBUG, "Wrote the mp table end at: %p - %p\n",
		     mc, smp_next_mpe_entry(mc));
	return smp_next_mpe_entry(mc);
}

unsigned long write_smp_table(unsigned long addr)
{
	void *v;
	v = smp_write_floating_table(addr);
	return (unsigned long)smp_write_config_table(v);
}
