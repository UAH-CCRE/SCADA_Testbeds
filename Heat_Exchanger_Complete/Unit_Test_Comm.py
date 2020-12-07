# -*- coding: utf-8 -*-
"""
Created on Tue Mar 10 15:43:48 2020

@authors: Rishabh Das, Mohammad Einaam Alim, Raphael Barata de Oliveira, Jack Smalligan, Christopher Nguyen

This script verifies that the system can operate normally by itself.

In order to verify operation while logging data, run Datalogger.py before running the Unit_Test_Comm.py script.

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
import sys

sys.path.append('./Heat_Exchanger_Attacks')
from HeatExchangerModbusUtility import ModbusUtility
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
		
        self.he = ModbusUtility(IP)
        self.CurrentAttack = None
        self.ThreadDict = {}
		
    def change_data_label(self,label,IP,Port):
        """
            calling this function changes the data label of the datalogger
        """
        client_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        address = (IP,int(Port))
        client_sock.connect(address)
        dat = pickle.dumps("Change|"+str(label))
        client_sock.send(dat)
	
    def NormalOperation1( self , label ):
        # #30 -- Set all values normal
        print("Performing Normal Operation " + label)
        self.he.WriteRegister( "Setpoint", 50 )
        self.he.WriteRegister( "PID_td", .0 )
        self.he.WriteRegister( "PID_tr", .1 )
        self.he.WriteRegister( "PID_kp", .4)
        time.sleep(15)

    def NormalOperation2( self, label ):
        # #31 -- Set all values normal
        print("Performing Normal Operation " + label)
        self.he.WriteRegister( "Setpoint", 45 )
        self.he.WriteRegister( "PID_td", .0 )
        self.he.WriteRegister( "PID_tr", .1 )
        self.he.WriteRegister( "PID_kp", .4)
        time.sleep(15)

    def NormalOperation3( self, label ):
        # #32 -- set all values normal
        print("Performing Normal Operation " + label)
        self.he.WriteRegister( "Setpoint", 35 )
        self.he.WriteRegister( "PID_td", .0 )
        self.he.WriteRegister( "PID_tr", .1 )
        self.he.WriteRegister( "PID_kp", .4)
        time.sleep(15)
        
    def NormalOperation4( self, label ):
        # #32 -- set random, reasonable values
        print("Performing Normal Operation " + label)
        self.he.WriteRegister( "Setpoint", random.randint(25, 70) )
        self.he.WriteRegister( "PID_td", .0 )
        self.he.WriteRegister( "PID_tr", .1 )
        self.he.WriteRegister( "PID_kp", .4)
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
    
    # # # Let the system flow through normal operation as is, with the Datalogger
    
    system_unit.change_data_label("Normal_Operation_1",'localhost',4321)
    system_unit.NormalOperation1("Range_50")			# 50
    
    system_unit.change_data_label("Normal_Operation_2",'localhost',4321)
    system_unit.NormalOperation2("Range_45")			# 45
    
    system_unit.change_data_label("Normal_Operation_3",'localhost',4321)
    system_unit.NormalOperation3("Range_35")			# 35
    
    system_unit.change_data_label("Normal_Operation_4",'localhost',4321)
    system_unit.NormalOperation4("Range_Rand")			# in range(25,70)
except:
    print("ERROR - Unexpected error:",sys.exc_info()[0])
    raise