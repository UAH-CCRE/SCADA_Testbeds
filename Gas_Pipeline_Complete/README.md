Copyright 2017 The University of Alabama in Huntsville

# (Single) Gas Pipeline Testbed Overview
This testbed models a heating, ventilation, and air conditioning (HVAC) system. As the name suggests, it is a control system with a PID scheme that provides thermal stability and acceptable indoor temperature quality.

## List of Functions
* Regulates pressure in a pipeline by turning a pump on and off and/or opening and closing a valve, using an on/off control scheme
* Pump Mode on/off (automatic)
* Valve Mode on/off (automatic)
* Manual Mode on/off
* Pump on (manual)
* Valve on (manual)
* Store historical data
* Remote monitoring
* Remote control

## List of Addressable Components
The ladder logic creates ten addressable components.<br>

| Name | Location   | Description |
| :-- | :-: | :-- |
| pressure | %IW0 | Receive pressure input from user |
| min_sp | %QW1 | Input for setting the min psi value |
| max_sp | %QW2 | Input for setting the max psi value |
| mode_register | %QW3 | Register for setting the mode of the system |
| pump_register | %QW4 | Stores the value of the pump |
| valve_register | %QW5 | Stores the value of the valve |
| pressure_psi | %QW6 | Measure the pressure in psi |
| pump | %QX0 | Allows for manually controlling the pump |
| valve | %QX1 | Allows for manually controlling the valve |
