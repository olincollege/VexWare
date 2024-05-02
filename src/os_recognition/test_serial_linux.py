## Python script to send serial signals from linux to Arduino

import serial
from time import sleep

serial_port = '/dev/ttyACM0' # Arduino binds to ACM0 port by default
baud_rate = 9600

sleep(5) # delay so Arduino can start reading Serial

# Open serial port
ser = serial.Serial(serial_port, baud_rate, timeout=1)

test_string = "Linux\n"

running = True

while running:
    ser.write(test_string.encode())
    sleep(0.1) # add 100ms delay
# attempt to open several serial ports on computer
# write over serial to arduino several times, then move to next port
# if arduino reads, turn on LED
