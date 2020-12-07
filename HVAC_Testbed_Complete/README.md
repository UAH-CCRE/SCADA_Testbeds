This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. 
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/. 
You may also visit https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode 

<p align="center">
<img src="../by-nc-sa.png" height=50>
</p>

# HVAC Testbed Overview
This testbed models a heating, ventilation, and air conditioning (HVAC) system. As the name suggests, it is a control system with a PID scheme that provides thermal stability and acceptable indoor temperature quality.

## Simulink Model
We created a HVAC from a model we found in Matlab [here](https://www.mathworks.com/help/simulink/slref/thermal-model-of-a-house.html).The system works largely the same, though we added cooling since the original had just heating. We replaced the thermostat with a controller entity to handle the heater and cooler modules in addition to the overall temperature. <br>
Note that there is a switch in the Simulink model, which controls using either a hot day's outdoor temperature (default: 90 ºF) or a cold day's outdoor temperature (default: 55 ºF).
