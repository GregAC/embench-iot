// Generated register defines for oled_driver

// Copyright information found in source file:
// Copyright lowRISC contributors.

// Licensing information found in source file:
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#ifndef _OLED_DRIVER_REG_DEFS_
#define _OLED_DRIVER_REG_DEFS_

// OLED command register
#define OLED_DRIVER_CMD(id) (OLED_DRIVER##id##_BASE_ADDR + 0x0)
#define OLED_DRIVER_CMD_DISP_WRITE 0
#define OLED_DRIVER_CMD_DISP_ON 1
#define OLED_DRIVER_CMD_DISP_OFF 2

// OLED Status register
#define OLED_DRIVER_STATUS(id) (OLED_DRIVER##id##_BASE_ADDR + 0x4)
#define OLED_DRIVER_STATUS_DISP_READY 0
#define OLED_DRIVER_STATUS_ON_READY 1
#define OLED_DRIVER_STATUS_OFF_READY 2

// Memory area: Pixel buffer memory
#define OLED_DRIVER_PIX_BUF(id) (OLED_DRIVER##id##_BASE_ADDR + 0x800)
#define OLED_DRIVER_PIX_BUF_SIZE_WORDS 128
#define OLED_DRIVER_PIX_BUF_SIZE_BYTES 512
#endif  // _OLED_DRIVER_REG_DEFS_
// End generated register defines for oled_driver
