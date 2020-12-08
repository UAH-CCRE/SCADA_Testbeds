<p>This project features work under copyright by the following: Copyright 2017 The University of Alabama in Huntsville. This applies to the Water Tank, the Single Gas Pipeline, and the 15km Gas Pipeline (5_VGP).</p>
This project features work licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. 
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/. 
You may also visit https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode 

<p align="center">
<img src="by-nc-sa.png" height=50>
</p>

# SCADA_Testbeds_Observation Overview
This repo's primary purpose is to provide frameworks and accompanying data from various models and testbeds.

# Directory Breakdown
Each directory is comprised of four main subdirectories: <br>
1) **Matlab Files** - simulink .slx files, README for setting up any dependencies<br>
2) **ScadaBR Files** - necessary HMI images and jsons to port into ScadaBR<br>
3) **Ladder Logic** - structured text files containing associated ladder logic<br>
4) **Attack Files** - includes attack scripts, corresponding config.json, and datalogger<br>
<pre>
SCADA_Testbeds_Observation
├───[Testbed_Name]_Complete
│   ├───Matlab_Files - simulink .slx files, README for setting up any dependencies
│   ├───ScadaBR_Files - necessary HMI images and jsons to port into ScadaBR
│   ├───Ladder_Logic - structured text files containing associated ladder logic
│   ├───Interface - configuration files for SimLink Interface program used with OpenPLC and Simulink
│   └───[Testbed_Name]_Attacks - includes attack scripts, config.json, and other testbed-specific resources.
│   README.md - documentation on the testbed
│   Unit_Test.py - script to run that validates the testbed's intended functionality and normal operation
│   Unit_Test_Comm.py - script that validates the testbed's functionality and communicates to datalogger
...
</pre>

# Environment
The framework used in this work was authored in a publication [here](https://www.researchgate.net/publication/326673221_Virtualization_of_SCADA_testbeds_for_cybersecurity_research_A_modular_approach). <br>
OpenPLC - https://www.openplcproject.com/<br>
ScadaBR - https://www.openplcproject.com/reference-installing-scadabr<br>
Matlab -> Simulink<br>

# Setup
## Initializing Ladder Logic in OpenPLC
1) Run OpenPLC Runtime.<br>
2) Navigate to http://localhost:8080/hardware and select the Simulink option (if on Linux, use Simlink with DNP3)<br>
3) Upload the ladder logic (a .st file) to http://localhost:8080/programs and launch the program.<br>
4) A minor modification is required in the OpenPLC code to allow proper communication with Simlink. Locate, in the directory where you installed OpenPLC, the file .../OpenPLC_v3/webserver/core/hardware_layer.cpp. (If this file doesn't exist yet, it is likely because you have not yet compiled and launched the program as described above.) Find the line of this file that reads "#define ANALOG_BUF_SIZE 8" and replace the "8" with "16". After doing this,  relaunch your program as described in step 3.<br>
## Running the Cygwin Terminal
3) If you have OpenPLC for Windows, Cygwin is already installed on your system. Navigate to C:\Users\[Your_Username]\OpenPLC\runtime <br>Run Cygwin.bat. This will open up a Cygwin Terminal. From this window, you can change directories to the simlink folder (or create it if it doesn't exist already) inside /home/\[Username]/.<br> Then copy the interface.cfg file from the testbed directory into this directory. The interface.cfg has user-specified parameters that you must configure prior to running (e.g. IP addresses, delay, etc.)<br>
4) Next, compile the simlink file. You can do this by using the following:
<pre>
g++ simlink.cpp -o simlink.exe -pthread
</pre>
5) Run the executable to make the connections:
<pre>
./simlink.exe
</pre>
Please note that the interface.cfg file must be in the same directory as simlink.exe.
This follows the [OpenPLC Simulink-Interface](https://github.com/thiagoralves/OpenPLC_Simulink-Interface). <br>
**Possible Sources of Error - Please Note:** Make sure your \*.st is running properly first before running simlink. If you do not see any connections made, you may need to disable your antivirus or windows defender temporarily. Disabling antivirus may also fix other issues.<br>

## Matlab & Simulink
6) After opening Matlab, launch Simulink and open the corresponding testbed model (\*.slx). To run the simulink models of the shared testbeds, the real-time slower module must be installed on Matlab. There are also a few toolbox dependencies that the user should be aware of. Each is detailed in the next couple sections.<br>

### The Real-Time Slower Installation
To install the *Real Time Slower*, open Matlab and navigate to the Real Time Slower directory. Then type mex sfun_time.c<br>
**Note: You may need to install the MinGW-w64 Compiler add-on.**

### The Matlab Compiler Runtime (MCR) Installation
The *Matlab Compiler Runtime* is needed to run the simulink executables managed by the Matlab Manager script, navigate to the correct zip on the [installation page on the Mathworks site](https://www.mathworks.com/products/compiler/matlab-runtime.html) and install the setup within the zip folder. 
**Note: You may need to set the environment variable of %PATH% to also include the directory of %MATLABROOT%\bin\win64, as described in [the documentation on generating and running executables outside Matlab](https://www.mathworks.com/help/releases/R2019a/dsp/ug/how-to-run-a-generated-executable-outside-matlab.html), just before the platform/command table.**  
Example: "C:\Program Files\MATLAB\R2019b\bin\win64"


### Simulink Toolbox Dependencies
The following toolbox dependencies are also needed:<br>
■ Simscape, Simscape Fluids, Simscape Electrical <br>
■ DSP System <br>
■ Signal Processing Toolbox <br>

7) Once you've completed these steps, simply run the testbed model.

### The OpenPLC_Interface
The simulink simulations will run as they are now. If you're running with different machines or different network settings than the typical localhost & PLC IP setup, please refer to the readme_openplc_interface for the OpenPLC_Interface block in the simulink models.

## Virtualization of the SCADA Model
TODO: do this section

# Attack Scripts
Each of the testbeds includes a Python 3 script that can be used to run a number of cyberattacks against the system. The Base.py file, present in the top-level directory, defines a BaseAttack class, which is extended by each of the testbed specific attack scripts, and a number of utility functions that are commonly used throughout all of the scripts. Our development and testing environment for these scripts was Kali Linux; some parts of the scripts may not perform as expected if run in another environment, especially a non-Linux environment. The attack scripts must be run as a super-user (either using sudo or from the root account). **It is important that each of the attack scripts be run from the [Testbed_Name]_Attacks directory (for example, the Gas_Pipeline_Attacks directory), rather than from any other directory. Additionally, the directory structure should not be modified; it is unlikely that the attack scripts will work as-is if the directory hierarchy is changed.** This is because the script makes assumptions about the the current working directory and the overall directory structure to resolve the location of certain other files. All of the attack scripts should be run with the following command line arguments:
<pre>
python(3) Attack_Script_Name.py [Interface] [PLC IP] [PLC Port] [HMI IP] [HMI Port]
</pre>
An example would be:
<pre>
python3 Water_Tank_Attack_Script.py eth0 100.100.100.1 502 100.100.100.2 9090
</pre>

## Dependencies
The Python libraries Scapy and Pymodbus are required for the attack scripts. **You must have at least Python3.7 to correctly acquire accurate times.**

### Ettercap
Ettercap is an open-source tool for Man-in-the-Middle attacks. It can be compiled from source available on GitHub; however; we recommend running the attack scripts from a Kali Linux environment, and Kali comes with Ettercap preloaded.<br>
**Possible sources of error in Ettercap**:
The most common issue with Ettercap is that it does not have permission to read from or write to the directories it runs in. As we said above, the attack scripts must be run as root (using sudo or from the root account); to provide the necessary permissions, the Ettercap configuration file (located in Kali at /etc/ettercap/etter.conf) should be modified so that the variables "ec_uid" and "ec_gid" are both set to 0. It may also be necessary to grant the root user ownership of the top-level directory of our release and all subdirectories. If issues with Ettercap persist, you may be able to find more information by changing the debug setting in the Base.ettercap_attack() method in Base.py.

### The _global_resources directory
This directory contains a number of resource files that are shared between the attack scripts. **This directory must not be renamed or moved.**

# The Datalogger
This Python script's primary purpose is to log data from various models and testbeds.

## Overview
The datalogger records and labels data sniffed from the network. As it sniffs the network, it specifically records packet information and accordingly calculates metrics for every packet (like Shannon entropy, process time, mean flow, etc.). This program ultimately assists in the development of (supervised) machine learning algorithms to learn the behavior of testbeds and further develop/enhance intrusion detection systems. This can allow for a binary (Normal v. Anomaly) classification model or a multi-category model that spans the types of attacks. As a way to get more detailed network data, the datalogger also attempts to start Wireshark in the background.<br>
TLDR:
1) Records and labels network data
2) Calculates packet info & metrics (e.g. Shannon entropy)
3) Assists (supervised) machine learning purposes
4) Binary (Normal v. Anomaly) classification that can be expanded upon

## Dependencies and Required Libraries
Required libraries for Datalogger.py include: pymodbus, scapy, pickle<br>
**Note:** Scapy requires administrative privileges in Windows to capture the machine's network traffic.</br>

### Other Possible Sources of Error
To sniff packets with the scapy library, you may need winpcap. Some distributions of linux, such as Kali, include this. You may have to install it separately. **Installing Wireshark is strongly recommended**, as it is a great tool to verify and visualize the packets yourself while also installing the necessary winpcap and pcap dependencies within its own installation. If you have Wireshark installed on your system, you should see a network_traffic.pcap file appear along with the other datalogs. If this file doesn't appear, it is likely because Wireshark lacks permission to write to that directory; granting the root user ownership of the directory or changing Wireshark's settings may be necessary.  
If you 

## Usage
The Datalogger.py file is present in the _global_resources directory; the attack scripts will start it automatically in the appropriate location to generate the log. By default, the datalogger's console output is suppressed within the attack script; if you would like to see this console output alongside the attack script's output, you may change the debug setting in the Datalogger.\_\_init\_\_() method in Base.py (be aware that the console will likely be cluttered by doing this, and it may be difficult to distinguish between the two outputs, but it may be useful for debugging purposes). The Config.json file, which provides important information to the datalogger, is located in the same directory as the attack script in our default configuration. When running the attack script, the datalogger must also be run manually on the PLC and HMI in order to create a datalog from each of these varying perspectives. When doing so, the system-specific Config.json file must be copied into the working directory where the datalogger is started. The datalogger takes the following command line arguments:
<pre>
python Datalogger.py -IP [IP address for Sniffing] -P [Port] -C [Class label] -I [Interface]
</pre>
The IP address for sniffing will typically be the PLC's IP address. The default port used for MODBUS is 502. We recommend that the passed class label be given as "Initialization" to easily distinguish this data from the data that is generated from a specific operation, which will receive a separate label from the attack script. An example would be:
<pre>
python Datalogger.py -IP 100.100.100.2 -P 502 -C Initialization -I eth0
</pre>

## JSON Config
The JSON config file contain the names of each of the register types. This includes coils, discrete input registers, holding registers, and input registers as well as each of their respective offsets. If there are no registers of a particular type, then leave the field empty. Please note that the network interface should also be written in the Config.json (linux often uses "eth0"). The file itself should follow this format:
<pre>
{
"coils" : {
	"COIL_NAME":COIL_OFFSET,
},
"discreteInputs":{
	"DISCRETE_INPUT_REGISTER_NAME":DISCRETE_INPUT_REGISTER_OFFSET,
},
"holdingRegisters":{
	"HOLDING_REGISTER_NAME":HOLDING_REGISTER_OFFSET,
},
"inputRegisters":{
	"INPUT_REGISTER_NAME":INPUT_REGISTER_OFFSET,
},
"set_interval_period":WRITE_EVERY___SAMPLES,
"Network_Interface":"NETWORK_INTERFACE_NAME"
}
</pre>

## Acknowledgments
This project uses many wonderful software, python libraries, and utilities that we simply couldn't do without. The following are some of the most crucial
- OpenPLC
- Wireshark
- Scapy
- Pymodbus
- TCPdump

