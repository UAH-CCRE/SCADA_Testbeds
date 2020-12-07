# this script is used in the calculated injection script

"""
    It takes the following args:
    increment_file.py [FILE] [START] [INCREMENT AMOUNT] [END] [TIME INTERVAL] (REPEAT)

    START and END should be integers, 
    INCREMENT AMOUNT may be a float, but only integers will be written to the file
    TIME INTERVAL can be a float, and should have units of  seconds

    REPEAT is optional; it should be 0 or 1.
        If it isn't present, it is assumed to be 0.
        If it is 1, the program will cycle between the START and END until it is interrupted.
        If it is 0, the program will go from START to END, and then will idle until interrupted.
"""

import sys
import time
import os

fileName = sys.argv[1]

#collect command line values
start_val = int(sys.argv[2])
increment = float(sys.argv[3])
end_val = int(sys.argv[4])
time_interval = float(sys.argv[5])
repeat = False

if len(sys.argv) == 7 and sys.argv[6] == "1":
    repeat = True

ge_expr = lambda current_val, target_val: current_val >= target_val
le_expr = lambda current_val, target_val: current_val <= target_val

def increment_loop(start, stop, step):
    expr = None
    
    if start < stop:
        assert(step > 0)
        expr = le_expr
    elif start > stop:
        assert(step < 0)
        expr = ge_expr
    else:
        raise ValueError("start must not be equal to stop")

    while expr(start, stop):
        with open(fileName, "w") as f:
            f.write(str(int(start)))
        start += step
        time.sleep(time_interval)

def main():
    # always run once, from START to END
    increment_loop(start_val, end_val, increment)

    while repeat:
        increment_loop(end_val, start_val, -increment)
        increment_loop(start_val, end_val, increment)

    while True: #wait for interrupt
        pass

try:
    main()
finally: # clean up by removing file
    os.remove(fileName)
