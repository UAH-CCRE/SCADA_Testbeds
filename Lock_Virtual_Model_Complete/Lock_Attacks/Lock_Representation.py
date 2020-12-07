"""
# ------------------------------------------------------------------------------
# Property of UAH (2020)
# This project features work licensed under the Creative Commons
# Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy
# of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/. You
# may also visit https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
# Authors: Jack Smalligan, Raphael Barata de Oliveira, Mohammad Einaam Alim
# ------------------------------------------------------------------------------
"""
from pymodbus.client.sync import ModbusTcpClient
import json
from enum import Enum, auto
from pymodbus.exceptions import ModbusIOException

# For the unintiated, the underscore in front of some of the variables and methods indicates that
# those members are intended to be private (i.e. they should not be accessed outside of this module
# (although they still can be from a technical perspective))

def _get_modbus_assignments():
        with open("Config.json") as f:
            modbus_addresses = json.load(f)
        coils = modbus_addresses["coils"]
        holding_reg = modbus_addresses["holdingRegisters"]
        input_reg = modbus_addresses["inputRegisters"]
        return coils, holding_reg, input_reg

class LockState(Enum):
    """
        Enum that represents the phase of the operation that the current boat in the lock is in.
        NONE indicates that there is no boat currently in the lock.
    """
    NONE = auto()
    UPPER_GATE_CHANGING = auto()
    BOAT_AT_TOP = auto()
    LOWER_GATE_CHANGING = auto()
    BOAT_AT_BOTTOM = auto()
    WATER_LEVEL_CHANGING = auto()

class _ModbusType(Enum):
    """
        Enum of modbus types.
    """
    COIL = 0
    HOLDING = 1
    INPUT = 2

class Lock:
    """
        The purpose of this class is to offer an abstraction for the lock that makes it easier to interact
        with for MODBUS purposes by removing magic numbers, as well as to remember the state of the system.

        DO NOT CHANGE THE Config.json FILE UNLESS YOU HAVE CHANGED THE CORRESPONDING USAGES HERE.
    """

    # retrieve coil and register assignments from json
    # these are dictionaries mapping a name to an offset
    _COILS, _HOLDING_REGISTERS, _INPUT_REGISTERS = _get_modbus_assignments()

    _RAW_COUNTS_PER_VALUE = 100.0

    @classmethod
    def get_raw_counts_per_value(cls):
        return cls._RAW_COUNTS_PER_VALUE

    def __init__(self, ip, port):
        self.client = ModbusTcpClient(ip, port)
        self.cache = {}

    def _generic_op(self, addr_type, name, value=None):
        """
            All of the methods in this class use this method. It is the sole handler for
            interacting with the client and the modbus configuration.

            The address type should be one of the defined constants in the _ModbusTypes enum:
                COIL, HOLDING, INPUT

            The name passed must match the declared name in the modbus configuration.

            If value is passed, we will write it to the specified location and return None.
                (if addr_type is INPUT, a value may not be passed; a TypeError will be issued)

            If a value is not passed, the value at the specified location will be returned
            (as a boolean if it is a coil, or an int if it is a register).
        """

        if addr_type == _ModbusType.COIL:
            if value is None:
                new = self.client.read_coils(Lock._COILS[name])
            else:
                self.client.write_coil(Lock._COILS[name], value)
                return None
        elif addr_type == _ModbusType.HOLDING:
            if value is None:
                new = client.read_holding_registers(Lock._HOLDING_REGISTERS[name]).getRegister(0)
            else:
                self.client.write_register(Lock._HOLDING_REGISTERS[name], value)
                return None
        elif addr_type == _ModbusType.INPUT:
            if value is not None:
                raise TypeError("A value cannot be written to an input register")
            new = self.client.read_input_registers(Lock._INPUT_REGISTERS[name])
        else:
            raise ValueError("Inappropriate value for addr_type. Use one of the class constants.")

        if type(new) == ModbusIOException:
            raise ModbusIOException("Modbus connection error.") from None
        else:
            if addr_type == _ModbusType.COIL:
                return bool(new.getBit(0))
            else: # input and holding
                return int(new.getRegister(0))


    def get_state(self):
        """
            Return the current state of the lock, based on an inference from the current data returned by the
            PLC.
        """

        # a gate being fully open indicates a boat passing through
        if self.get_upper_gate_value() == 90:
            return LockState.BOAT_AT_TOP
        elif self.get_lower_gate_value() == 90:
            return LockState.BOAT_AT_BOTTOM

        # a gate opening or closing (obviously) indicates that it is changing
        elif self.open_lower_gate_command(issue=False) or self.close_lower_gate_command(issue=False):
            return LockState.LOWER_GATE_CHANGING
        elif self.open_upper_gate_command(issue=False) or self.close_upper_gate_command(issue=False):
            return LockState.UPPER_GATE_CHANGING

        # As long as the lock doesn't meet the conditions for one of the preceding states, a changing water level
        # is indicated by either of the valves not being closed or in the process of opening or closing
        elif (self.get_upper_valve_value() > 0 or
                self.get_lower_valve_value() > 0 or
                self.open_lower_valve_command(issue=False) or
                self.open_upper_valve_command(issue=False) or
                self.close_lower_valve_command(issue=False) or
                self.close_upper_gate_command(issue=False)
            ):
            return LockState.WATER_LEVEL_CHANGING

        # if none of the preceding are satisfied, no boat is in the lock (for our purposes)
        else:
            return LockState.NONE

    # ---------------- UPPER GATE --------------------
    def open_upper_gate_command(self, issue=True):
        """
            If issue is True, send the command for the gate to open; otherwise, return the current status
            of the coil.
        """
        if issue:
            self._generic_op(_ModbusType.COIL, "Upper_Gate_Open_Command", True)
        else:
            return self._generic_op(_ModbusType.COIL, "Upper_Gate_Open_Command")

    def close_upper_gate_command(self, issue=True):
        """
            If issue is True, send the command for the gate to close; otherwise, return the current status
            of the coil.
        """
        if issue:
            self._generic_op(_ModbusType.COIL, "Upper_Gate_Close_Command", True)
        else:
            return self._generic_op(_ModbusType.COIL, "Upper_Gate_Close_Command")

    def get_upper_gate_value(self):
        return self._generic_op(_ModbusType.INPUT, "Upper_Gate_Value")/Lock._RAW_COUNTS_PER_VALUE

    def is_chamber_equal_to_reservoir(self):
        # this method is related to whether the upper gate should open,
        # the upper gate can open when they are equal
        return self._generic_op(_ModbusType.COIL, "Reservoir_and_Chamber_Depths_Equal")

    # ---------------- UPPER VALVE -------------------
    def open_upper_valve_command(self, issue=True):
        """
            If issue is True, send the command for the valve to open; otherwise, return the current status
            of the coil.
        """
        if issue:
            self._generic_op(_ModbusType.COIL, "Upper_Valve_Open_Command", True)
        else:
            return self._generic_op(_ModbusType.COIL, "Upper_Valve_Open_Command")

    def close_upper_valve_command(self, issue=True):
        """
            If issue is True, send the command for the valve to close; otherwise, return the current status
            of the coil.
        """
        if issue:
            self._generic_op(_ModbusType.COIL, "Upper_Valve_Close_Command", True)
        else:
            return self._generic_op(_ModbusType.COIL, "Upper_Valve_Close_Command")

    def get_upper_valve_value(self):
        return self._generic_op(_ModbusType.INPUT, "Upper_Valve_Value")/Lock._RAW_COUNTS_PER_VALUE

    # --------------- LOWER GATE ---------------------
    def open_lower_gate_command(self, issue=True):
        """
            If issue is True, send the command for the gate to open; otherwise, return the current status
            of the coil.
        """
        if issue:
            self._generic_op(_ModbusType.COIL, "Lower_Gate_Open_Command", True)
        else:
            return self._generic_op(_ModbusType.COIL, "Lower_Gate_Open_Command")

    def close_lower_gate_command(self, issue=True):
        """
            If issue is True, send the command for the gate to close; otherwise, return the current status
            of the coil.
        """
        if issue:
            self._generic_op(_ModbusType.COIL, "Lower_Gate_Close_Command", True)
        else:
            return self._generic_op(_ModbusType.COIL, "Lower_Gate_Close_Command")

    def get_lower_gate_value(self):
        return self._generic_op(_ModbusType.INPUT, "Lower_Gate_Value")/Lock._RAW_COUNTS_PER_VALUE

    def is_chamber_equal_to_tailwater(self):
        # this method is related to whether the lower gate should open,
        # the lower gate can open when they are equal
        return self._generic_op(_ModbusType.COIL, "Tailwater_and_Chamber_Depths_Equal")

    # --------------- LOWER VALVE -------------------
    def open_lower_valve_command(self, issue=True):
        """
            If issue is True, send the command for the valve to open; otherwise, return the current status
            of the coil.
        """
        if issue:
            self._generic_op(_ModbusType.COIL, "Lower_Valve_Open_Command", True)
        else:
            return self._generic_op(_ModbusType.COIL, "Lower_Valve_Open_Command")

    def close_lower_valve_command(self, issue=True):
        """
            If issue is True, send the command for the valve to close; otherwise, return the current status
            of the coil.
        """
        if issue:
            self._generic_op(_ModbusType.COIL, "Lower_Valve_Close_Command", True)
        else:
            return self._generic_op(_ModbusType.COIL, "Lower_Valve_Close_Command")

    def get_lower_valve_value(self):
        return self._generic_op(_ModbusType.INPUT, "Lower_Valve_Value")

    # ------------- EMERGENCY/WARNINGS ---------------
    def sound_warning(self, isWarning=None):
        """
            Write the value of isWarning to the warning button coil, if it is passed; otherwise,
            return the value of warning button coil.
        """
        if isWarning is None:
            return self._generic_op(_ModbusType.COIL, "Warn_Button")
        else:
            self._generic_op(_ModbusType.COIL, "Warn_Button", isWarning)


    def gate_emergency(self, isEmergency=None):
        """
            Write the value of isEmergency to the gate emergency coil, if it is passed; otherwise,
            return the value of gate emergency coil.
        """
        if isEmergency is None:
            return self._generic_op(_ModbusType.COIL, "Emergency_Gate")
        else:
            self._generic_op(_ModbusType.COIL, "Emergency_Gate", isEmergency)

    def valve_emergency(self, isEmergency=None):
        """
            Write the value of isEmergency to the valve emergency coil, if it is passed; otherwise,
            return the value of valve emergency coil.
        """
        if isEmergency is None:
            return self._generic_op(_ModbusType.COIL, "Emergency_Valve")
        else:
            self._generic_op(_ModbusType.COIL, "Emergency_Valve", isEmergency)

    # -------------------- DEPTHS --------------------
    def get_chamber_depth(self):
        return self._generic_op(_ModbusType.INPUT, "Chamber_Depth")/Lock._RAW_COUNTS_PER_VALUE

    def get_reservoir_depth(self):
        return self._generic_op(_ModbusType.INPUT, "Reservoir_Depth")/Lock._RAW_COUNTS_PER_VALUE

    def get_tailwater_depth(self):
        return self._generic_op(_ModbusType.INPUT, "Tailwater_Depth")/Lock._RAW_COUNTS_PER_VALUE

    def get_sill_height(self):
        return self._generic_op(_ModbusType.INPUT, "Sill_Height")/Lock._RAW_COUNTS_PER_VALUE

    # ---------------- OPERATIONS --------------------
    def Fill_Chamber(self):
        """
            Fills up the chamber. Will idle for completion.
        """

        self.state = LockState.WATER_LEVEL_CHANGING

        # idle for lower valve to close
        while self.get_lower_valve_value() > 0:
            self.close_lower_valve_command()

        # idle for chamber to fill
        while not self.is_chamber_equal_to_reservoir():
            self.open_upper_valve_command()

        # when the chamber is full, close the upper valve
        # idle for upper valve to close
        while self.get_upper_valve_value() > 0:
            self.close_upper_valve_command()

    def Empty_Chamber(self):
        """
            Empties the chamber. Will idle for completion.
        """

        self.state = LockState.WATER_LEVEL_CHANGING

        # idle for upper valve to close
        while self.get_upper_valve_value() > 0:
            self.close_upper_valve_command()

        # idle for chamber to empty
        while not self.is_chamber_equal_to_tailwater():
            self.open_lower_valve_command()

        # when the chamber is empty, close the lower valve
        # idle for lower valve to close
        while self.get_lower_valve_value() > 0:
            self.close_lower_valve_command()

    def Open_Upper_Gate(self):
        """
            Opens the upper gate. Will idle for completion.

            It is a precondition that the chamber be at the reservoir height. If it isn't, the function will
            return without doing anything. (At the ladder logic level, the operation would be disallowed, even
            if we attempted to open it.)

        """

        if not self.is_chamber_equal_to_reservoir():
            return

        self.state = LockState.UPPER_GATE_CHANGING

        # 90 is fully open
        while self.get_upper_gate_value() != 90:
            self.open_upper_gate_command()

        # when we're done opening, the boat is entering
        self.state = LockState.BOAT_AT_TOP

    def Close_Upper_Gate(self):
        """
            Close the upper gate. Will idle for completion.
        """

        self.state = LockState.UPPER_GATE_CHANGING

        # 7 is fully closed
        while self.get_upper_gate_value() != 7:
            self.close_upper_gate_command()

    def Open_Lower_Gate(self):
        """
            Opens the lower gate. Will idle for completion.

            It is a precondition that the chamber be at the tailwater height. If it isn't, the function will
            return without doing anything. (At the ladder logic level, the operation would be disallowed, even
            if we attempted to open it.)
        """

        if not self.is_chamber_equal_to_tailwater():
            return

        self.state = LockState.LOWER_GATE_CHANGING

        # 90 is fully open
        while self.get_lower_gate_value() != 90:
            self.open_lower_gate_command()

        # when we're done opening, the boat is entering
        self.state = LockState.BOAT_AT_BOTTOM

    def Close_Lower_Gate(self):
        """
            Close the lower gate. Will idle for completion.
        """
        self.state = LockState.LOWER_GATE_CHANGING

        # 7 is fully closed
        while self.get_lower_gate_value() != 7:
            self.close_lower_gate_command()
