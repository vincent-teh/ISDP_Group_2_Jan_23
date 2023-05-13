# Simple client code for receiving data
# Pending to integrate with Arduino Car
import socket

PORT = 5050
SERVER = "192.168.137.1"
ADDR = (SERVER, PORT)
FORMAT = 'utf-8'

raspi = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
raspi.connect(ADDR)
while True:
    message = raspi.recv(1024).decode(FORMAT)
    print(message)
