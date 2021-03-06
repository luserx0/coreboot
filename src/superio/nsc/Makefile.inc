##
## This file is part of the coreboot project.
##
## Copyright (C) 2009 Ronald G. Minnich
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; version 2 of the License.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##

## include generic nsc pre-ram stage driver
bootblock-$(CONFIG_SUPERIO_NSC_COMMON_PRE_RAM) += common/early_serial.c
romstage-$(CONFIG_SUPERIO_NSC_COMMON_PRE_RAM) += common/early_serial.c

subdirs-y += pc87309
subdirs-y += pc87360
subdirs-y += pc87366
subdirs-y += pc87382
subdirs-y += pc87384
subdirs-y += pc87392
subdirs-y += pc87417
subdirs-y += pc97317
