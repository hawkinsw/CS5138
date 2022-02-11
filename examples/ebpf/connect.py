#!/usr/bin/env python3
# coding: utf-8

import sys
from socket import inet_ntop, AF_INET, AF_INET6
from bcc import BPF, DEBUG_PREPROCESSOR
import ctypes as ct
import subprocess
from struct import pack

IFNAMSIZ = 16  # uapi/linux/if.h

ICMP_EVT = 1


class TcpEvt(ct.Structure):
    _fields_ = [
        ("pid", ct.c_int),
        ("ip_version", ct.c_ulonglong),
        ("saddr", ct.c_ulonglong * 2),
    ]


class IcmpEvt(ct.Structure):
    _fields_ = [
        # Routing information
        ("ifname", ct.c_char * IFNAMSIZ),
        ("netns", ct.c_ulonglong),
        # Packet type (IPv4 or IPv6) and address
        ("ip_version", ct.c_ulonglong),
        ("icmptype", ct.c_ulonglong),
        ("icmpid", ct.c_ulonglong),
        ("icmpseq", ct.c_ulonglong),
        ("saddr", ct.c_ulonglong * 2),
        ("daddr", ct.c_ulonglong * 2),
    ]


def _get(l, index, default):
    """
    Get element at index in l or return the default
    """
    if index < len(l):
        return l[index]
    return default


def tcp_connect_event_printer(cpu, data, size):
    event = ct.cast(data, ct.POINTER(TcpEvt)).contents
    # Decode address
    if event.ip_version == 4:
        saddr = inet_ntop(AF_INET, pack("=I", event.saddr[0]))
    elif event.ip_version == 6:
        saddr = inet_ntop(AF_INET6, event.saddr)
    else:
        print("Could not decode the address!")
        return
    print(f"{event.pid}: {saddr}")


if __name__ == "__main__":
    # Build probe and open event buffer
    b = BPF(src_file="icmp.bcc")
    b["tcp_connect_event"].open_perf_buffer(tcp_connect_event_printer)

    # Print a header.
    print(f"PID:Address")
    # Listen for event until the ping process has exited
    while True:
        b.perf_buffer_poll(1)
