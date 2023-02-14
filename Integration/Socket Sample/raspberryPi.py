import socket

PORT = 5050
SERVER = "127.0.1.1"
ADDR = (SERVER, PORT)
FORMAT = 'utf-8'

raspi= socket.socket(socket.AF_INET, socket.SOCK_STREAM)
raspi.connect(ADDR)
