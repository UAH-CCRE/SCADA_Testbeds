# -------------------------------------------------------------------------------------------------
# This Python script creates a GUI for the robotic arm SCADA testbed. The length of the robotic
# arm and the current state of the robotic arm is querried from the MODBUS memory of the PLC
# Program by:-
# Rishabh Das
# Date:- 4th October 2018
# -------------------------------------------------------------------------------------------------
import math
import pygame
import time
import sys
from pyModbusTCP.client import ModbusClient

# -------------------------------------------------------------------------------------------------
# Declaring the specification fo the robotic arm as global variable. The coordinates are also
# declared as global variable
# -------------------------------------------------------------------------------------------------
# Declaring the coordinate of the two joints of the robotic arm
x = 0
y = 0
x1 = 0
y1 = 0

# -------------------------------------------------------------------------------------------------
# This function queries the PLC to get the Specification of the Robotic arm
# -------------------------------------------------------------------------------------------------
def run_gui():
    global x, y, x1, y1
    # Declaring Modbus PLC
    print("The IP address of the PLC is:",sys.argv[1])

    #Declaring the modbus client 
    try:
        client = ModbusClient(host=sys.argv[1],port=502)
    except ValueError:
        print("Error with host or port number")
        
    # Declaring the colors required int he graphics. This is in RGB format
    BLACK = (0, 0, 0)
    GREY =  (169, 169, 169)
    BLUE =  (0, 0, 255)
    GREEN = (0, 255, 0)
    RED =   (255, 0, 0)

    # Drawing the robotic arm in pygame. The one time initilization is performed to use the Pygame instance
    pygame.init()
    size = [600, 600]
    screen = pygame.display.set_mode(size)
    pygame.display.set_caption("Robotic Arm-Rishabh Das-UAH")
    message = pygame.font.SysFont("monospace",15)
    header = pygame.font.SysFont("monospace",30)
    
    

    run= True
    # This is the main loop that gets the current position of the robotic arm and updates the graphics after
    # every 100 ms
    while run:
        # -----------------------------------------------------------------------------------------
        # MODBUS Section of the loop. The reading of the registers are collected fromt he PLC memory
        # -----------------------------------------------------------------------------------------
        # check the connectivity of the TCP client to the GUI to the PLC
        if not client.is_open():
            if not client.open():
                print("Unable to Connect to " + sys.argv[1] + ":502")

        # Reading the registers for current lengths and the thetas
        theta_list = client.read_input_registers(2, reg_nb=2)
        length_list = client.read_holding_registers(4,reg_nb=2)

        # Print the list of the thetas
        # print(theta_list)
        # print(length_list)

        # Get the length of the arms from the MODBUS memory of the PLC to local variables
        length_1 = length_list[0]
        length_2 = length_list[1]

        if length_1 != 0  and length_2 != 0:
            ratio = (length_1/length_2)
        else:
            print("Arm length set to 0 \nCannot render graphics")
            sys.exit(0)
        length_2 = 250/(ratio+1)
        length_1 = 250 - length_2

        if length_1 > 0 and length_2 > 0:
            # Get the current Theta positions of the arms from the MODBUS memory of the PLC to local variables
            Theta_1 = theta_list[0]
            Theta_2 = theta_list[0] + theta_list[1]

            # Calculate the coordinates
            calculate_coordinates(length_1, length_2, Theta_1, Theta_2)

            # -----------------------------------------------------------------------------------------
            # This section of the loop creates the GUI of the robotic arm kusing the pygame library
            # -----------------------------------------------------------------------------------------
            screen.fill(BLACK)
            # Drawing the robotic arm in pygame
            pygame.draw.line(screen, GREEN, [275, 275], [275 + x1, 275 - y1], 5)
            pygame.draw.line(screen, GREEN, [275 + x1, 275 - y1], [275 + x, 275 - y], 5)
            pygame.draw.circle(screen, BLUE, [275, 275], 7)
            pygame.draw.circle(screen, BLUE, [275 + round(x1), 275 - round(y1)], 7)
            pygame.draw.circle(screen, BLUE, [275 + round(x), 275 - round(y)], 7)

            # Calculate the coordinates
            calculate_coordinates(length_list[0], length_list[1], Theta_1, Theta_2)
            disp_coor1=message.render("("+str(int(x1))+","+str(int(y1))+")",1,GREEN)
            disp_coor2=message.render("("+str(int(x))+","+str(int(y))+")",1,GREEN)
            calculate_coordinates(length_1, length_2, Theta_1, Theta_2)
            screen.blit(disp_coor1,(275 + round(x1), 275 - round(y1)))
            screen.blit(disp_coor2,(275 + round(x), 275 - round(y)))
            
            #Displaying Heading
            title=header.render("Robotic Arm",1,GREEN)
            screen.blit(title,(10,1))
            
            #Displaying Theta values
            theta1_values=message.render("Theta first joint:"+str(theta_list[0]),1,GREEN)
            theta2_values=message.render("Theta second joint:"+str(theta_list[1]),1,GREEN)
            screen.blit(theta1_values,(400,550))
            screen.blit(theta2_values,(400,570))
            
            # Checking if the user clicked on the close button
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    run = False
                    sys.exit(0)
            pygame.display.update()

            #Controls the refresh rate of the robotic arm
            time.sleep(0.05)
        else:
            print("Invalid length! The GUI cannot be rendered!")
            sys.exit(0)

# -------------------------------------------------------------------------------------------------
# This function calculates the coordinates of the arm
# -------------------------------------------------------------------------------------------------
def calculate_coordinates(length_1,length_2,Theta_1,Theta_2):
    global x,y,x1,y1
    # Calculating the coordinate of the first joint
    x1= length_1*(math.cos(Theta_1*0.0174533))
    y1= length_1*(math.sin(Theta_1*0.0174533))
    # Calculating the coordinate of the end of the robotic arm
    x= length_1*(math.cos(Theta_1*0.0174533)) + length_2*(math.cos(Theta_2*0.0174533))
    y= length_1*(math.sin(Theta_1*0.0174533)) + length_2*(math.sin(Theta_2*0.0174533))
    #print("The final coordinate of the Robotic arm:(x1,y1)",x1,y1)
    #print("The final coordinate of the Robotic arm:(x,y)",x,y)

# -------------------------------------------------------------------------------------------------
# Main Function controlling the flow of the program
# -------------------------------------------------------------------------------------------------
def main():
    # run the function to create the robotic arm visulaization
    run_gui()

if __name__ == '__main__':
    main()










