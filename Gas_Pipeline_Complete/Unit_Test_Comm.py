# -*- coding: utf-8 -*-
"""
Created on Tue Mar 10 15:43:48 2020

@authors: Rishabh Das, Mohammad Einaam Alim, Raphael Barata de Oliveira, Jack Smalligan, Christopher Nguyen

In addition to verifying that the system can operate normally, this script communicates with the data logger, 
letting it know that its operation is correct.

In order to test, run Datalogger.py before running this script.

"""
import socket
import threading
import pickle
import time
import random
from pymodbus.client.sync import ModbusTcpClient
from scapy.all import *
import subprocess
import binascii

from scapy.layers.inet import TCP,IP
from scapy.sendrecv import sniff

def display_dict(dict):
    for (key, values) in dict.items():
        print(key, " : ", values)

class operation:
    
    def __init__(self,IP,Port,Interface,HMI_IP):
        """
            The IP and Port of the computer being attacked.
            If we are attacking a PLC, the IP and Port of the PLC
            should be used while amking an object to this class
        """
        self.IP = IP
        self.Port = Port
        self.Interface = Interface
        self.HMI_IP = HMI_IP
	
    def change_data_label(self,label,IP,Port):
        """
            calling this function changes the data label of the datalogger
        """
        client_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        address = (IP,int(Port))
        client_sock.connect(address)
        dat = pickle.dumps("Change|"+str(label))
        client_sock.send(dat)
	
    def Normal_operation_1(self,label):
        """
            This operation will configure the Gas Pipe as follows:
            Mode: automatic valve_mode(holding register 3: 0 = manual, 1 = pump_mode, 2 = valve_mode)
            Min setpoint 20 (holding register 1, 0-100%)
            Max setpoint 30 (holding register 2, 0-100%)
            Valve = open (holding register 5, 0 = closed, 1 = open)
        """

        print("Performing Normal Operation " + label)
        client.write_register(1,3500,unit=1) #min setpoint 35
        client.write_register(2,4000,unit=1) #max setpoint 40
        client.write_register(3,2,unit=1)    #auto mode (Valve)
        time.sleep(15)

    def Normal_operation_2(self,label):
        """
            This operation will configure the Gas Pipe as follows:
            Mode: automatic pipe_mode(holding register 3: 0 = manual, 1 = pump_mode, 2 = valve_mode)
            Min setpoint 20 (holding register 1, 0-100%)
            Max setpoint 30 (holding register 2, 0-100%)
            Valve = open (holding register 5, 0 = closed, 1 = open)
        """

        print("Performing Normal Operation " + label)
        client.write_register(1,2000,unit=1) #min setpoint 35
        client.write_register(2,3000,unit=1) #max setpoint 40
        client.write_register(3,1,unit=1)    #auto mode (Pump)
        time.sleep(15) 	
		
#-------------------------------------------------------------------------------------------
#           MAIN Call

# Get the list of interfaces
interfaceCodes = {}
interfaceList = get_if_list()
for i in range(0,len(interfaceList)):
    interfaceCodes[str(i)] = interfaceList[i]

# Handle command line arguments
if any(optionPassed == "-h" for optionPassed in sys.argv):
    print("USAGE:   sudo python3 [PLC IP Address] [Interface Code] [HMI IP Address]")
    print("Example: sudo python3 Unit_Test.py 192.168.56.1 0 192.168.56.2")
    print("Interface codes:")
    display_dict(interfaceCodes)
    sys.exit(0)

if len(sys.argv) != 4:
    print("Incorrect usage: pass PLC IP address, interface code, and HMI IP address as command-line arguments")
    print("Example:  sudo python3 Unit_Test.py 192.168.56.1 0 192.168.56.2")
    print("For list of interface codes, run with command line argument -h")
    sys.exit(2)

print("==== Begin Script ====")
PLCIP = sys.argv[1] #'192.168.1.31'  # PLC
print("PLC IP Address:",sys.argv[1])
PLCPORT = 502
print("PLC Port: ",PLCPORT)
if(sys.argv[2] in interfaceCodes.keys()):
    PLCIFACE = interfaceCodes[sys.argv[2]]
else:
    print("WARNING: Specified interface was not present in list of interfaces!")
    print("Try one of the following: ")
    display_dict(interfaceCodes)
    sys.exit(2)
print("Interface Name: ",PLCIFACE)
HMIIP = sys.argv[3]
print("HMI IP Address: ",sys.argv[3])

try:
    # Initialize system unit test
    system_unit = operation(PLCIP, PLCPORT, PLCIFACE, HMIIP)
    client = ModbusTcpClient(PLCIP)
    
    # # # Let the system flow through normal operation and communicate with the Datalogger
    
    # Let the system function using Automatic Valve Configuration
    system_unit.change_data_label("NormalOperation_AutoValveMode",'localhost',4321)
    system_unit.Normal_operation_1("AutoValveMode")
    
    # Let the system function using Automatic Pump Configuration
    system_unit.change_data_label("NormalOperation_AutoPumpMode",'localhost',4321)
    system_unit.Normal_operation_2("AutoPumpeMode")
except:
    print("ERROR - Unexpected error:",sys.exc_info()[0])
    raise
