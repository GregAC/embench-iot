#!/bin/bash

pushd ../../../
ninja -C build-out/sw/fpga sw/device/lib/libmem_ot.a
ninja -C build-out/sw/fpga sw/device/lib/liboled_ot.a
ninja -C build-out/sw/fpga sw/device/lib/libuart_ot.a
ninja -C build-out/sw/fpga sw/device/lib/libirq_ot.a
cp build-out/sw/fpga/sw/device/lib/libmem_ot.a ./sw/vendor/embench-iot/config/riscv32/boards/earlgrey/
cp build-out/sw/fpga/sw/device/lib/liboled_ot.a ./sw/vendor/embench-iot/config/riscv32/boards/earlgrey/
cp build-out/sw/fpga/sw/device/lib/libuart_ot.a ./sw/vendor/embench-iot/config/riscv32/boards/earlgrey/
cp build-out/sw/fpga/sw/device/lib/libirq_ot.a ./sw/vendor/embench-iot/config/riscv32/boards/earlgrey/
cp sw/device/exts/common/_crt.c ./sw/vendor/embench-iot/config/riscv32/boards/earlgrey/
cp sw/device/exts/common/link.ld ./sw/vendor/embench-iot/config/riscv32/boards/earlgrey/
cp sw/device/lib/irq_vectors.S ./sw/vendor/embench-iot/config/riscv32/boards/earlgrey/
./util/regtool.py -D -o ./sw/vendor/embench-iot/config/riscv32/boards/earlgrey/uart_regs.h ./hw/ip/uart/data/uart.hjson
./util/regtool.py -D -o ./sw/vendor/embench-iot/config/riscv32/boards/earlgrey/oled_driver_regs.h ./hw/ip/oled_driver/data/oled_driver.hjson
popd

./build_all.py  --arch riscv32 --chip speed-test --board earlgrey --cc riscv32-unknown-elf-gcc --ld riscv32-unknown-elf-gcc --cpu-mhz 25 --verbose


