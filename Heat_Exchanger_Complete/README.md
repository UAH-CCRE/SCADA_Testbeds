This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. 
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/. 
You may also visit https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode 

<p align="center">
<img src="../by-nc-sa.png" height=50>
</p>

# Heat Exchanger Testbed Overview
This testbed models a system that regulates the transfer of heat between two fluids.

## Stream Quadrants
There are four quadrants to this model, as there is a hot side and a cold side as well as an inlet stream and an outlet stream. Identifying each starting from the upper left corner and going clockwise around the image, we have:<br>
1. Hot Side - Inlet Stream
2. Hot Side - Outlet Stream
3. Cold Side - Inlet Stream
4. Cold Side - Inlet Stream

The cold side denotes the coolant for the system, which absorbs the heat by the hot side's stream. The temperatures of the inlet and outlet streams are also indicated.<br>
## System Monitoring
The measurements the operator can monitor are:<br>
1. Tube Side Pressure Drop
2. Shell Side Pressure Drop
3. Cold Mass Flow In
4. Hot Mass Flow In

## System Configuration
The system uses a PID scheme. There are 4 control points by which an operator may configure the system: the overall system temperature (ºC), the proportional coefficient Kp, integral coefficient Tr, and derivative coefficient Td. These are all configurable from the HMI.<br>

## Visualization Graph
The plot graphs the flow and temperature against time. You can set the amount of time you would like to plot against by hovering over the tooltip icon and changing the time selection. Otherwise, the plot may disappear after some time has elapsed.<br>

## Simulink Model
Note that you must have Simscape and Simscape Fluids to run the system.
