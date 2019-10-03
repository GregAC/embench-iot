#!/bin/sh
set -x

/tools/riscv/bin/riscv32-unknown-elf-objdump -fhSD $1 > $1.dis
/tools/riscv/bin/riscv32-unknown-elf-objcopy -O binary $1 $1.bin
srec_cat $1.bin -binary -offset 0x0000 -byte-swap 4 -o $1.vmem -vmem

