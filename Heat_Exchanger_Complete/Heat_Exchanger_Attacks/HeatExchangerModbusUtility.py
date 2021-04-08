"""
# ------------------------------------------------------------------------------
# Property of UAH (2020)
# This project features work licensed under the Creative Commons
# Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy
# of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/. You
# may also visit https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
# Authors: Mohammad Einaam Alim, Jack Smalligan, Raphael Ferreira Barata de Oliveira,
#           Christopher Nguyen, Rishabh Das
# ------------------------------------------------------------------------------
"""
from pymodbus.client.sync import ModbusTcpClient
import struct

REG_DICT={
    "Flow":         {"size":2,  "offset": 0,    "type": "holding"  },
    "ColdTempIn":   {"size":2,  "offset": 1,    "type": "input"    },
    "ColdTempOut":  {"size":2,  "offset": 4,    "type": "input"    },
    "HotMassFlowIn":{"size":2,  "offset": 3,    "type": "input"    },
    "HotTempIn":    {"size":2,  "offset": 2,    "type": "input"    },
    "Setpoint":     {"size":2,  "offset": 1,    "type": "holding"  },
    "ShellPress":   {"size":2,  "offset": 6,    "type": "input"    },
    "Temperature":  {"size":2,  "offset": 0,    "type": "input"    },
    "TubePress":    {"size":2,  "offset": 5,    "type": "input"    },
    "PID_kp":       {"size":4,  "offset": 2048, "type": "holding"  },
    "PID_td":       {"size":4,  "offset": 2052, "type": "holding"  },
    "PID_tr":       {"size":4,  "offset": 2050, "type": "holding"  },
}

class ModbusUtility():
    def __init__( self, ip ):
        self.modcli = ModbusTcpClient(ip)

    @staticmethod
    def getReg( reg, index=0 ):
        # Registers are stored without decimal points. Their values represent
        # the number multiplied by 100 so we undo that to get the real value

        # We assume desired register is first element, pass in optional index to change
        return( float( reg[index] ) / 100 )

    @staticmethod
    def setReg( data ):
        # Since register data is stored without decimals and multiplied by 100 that is
        # what we supply
        return( int( data*100 ) )

    def PrintAllRegisters( self ):
        print("Printing registers...")
        for key in REG_DICT.keys():
            data = self.ReadRegister( key )

            print( "Register [{}]: {}".format( key, data ) )

    def ReadRegister( self, name ):
        t = REG_DICT[name]["type"]    # Current register type
        o = REG_DICT[name]["offset"]  # Current register offset
        s = REG_DICT[name]["size"]    # Current register size in bytes.

        # If the size is greater the 2 bytes unpack it like it is a float.
        # Really we should also check that this is a float but it doesn't matter since
        # our system only has 3 registers that are 4 bytes long and they are all floats
        if( t == "holding" ):
            if( s > 2 ):
                data = self.modcli.read_holding_registers(o,s,unit=1).registers
                reg = struct.unpack(">f", data[0].to_bytes(2,"big") + data[2].to_bytes(2,"big") )
                return( reg[0] )

            data = self.modcli.read_holding_registers(o,1,unit=1)
        else:
            data = self.modcli.read_input_registers(o,1,unit=1)

        return( self.getReg( data.registers ) )

    def WriteRegister( self, name, num ):
        o = REG_DICT[name]["offset"]  # Current register offset
        s = REG_DICT[name]["size"]/2  # Current register size
        t = REG_DICT[name]["type"]    # Current register type

        if( t == "holding" ):
            if( s > 1 ):
                data = struct.unpack( "HH", struct.pack("=f", num)  )
                # Sending these backwards is a conscious decision. Unpack always returns
                # them in 'backwards' order.
                self.modcli.write_registers( o, data[1] )
                self.modcli.write_registers( o+1, data[0] )
            else:
                data = num
                self.modcli.write_registers( o, self.setReg( data ) )

        elif( t == "input" ):
            data = num
            self.modcli.write_registers( o+800, self.setReg( data ) )
