#!/bin/bash


USERNAME=`whoami`
echo "${USERNAME}"

if [ "${USERNAME}" != "root" ]; then
				echo "ERROR: You must run this script as root."
				exit 1
fi

# A script to configure mitmproxy to run in
# transparent mode. See
# https://docs.mitmproxy.org/stable/howto-transparent/

# Save the old version of send_redirects. We're
# about to overwrite it.
OLD_SEND_REDIRECTS=`sysctl -n net.ipv4.conf.all.send_redirects`
# The ``documentation" told me to do this.
sysctl -w net.ipv4.conf.all.send_redirects=0 2>&1 >/dev/null

# Log all secrets to this file so that we can decrypt
# the SSL traffic in Wireshark in real time (and even
# afterwards). See https://wiki.wireshark.org/TLS#using-the-pre-master-secret
# for how to configure Wireshark to take advantage of
# this configuration.
KEYFILE_FILE="/home/${SUDO_USER}/keyfile.txt"

echo "INFO: The SSL keyfile is located at ${KEYFILE_FILE}. Make a note."

# Use a regular expression to define which connections
# we do not want to proxy. By default, we will accept
# all connections.
IGNORE_REGEX="^$"

# Assume that our outbound (to the Internet) interface
# is named eth1
OUTBOUND_IFACE=eth1

# Use iptables/ip6tables to redirect packets for ports
# 80 and 443 to the mitmproxy.
iptables -t nat -A PREROUTING -i ${OUTBOUND_IFACE} -p tcp --dport 80 -j REDIRECT --to-port 8080
iptables -t nat -A PREROUTING -i ${OUTBOUND_IFACE} -p tcp --dport 443 -j REDIRECT --to-port 8080
ip6tables -t nat -A PREROUTING -i ${OUTBOUND_IFACE} -p tcp --dport 80 -j REDIRECT --to-port 8080
ip6tables -t nat -A PREROUTING -i ${OUTBOUND_IFACE} -p tcp --dport 443 -j REDIRECT --to-port 8080

# Now, launch it!
SSLKEYLOGFILE="${KEYFILE_FILE}" mitmproxy --mode transparent --verbose --set stream_large_bodies=3m --showhost --set block_global=false --ignore-hosts ${IGNORE_REGEX}

# Remove the iptables/ip6tables redirection rules -- just
# to be safe.
iptables -t nat -D PREROUTING -i ${OUTBOUND_IFACE} -p tcp --dport 80 -j REDIRECT --to-port 8080
iptables -t nat -D PREROUTING -i ${OUTBOUND_IFACE} -p tcp --dport 443 -j REDIRECT --to-port 8080
ip6tables -t nat -D PREROUTING -i ${OUTBOUND_IFACE} -p tcp --dport 80 -j REDIRECT --to-port 8080
ip6tables -t nat -D PREROUTING -i ${OUTBOUND_IFACE} -p tcp --dport 443 -j REDIRECT --to-port 8080

# Reset send_redirects
sysctl -w net.ipv4.conf.all.send_redirects=${OLD_SEND_REDIRECTS} 2>&1 >/dev/null
