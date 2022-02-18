#!/bin/bash

# Disable IP forwarding (both IPv4 and IPv6)
sysctl -w net.ipv4.ip_forward=0
sysctl -w net.ipv6.conf.all.forwarding=0

# Assume that our outbound (to the Internet) interface
# is named eth0
OUTBOUND_IFACE=eth0
iptables -t nat -D POSTROUTING -o ${OUTBOUND_IFACE} -j MASQUERADE
ip6tables -t nat -D POSTROUTING -o ${OUTBOUND_IFACE} -j MASQUERADE
