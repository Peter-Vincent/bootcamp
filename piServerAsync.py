# Peter Vincent
# Version of the core python server running with async routines


import sys
import time 
import zmq
import socket
import serial
import asyncio
from itertools import cycle

if len(sys.argv) < 2:
    raise RuntimeError("2 arguments required - socket number and serial port")
socket_num  = int(sys.argv[1])
serial_port = sys.argv[2]
print(sys.argv)
ser = serial.Serial(serial_port)
message = ''
async def tcp_echo_client(message,):
    reader, writer = await asyncio.open_connection('localhost',socket_num)

    data = await reader.read(255)
    print(f'Received: {data.decode()!r}')
    message = data.decode("utf-8")

    if 'k' in message:
        writer.close()

asyncio.run(tcp_echo_client(message))

print("program doesn't halt")