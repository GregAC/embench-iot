__all__ = [
    'get_target_args',
    'build_benchmark_cmd',
    'decode_results',
]

import argparse
import csv
import os.path
import re

from embench_core import log

cycles_re = re.compile(r'Cycles\: ([\da-fA-F]*)')


def get_target_args(remnant):
    """Parse left over arguments"""
    parser = argparse.ArgumentParser(description='Get target specific args')

    parser.add_argument(
        '--ot_top',
        type=str,
        required=True,
        help='Path to the root of OT repository'
    )

    parser.add_argument(
        '--spiflash',
        type=str,
        required=True,
        help='Path to spiflash binary',
    )

    parser.add_argument(
        '--fpga_uart',
        type=str,
        required=True,
        help='Path to FPGA UART (/dev/ttyUSBnn)',
    )

    return parser.parse_args(remnant)


def build_benchmark_cmd(bench, args):
    """Construct the command to run the benchmark.  "args" is a
       namespace with target specific arguments"""
    cmd = [f'pytest',
            '-s',
            '-v',
           f'{args.ot_top}/test/systemtest/functional_fpga_test.py',
            '--fpga_uart',
           f'{args.fpga_uart}',
            '--spiflash',
           f'{args.spiflash}',
            '--test_bin',
           f'{bench}.bin',
            '--log',
           f'{bench}.uart.log']

    return cmd


def decode_results(stdout_str, stderr_str, bench, appdir):
    """Extract the results from the output string of the run. Return the
       elapsed time in milliseconds or zero if the run failed."""

    bench_out_filename = os.path.join(appdir, f'{bench}.uart.log')

    log.debug(f'Looking for {bench} results in {bench_out_filename}')

    try:
        with open(bench_out_filename) as bench_out_uart_log:
            for uart_row in bench_out_uart_log:
                cycles_match = cycles_re.search(uart_row)
                if(cycles_match):
                    cycle_count = int(cycles_match.group(1), 16)
                    return cycle_count / 25000.0
    except FileNotFoundError:
        log.warning(f'Could not find {bench_out_filename}')


    log.warning(f'Could not find cycle count in {bench_out_filename}')

    return 0.0
