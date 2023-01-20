#!/usr/bin/env python3
# coding: utf-8

import sys
from socket import inet_ntop, AF_INET, AF_INET6
from bcc import BPF, DEBUG_PREPROCESSOR
import ctypes as ct
from struct import pack

# Keep in sync with change_interp_evt in connect.bcc
class ChangeInterpStruct(ct.Structure):
    _fields_ = [ ("pid", ct.c_int), ("filename", ct.c_char * 81) ]

def load_elf_binary_kfunc_printer(cpu, data, size):
    """
    This function is called every time that there is a call
    to load_elf_binary.

    pid: PPID of the process which (indirectly) invoked the function.
    filename: a NULL-terminated string naming the ELF file to be loaded.
    """
    event = ct.cast(data, ct.POINTER(ChangeInterpStruct)).contents
    filename = event.filename.decode("utf-8")
    print(f"PID {event.pid} loaded an ELF binary named {filename}.")

if __name__ == "__main__":
    b = BPF(src_file="exec.bcc")
    b["load_elf_binary"].open_perf_buffer(load_elf_binary_kfunc_printer)

    print(f"Waiting for the operating system to load an elf binary...")

    # Now, let's roll.
    while True:
        b.perf_buffer_poll(1)
