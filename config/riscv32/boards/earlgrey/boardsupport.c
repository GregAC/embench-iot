/* Copyright (C) 2017 Embecosm Limited and University of Bristol

   Contributor Graham Markall <graham.markall@embecosm.com>

   This file is part of Embench and was formerly part of the Bristol/Embecosm
   Embedded Benchmark Suite.

   SPDX-License-Identifier: GPL-3.0-or-later */

#include <support.h>
#include "sw/device/lib/oled_driver.h"
#include "sw/device/lib/uart.h"
#include "sw/device/lib/common.h"

void pcount_reset() {
  asm volatile(
      "csrw minstret,       x0\n"
      "csrw mcycle,         x0\n"
      "csrw mhpmcounter3,   x0\n"
      "csrw mhpmcounter4,   x0\n"
      "csrw mhpmcounter5,   x0\n"
      "csrw mhpmcounter6,   x0\n"
      "csrw mhpmcounter7,   x0\n"
      "csrw mhpmcounter8,   x0\n"
      "csrw mhpmcounter9,   x0\n"
      "csrw mhpmcounter10,  x0\n"
      "csrw mhpmcounter11,  x0\n"
      "csrw mhpmcounter12,  x0\n"
      "csrw mhpmcounter13,  x0\n"
      "csrw mhpmcounter14,  x0\n"
      "csrw mhpmcounter15,  x0\n"
      "csrw mhpmcounter16,  x0\n"
      "csrw mhpmcounter17,  x0\n"
      "csrw mhpmcounter18,  x0\n"
      "csrw mhpmcounter19,  x0\n"
      "csrw mhpmcounter20,  x0\n"
      "csrw mhpmcounter21,  x0\n"
      "csrw mhpmcounter22,  x0\n"
      "csrw mhpmcounter23,  x0\n"
      "csrw mhpmcounter24,  x0\n"
      "csrw mhpmcounter25,  x0\n"
      "csrw mhpmcounter26,  x0\n"
      "csrw mhpmcounter27,  x0\n"
      "csrw mhpmcounter28,  x0\n"
      "csrw mhpmcounter29,  x0\n"
      "csrw mhpmcounter30,  x0\n"
      "csrw mhpmcounter31,  x0\n"
      "csrw minstreth,      x0\n"
      "csrw mcycleh,        x0\n"
      "csrw mhpmcounter3h,  x0\n"
      "csrw mhpmcounter4h,  x0\n"
      "csrw mhpmcounter5h,  x0\n"
      "csrw mhpmcounter6h,  x0\n"
      "csrw mhpmcounter7h,  x0\n"
      "csrw mhpmcounter8h,  x0\n"
      "csrw mhpmcounter9h,  x0\n"
      "csrw mhpmcounter10h, x0\n"
      "csrw mhpmcounter11h, x0\n"
      "csrw mhpmcounter12h, x0\n"
      "csrw mhpmcounter13h, x0\n"
      "csrw mhpmcounter14h, x0\n"
      "csrw mhpmcounter15h, x0\n"
      "csrw mhpmcounter16h, x0\n"
      "csrw mhpmcounter17h, x0\n"
      "csrw mhpmcounter18h, x0\n"
      "csrw mhpmcounter19h, x0\n"
      "csrw mhpmcounter20h, x0\n"
      "csrw mhpmcounter21h, x0\n"
      "csrw mhpmcounter22h, x0\n"
      "csrw mhpmcounter23h, x0\n"
      "csrw mhpmcounter24h, x0\n"
      "csrw mhpmcounter25h, x0\n"
      "csrw mhpmcounter26h, x0\n"
      "csrw mhpmcounter27h, x0\n"
      "csrw mhpmcounter28h, x0\n"
      "csrw mhpmcounter29h, x0\n"
      "csrw mhpmcounter30h, x0\n"
      "csrw mhpmcounter31h, x0\n");
}

void pcount_enable(int enable) {
  // Note cycle is disabled with everything else
  unsigned int inhibit_val = enable ? 0x0 : 0xFFFFFFFF;
  // mucounteren == mcountinhibit but binutils doesn't seem to known the
  // mcountinhibit name
  asm volatile("csrw  mucounteren, %0\n" : : "r"(inhibit_val));
}

void pcount_read(uint32_t pcount_out[]) {
  asm volatile(
      "csrr %0, minstret\n"
      : "=r"(pcount_out[0])
  );

  asm volatile(
      "csrr %0, mcycle\n"
      : "=r"(pcount_out[1])
  );

  asm volatile(
      "csrr %0, mhpmcounter3\n"
      : "=r"(pcount_out[2])
  );

  asm volatile(
      "csrr %0, mhpmcounter4\n"
      : "=r"(pcount_out[3])
  );

  asm volatile(
      "csrr %0, mhpmcounter5\n"
      : "=r"(pcount_out[4])
  );

  asm volatile(
      "csrr %0, mhpmcounter6\n"
      : "=r"(pcount_out[5])
  );

  asm volatile(
      "csrr %0, mhpmcounter7\n"
      : "=r"(pcount_out[6])
  );

  asm volatile(
      "csrr %0, mhpmcounter8\n"
      : "=r"(pcount_out[7])
  );

  asm volatile(
      "csrr %0, mhpmcounter9\n"
      : "=r"(pcount_out[8])
  );

  asm volatile(
      "csrr %0, mhpmcounter10\n"
      : "=r"(pcount_out[9])
  );
}

const char* pcount_names[] = {
  "Instructions Retired",
  "Cycles",
  "LSU Busy",
  "IFetch wait",
  "Loads",
  "Stores",
  "Jumps",
  "Branches",
  "Taken Branches",
  "Compressed Instructions"
};

const uint32_t pcount_num = 10;

void dump_pcounts() {
  uint32_t pcounts[pcount_num];

  pcount_read(pcounts);
  uart_send_str("Performance Counters\r\n"
                "--------------------\r\n");
  for (uint32_t i = 0;i  < pcount_num; ++i) {
    uart_send_str(pcount_names[i]);
    uart_send_str(": ");
    uart_send_uint(pcounts[i], 32);
    uart_send_str("\r\n");
  }
  uart_send_str("\r\n");
}

void
initialise_board ()
{
  uart_init(UART_BAUD_RATE);
  uart_send_str("Embench running\r\n");
  oled_clear(1);

  oled_write_str("Embench", 0, 0);
  oled_write_str(bench_name, 2, 0);

  oled_write_disp();
}

void __attribute__ ((noinline)) __attribute__ ((externally_visible))
start_trigger ()
{
  uart_send_str("Start bench\r\n");
  pcount_enable(0);
  pcount_reset();
  pcount_enable(1);
}

void __attribute__ ((noinline)) __attribute__ ((externally_visible))
stop_trigger ()
{
  pcount_enable(0);
  uart_send_str("Stop bench\r\n");
  dump_pcounts();
}


void __attribute__ ((noinline)) __attribute__ ((externally_visible))
board_bench_result (int res)
{
  if(res) {
    uart_send_str("PASS!\r\n");
  } else {
    uart_send_str("FAIL!\r\n");
  }
}
