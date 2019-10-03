#!/bin/sh

stty -F $OT_FPGA_UART $OT_FPGA_UART_BAUD

OT_TOP=`realpath ../../../`

./benchmark_speed.py --target-module run_earlgrey_fpga \
  --ot_top $OT_TOP \
  --spiflash $OT_TOP/build-bin/sw/host/spiflash/spiflash \
  --fpga_uart $OT_FPGA_UART

