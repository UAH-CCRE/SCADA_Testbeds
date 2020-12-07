# -*- coding: utf-8 -*-
"""
# ------------------------------------------------------------------------------
# Property of UAH (2020)
# This project features work licensed under the Creative Commons
# Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy
# of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/. You
# may also visit https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
# Testbed Data Logger
# Authors: Mohammad Einaam Alim, Jack Smalligan, Raphael Ferreira Barata de Oliveira,
#           Christopher Nguyen, Rishabh Das
# ------------------------------------------------------------------------------
"""
import binascii
import csv
import json
import logging
import math
import pickle
import socket
import sys
import threading
import time
import subprocess
import shlex
from datetime import datetime
from threading import Event, Thread
from time import perf_counter_ns

from pymodbus.client.sync import ModbusTcpClient
from scapy.all import ETH_P_ALL
from scapy.config import conf
from scapy.layers.inet import IP, TCP
from scapy.sendrecv import sniff

# import logging.handlers as Handlers


def Hentropy(xi):
    """
        This function finds the Shannon entropy of an argument list
    """
    prob = [float(xi.count(c))/len(xi) for c in dict.fromkeys(xi)]
    H = -sum([p*math.log(p, 2) for p in prob])
    return H


class meanflow:
    """
        Number of packets per channel
    """

    def __init__(self, client_IP, window):
        self.window_pac = []
        self.client_IP = client_IP
        self.window_time = window  # Time in seconds

    def check_flow(self):
        # Current time object
        currenttime = datetime.now()

        # appending the current time object to the window
        self.window_pac.append(currenttime)

        # DEBUG
        # print(currenttime.timestamp())
        # print(self.window_pac[0].timestamp())

        while len(self.window_pac) > 0:
            if currenttime.timestamp() - self.window_pac[0].timestamp() > self.window_time:
                self.window_pac.pop(0)
            else:
                break
        return [self.client_IP, len(self.window_pac)]


class Sniffer(Thread):
    """
        Custom Sniffer to be confined to its own thread
    """

    def __init__(self, interface):
        super().__init__()

        # Python program exits when only daemon threads are left
        self.daemon = True

        # global contents array, stores 100 rows before writing
        contents = []
        iteration = 0

        # Declare self properties
        self.socket = None
        self.interface = interface
        self.stop_sniffer = Event()

    def run(self):
        self.socket = conf.L2listen(
            type=ETH_P_ALL,
            iface=self.interface,
            filter="tcp"
        )
        sniff(
            opened_socket=self.socket,
            prn=self.print_packet,
            stop_filter=self.should_stop_sniffer
        )

    def join(self, timeout=None):
        self.stop_sniffer.set()
        super().join(timeout)

    def should_stop_sniffer(self, packet):
        return self.stop_sniffer.isSet()

    # Define pseudo lambda for sniffer class, print out relevant info to separate csv
    def print_packet(self, packet):
        # global variables available between instances of sniffed packet
        global startTimer
        global endTimer
        global contents
        global dstList
        global writeInterval
        global netByteRate
        global dportDict
        global sportDict
        global pairDict
        global writeCount  # number of times written
        global meanFlowList

        # Update count of packet entries
        writeCount += 1

        if(packet.haslayer(TCP) and packet.haslayer(IP)):
            # Process packet flags
            tcpFlagsChk = ['U', 'A', 'P', 'R', 'S', 'F']
            tcpFlagString = ''
            ipFlagString = ''
            if (packet[TCP].flags):
                tcpFlagString = [ch for ch in str(
                    packet[TCP].flags)]  # example: [P, A]

            tcpFlags = []
            for m in tcpFlagsChk:
                value = 0
                for n in tcpFlagString:
                    if (m == n):
                        value = 1
                        break
                tcpFlags.append(value)

            ipFlagsChk = ['DF', 'MF']

            if (packet[IP].flags):
                ipFlagString = [ch for ch in str(
                    packet[IP].flags)]  # example: [P, A]

            ipFlags = []
            for m in ipFlagsChk:
                value = 0
                for n in ipFlagString:
                    if (m == n):
                        value = 1
                        break
                ipFlags.append(value)

            # TODO: Process packet payload
            packetPayload = binascii.hexlify(bytes(packet[TCP].payload))
            packetPayloadsList.append(packetPayload)
            # Modbus Application Protocol (MBAP) Header
            #   MBAP consists of 7 Bytes
            #  1 B = 2 hex, e.g. 0xFF
            transactionID = packetPayload[0:4]  # 2 bytes
            protocolID = packetPayload[4:8]  # 2 bytes
            # 2 bytes, describes len of unitID,funcCode,data
            lengthField = packetPayload[8:12]
            unitID = packetPayload[12:14]  # 1 byte

            # Protocol Data Unit (PDU)
            #  PDU consists of Function Code [1 Byte] and Data [x]
            #  Modbus TCP embeds a standard Modbus data frame into the TCP frame
            functionCode = packetPayload[14:16]  # 1 byte
            data = packetPayload[16:]  # remaining variable # bytes

            # Activities to monitor -- Raw, Retrieved, Recorded
            csvPacket["MAC Destination"] = packet.dst
            csvPacket["MAC Source"] = packet.src
            csvPacket["Version"] = packet[IP].version
            csvPacket["IHL"] = packet[IP].ihl
            csvPacket["Type of Service"] = packet[IP].tos
            csvPacket["Total Length"] = packet[IP].len
            csvPacket["Identification"] = packet[IP].id
            csvPacket["IP Flags [DF]"] = ipFlags[0]
            csvPacket["IP Flags [MF]"] = ipFlags[1]
            csvPacket["Fragment Offset"] = packet[IP].frag
            csvPacket["Time to Live"] = packet[IP].ttl
            csvPacket["Protocol"] = packet[IP].proto
            csvPacket["Header Checksum"] = packet[IP].chksum
            csvPacket["Source Address"] = packet[IP].src
            csvPacket["Destination Address"] = packet[IP].dst

            csvPacket["Source Port"] = packet[TCP].sport
            csvPacket["Destination Port"] = packet[TCP].dport
            csvPacket["Payload [P]"] = packetPayload
            csvPacket["[P] Transaction ID"] = transactionID
            csvPacket["[P] Protocol ID"] = protocolID
            csvPacket["[P] Length Field"] = lengthField
            csvPacket["[P] Unit ID"] = unitID
            csvPacket["[P] Function Code"] = functionCode
            csvPacket["[P] Data"] = data
            csvPacket["Sequence Number"] = packet[TCP].seq
            csvPacket["Acknowledgement Number"] = packet[TCP].ack
            csvPacket["Data Offset"] = packet[TCP].dataofs
            csvPacket["Reserved"] = packet[TCP].reserved
            csvPacket["TCP Flags [URG]"] = tcpFlags[0]
            csvPacket["TCP Flags [ACK]"] = tcpFlags[1]
            csvPacket["TCP Flags [PSH]"] = tcpFlags[2]
            csvPacket["TCP Flags [RST]"] = tcpFlags[3]
            csvPacket["TCP Flags [SYN]"] = tcpFlags[4]
            csvPacket["TCP Flags [FIN]"] = tcpFlags[5]
            csvPacket["Window Size"] = packet[TCP].window
            csvPacket["Checksum"] = packet[TCP].chksum
            csvPacket["Urgent Pointer"] = packet[TCP].urgptr

            csvPacket["Packet Size [B]"] = len(packet)

            # Append to hash maps
            dportDict[str(packet[TCP].dport)] = None
            sportDict[str(packet[TCP].sport)] = None

            # If we've never seen this pair before, add it
            if (pairDict.get('MAC: ' + str(csvPacket["MAC Source"]) + '   IP: ' + str(packet[IP].src)) == None):
                pairDict['MAC: ' + str(csvPacket["MAC Source"]) + '   IP: ' + str(packet[IP].src)] = meanflow(
                    client_IP=packet[IP].src, window=1)
                print("Found a new pair!")

            # Record timestamp
            timeStamp = datetime.now()
            csvPacket["Timestamp"] = timeStamp.strftime("%Y-%m-%d %H:%M:%S.%f")

            # TODO: Process Inter-Packet Metrics -- Calculated, Obtained, Derived
            #   Inter-Packet Delay Metric,
            #   Packet Processing Time in PLC,
            #   Packet Rates,
            #   Shannon Entropy,
            IPAT = 0  # Inter-packet arrival time -
            #   Time of packet arrival
            #   Time between packets arriving at same destination
            PPT = 0  # Packet process time -
            #   Time PLC takes to process; i.e.
            #   Time between receiving and transmitting a packet on PLC

            # Measure in nanosecond resolution
            timeStamp = time.time()

            # Determine IPD
            if (packet.dst in dstList):  # src -> dst logged before
                # Retrieve last instance of dst when it received something
                index = len(dstList) - 1 - dstList[::-1].index(packet.dst)
                IPAT = timeStamp - dstList[index + 1]

            mf = meanflow(client_IP=packet.src, window=1)
            # When dst IP matches the last src IP,
            if (packet.dst in srcList):
                # Retrieve last instance of dst when it sent something
                index = len(srcList) - 1 - srcList[::-1].index(packet.dst)
                endTimer = perf_counter_ns()
                PPT = (endTimer - srcList[index + 1]) / (10 ** 9)

            trueMF = pairDict['MAC: ' + str(csvPacket["MAC Source"]) +
                              '   IP: ' + str(packet[IP].src)].check_flow()

            # Append (dst,time) to dstList
            dstList.append(packet.dst)
            dstList.append(timeStamp)

            # Start perf timer for the packet (ends when PLC responds)
            startTimer = perf_counter_ns()

            # Append (dst,start_time) to srcList
            srcList.append(packet.src)
            srcList.append(startTimer)

            # Calculate protocol overhead
            protocolOverhead = float(
                len(packet) - len(packetPayload)) / len(packet)
            protocolEff = float(len(packetPayload)) / len(packet)
            if (IPAT == 0):
                netByteRate = 0
            else:
                netByteRate = float(csvPacket["Packet Size [B]"]) / IPAT
            throughput = protocolEff * (netByteRate * 8)

            # Extend row by metrics
            csvPacket["Inter-Packet Delay (s)"] = IPAT
            csvPacket["Packet Process Time (s)"] = PPT
            csvPacket["Protocol Overhead"] = protocolOverhead
            csvPacket["Protocol Efficiency"] = protocolEff
            csvPacket["Throughput"] = throughput
            # csvPacket["IP Check Flow Val"] = ipcf
            csvPacket["Client IP and Mean Flow"] = trueMF

            # Contents specific to the row
            contentsRow = list(csvPacket.values())

            # Add the row to the global record of contents
            contents.extend([contentsRow])

        # For every set interval, write
        if (len(contents) % writeInterval == 0):
            txsum = 0
            for csvLine in contents:
                with open('output_Network_data.csv', 'a', newline='') as file_packet:
                    writer_packets = csv.writer(file_packet)
                    writer_packets.writerow(csvLine)
                # Add up bytes transmitted and then find byte rate to use
                txsum += csvLine[37]
            # netByteRate = float(txsum/len(contents)) / writeCount
            # Reset
            contents = []


def label_monitor():
    """
        This function creates a server which receives the value of the class label
    """
   # global IPAddress
    print("Starting Label monitor!")
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind(('127.0.0.1', 4321))
    sock.listen(1)
    while True:
        connection, client_address = sock.accept()

        # Receive data and send it to routine handler
        data = pickle.loads(connection.recv(1024))
        if data.split("|")[0] != "Stop":
            handle_routines(data)
        else:
            # Kills the server
            break


def handle_routines(data):
    """
        Helps to change the class label dynamically
    """
    # The Messages processed will have the following format
    # Type|Value
    # Type - Can be either "Stop" or Change
    # Change will have a value of the new class label
    if data.split("|")[0] == "Change":
        newlabel = str(data.split("|")[1])
        print("Class label changed to "+newlabel)
    else:
        print("Cannot interpret message!")


def handle_commandline():
    """
        This function handles the commandline arguments
    """
    # print("python filename.py -IP [IPaddress for sniffing] -P [Port] -C [Class label]")
    if len(sys.argv) == 9:
        print("Sniffing IP:", sys.argv[2])
        print("Sniffing port", sys.argv[4])
        print("Labelling all data as:", sys.argv[6])
        print("Using interface: ", sys.argv[8])

    else:
        print("Please check commandline!")
        print(
            "python filename.py -IP [IPaddress for sniffing] -P [Port] -C [Class label] -I [Interface]")
        sys.exit(2) #invalid cmd line args



# ======= MAIN ========================================
print("==== Begin Script ====")
handle_commandline()

# Logging stuff
logging.basicConfig()
log = logging.getLogger()
log.setLevel(logging.ERROR)

# Suppress Scapy IPv6 warning
logging.getLogger("scapy.runtime").setLevel(logging.ERROR)

# First row of sniffer csv that holds all packet metrics
csvPacket = dict.fromkeys([  # IP
    "MAC Destination", "MAC Source",
    "Version", "IHL", "Type of Service", "Total Length",
    "Identification",
    # Lists of flags in IP
    "IP Flags [DF]", "IP Flags [MF]",
    "Fragment Offset",
    "Time to Live", "Protocol", "Header Checksum",
    "Source Address", "Destination Address",
    # TCP
    "Source Port", "Destination Port",
                   # Payload Headers
                   "Payload [P]",
                   "[P] Transaction ID", "[P] Protocol ID", "[P] Length Field", "[P] Unit ID",
                   "[P] Function Code", "[P] Data",
                   # Remaining Fields
                   "Sequence Number", "Acknowledgement Number",
                   "Data Offset", "Reserved",
    # Lists of flags in TCP
                   "TCP Flags [URG]", "TCP Flags [ACK]", "TCP Flags [PSH]",
                   "TCP Flags [RST]", "TCP Flags [SYN]", "TCP Flags [FIN]",
                   "Window Size", "Checksum", "Urgent Pointer",
                   # Metrics
                   "Packet Size [B]", "Timestamp",
                   "Inter-Packet Delay (s)",
                   "Packet Process Time (s)",
    "Protocol Overhead", "Protocol Efficiency", "Throughput", "Channel Utilization",
    "Client IP and Mean Flow"
])
csvPacketHeader = csvPacket.keys()

with open('output_Network_data.csv', 'w', newline='') as file_packet:
    writer_packets = csv.writer(file_packet)
    writer_packets.writerow(csvPacketHeader)

# Interface for TCP connection
#   Windows machine uses names; Linux uses enp0s3, enp0s8, eth0,fglobsl etc.
# interfaceName = "VMware Network Adapter VMnet1"

# Declare global variables to be read from packet handling
# List of lists, holds each row to write to file and resets every writeInterval
contents = []
dstList = []                    # List of dst IPs and time values to access
srcList = []                    # List of src IPs and time values to access
# List of ALL packet payloads used in calculating Shannon entropy
packetPayloadsList = []
writeInterval = 100             # Every <interval> packets, write to file
startTimer = 0                  # Starting Timer between packets
endTimer = 0                    # Ending Timer between packets
netByteRate = 1                 # Default metric
writeCount = 0                  # Number of times written
dportDict = {}                  # Dictionary holds unique destination IPs
sportDict = {}                  # Dictionary holds unique source IPs
pairDict = {}                   # Dictionary holds unique (MAC, IP) pairs
# list of mean flow objects for each instance of a client IP
meanFlowList = []
global y

# Initialize sniffer to sniff network for traffic (reading from machine host to system)
with open('Config.json') as jsonFile:
    y = json.load(jsonFile)
interfaceName = sys.argv[8] #y["Network_Interface"]
sniffer = Sniffer(interface=interfaceName)
print("[*] Start sniffing...")
sniffer.start()

# thread1 = threading.Thread(target=test)
thread1 = threading.Thread(target=label_monitor, daemon=True)
thread1.start()

wiresharkProcess = None

try:
    print("Starting wireshark in the background...")
    wiresharkProcess = subprocess.Popen(shlex.split("dumpcap -i %s -w network_traffic.pcap" % interfaceName), stdout=subprocess.DEVNULL, stderr=subprocess.STDOUT)

    print("Reading MODBUS values!")
    # Open client connection
    IPAddress = sys.argv[2]
    client = ModbusTcpClient(IPAddress, timeout=5)

    # Open CONFIG to pull headers and lists from
    with open('Config.json') as jsonFile:
        y = json.load(jsonFile)

    # Coil Registers and their Headers & Offsets
    coilsHeader = []
    coilList = []
    for i in y["coils"]:
        coilsHeader.append(i)
        coilList.append(y["coils"][i])

    # Discrete Input Registers and their Headers & Offsets
    discreteInputHeader = []
    discreteInputsList = []
    for i in y["discreteInputs"]:
        coilsHeader.append(i)
        coilList.append(y["discreteInputs"][i])

    # Holding Registers and their Headers & Offsets
    holdingRegistersHeader = []
    holdingRegisterList = []
    for i in y["holdingRegisters"]:
        holdingRegistersHeader.append(i)
        holdingRegisterList.append(y["holdingRegisters"][i])

    # Input Registers and their Headers & Offsets
    inputRegistersHeader = []
    inputRegisterList = []
    for i in y["inputRegisters"]:
        inputRegistersHeader.append(i)
        inputRegisterList.append(y["inputRegisters"][i])

    # Interval to write PLC values to file
    #  i.e. How many samples should we gather before writing?
    setInterval = y["set_interval_period"]

    # Put header together
    csvRowHeader = coilsHeader
    csvRowHeader.extend(discreteInputHeader)
    csvRowHeader.extend(holdingRegistersHeader)
    csvRowHeader.extend(inputRegistersHeader)

    csvRowHeader.extend(["Timestamp"])

    # Initialize empty general context list
    context = []

    # First open and write header to file
    with open('output_MODBUS_data.csv', 'w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(csvRowHeader)

    # Set period to # seconds between calls
    period = 0.4

    # DEBUG: Set number of iterations for a timer implementation
    s = 0
    iterTemp = 10
    loopIterations = iterTemp / period

    # Lock time loop to system clock
    startingTime = time.time()

    # DEBUG: replace with timer or True
    # while (1):
    while True:
        try:
            contextVals = []
            for i in coilList:
                # if (client.read_coils(i, 1).bits[0]):
                if (client.read_coils(i, 1).bits[0]):
                    x = 1
                else:
                    x = 0
                contextVals.append(x)
            for i in discreteInputsList:
                if (client.read_discrete_inputs(i, 1).bits[0]):
                    x = 1
                else:
                    x = 0
                contextVals.append(x)

            for j in holdingRegisterList:
                contextVals.extend(client.read_holding_registers(j, 1).registers)

            for c in inputRegisterList:
                contextVals.extend(client.read_input_registers(c, 1).registers)

            # Record timestamp
            timeStamp = [datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")]
            contextVals.extend(timeStamp)
            context.extend([contextVals])
            s += 1

            # Write to file every set interval
            if(s % setInterval == 0):
                for vals in context:
                    with open('output_MODBUS_data.csv', 'a', newline='') as file_append:
                        writer = csv.writer(file_append)
                        writer.writerow(vals)
                # Reset
                context = []

            # Runs every x time instead of delaying by x time between calls
            # NOTE: +-1ms precision
            time.sleep(period - ((time.time() - startingTime) % period))
        except AttributeError: #occurs if the response handle is a modbus exception
            pass #just don't write anything this iteration, wait for connection to recover
    # Close client connection
    client.close()
except KeyboardInterrupt:
    print("[*] Stop sniffing")
    sniffer.join(2.0)

    # If sniffer is still up, close it entirely
    if sniffer.is_alive():
        sniffer.socket.close()
finally:
    wiresharkProcess.kill()
    print("Wireshark stopped")

print("==== Finished General Testing Portion ====")
# Close client connection
client.close()
sniffer.join(2.0)
if sniffer.is_alive():
    sniffer.socket.close()
print("[*] Stopped sniffing")
print("========= Metrics =========")
print("Packet Entropy [Specific_Instance/Overall] = ",
      Hentropy(packetPayloadsList))
print("Number of Source Ports = ", len(sportDict.keys()))
print("Number of Destination Ports = ", len(dportDict.keys()))
print("Number of Peers Tracked by (MAC, IP) Pair = ", len(pairDict))
print("===========================")
print("===== Finished Script =====")
