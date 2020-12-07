"""
    Script that can modify a binary packet to change its values before it is forwarded
    Program args:

    modify_packet.py [Packet File Name] [1st register to change] [mode] [replacement or modification] [... (continue for additional registers to change)]

    modes:
        r -> replace
        m -> modify (if it's a modification, the next argument is added to the current value)
        fr -> replace with a value in a file (in the file cases, the replacement or modification is the filename)
        fm -> modify with a value in a file
"""
from sys import argv
from os import system, remove
from time import time

packetFile = argv[1]
packetContents = None

with open(packetFile, 'rb') as f:
    packetContents = list(f.read())

t = str(time())[11:16]

OFFSET = 9 # where the base of the first register is in the payload of a modbus packet
REGISTER_SIZE = 2 # in bytes

def process_registers():
    # the loop goes through the passed arguments, and processes each register as required
    for arg_index in range(2, len(argv), 3):
        registerNumber = int(argv[arg_index])

        baseIndex = OFFSET + (registerNumber * REGISTER_SIZE)

        #check to avoid IndexError
        if baseIndex+REGISTER_SIZE-1 < len(packetContents):

            mode = argv[arg_index+1]
            adjustmentValue = argv[arg_index+2]
            requested = None
            currentValue = ""

            for i in range(REGISTER_SIZE):
                # the reason for the the [2:] string splicing is to remove the 0x from the hex output
                currentValue += hex(packetContents[baseIndex+i])[2:]

            # convert currentValue to int
            currentValue = int(currentValue, 16)

            if mode == "r": #replacement
                requested = int(adjustmentValue)

            elif mode == "m": #modification
                requested = currentValue+int(adjustmentValue)

            elif mode[0] == "f": #file
                fileContents = None

                with open(adjustmentValue, "r") as val:
                    fileContents = val.read()

                    if len(fileContents) > 0:
                        fileContents = int(fileContents)
                    else:
                        return None

                if mode[1] == "m": # modification
                    #if it is this mode, the file must contain a single int
                    requested = currentValue+fileContents
                elif mode[1] == "r": # replacement
                    #if it is this mode, the file must contain a single int, in the range [0, 65535]
                    requested = fileContents

            #make sure the new value can be written as a byte
            if requested > 2**16-1:
                requested = 2**16-1
            elif requested < 0:
                requested = 0

            #count from REG_SIZE-1 to 0
            for i in range(REGISTER_SIZE-1, -1, -1):
                # mask all but the last byte, and write to the appropriate byte 
                # in the packet
                packetContents[baseIndex+i] = requested & 255

                # shift out the last byte
                requested >>= 8

process_registers()
#the reason for adding the time indicator is to guarantee that 
#concurrently running filters don't result in an edit conflict, which results in many problems
with open(packetFile+t+".packet", "wb") as p:
    p.write(bytearray(packetContents))

system("/usr/bin/cat %s" % packetFile+t+".packet")
remove(packetFile+t+".packet")
remove(packetFile)