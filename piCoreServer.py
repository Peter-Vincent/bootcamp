# Code to fun the core server on the Pi handling all other activities

import sys
import time 
import zmq
import socket
import serial
from itertools import cycle


if len(sys.argv) < 2:
    raise RuntimeError("2 arguments required - socket number , serial port")
socket_num  = int(sys.argv[1])
serial_port = sys.argv[2]
print(sys.argv)
ser = serial.Serial(serial_port)

c_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
c_server.connect(("localhost",socket_num))
c_server.settimeout(0.25)
live = True

velocity = 0
states = cycle(("tra","direct"))
cur_state = next(states)
print(cur_state)
serial_command = ''
timeout = 0
data = b'e'
data_parse = data.decode("utf-8")
while live:
    try:
        data = c_server.recv(256)
        timeout = 0
        data = data[:1]
        data_parse = data.decode("utf-8")
        print('Recieved ' + data_parse + '\n')
    except socket.timeout as e:
        err = e.args[0]
        if err == 'timed out':
            timeout += 1
            if timeout == 4:
                data = b'e'
                data = data[:1]
                data_parse = data.decode("utf-8")
                print('Recieved ' + data_parse + '\n')
        else:
            print(e)
            live = False
            continue
    if "k" in data_parse: 
        live = False
        continue
    if "t" in data_parse:
        # Switch drive mode
        cur_state = next(states)
        print(cur_state)
        data_parse = ''
    # parse the data into commands for the arduino motor
    if cur_state is "direct":
        if "e" in data_parse:
            velocity = 0
            serial_command = 'l' + str(velocity)
        elif "w" in data_parse:
            velocity = velocity + 255
            serial_command = 'l' + str(velocity)
        elif "s" in data_parse:
            velocity = velocity - 255
            serial_command = 'l' + str(velocity)
        elif "a" in data_parse:
            serial_command = 'z0.2'
        elif "d" in data_parse:
            serial_command = 'x0.2'
    elif cur_state is "tra":
        if "w" in data_parse:
            velocity = velocity + 255
            serial_command = 'l' + str(velocity)
        elif "s" in data_parse:
            velocity = velocity - 255
            serial_command = 'l' + str(velocity)
        elif "a" in data_parse:
            serial_command = 'z0.2'
        elif "d" in data_parse:
            serial_command = 'x0.2'
    if velocity > 255:
        velocity = 255
    if velocity < -255:
        velocity = -255
    serial_command = (serial_command + '\n')
    ser.write(bytes(serial_command,"utf-8"))
c_server.close()
