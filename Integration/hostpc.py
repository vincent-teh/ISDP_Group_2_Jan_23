import socket
import threading


PORT = 5050
SERVER = socket.gethostbyname(socket.gethostname())
ADDR = (SERVER, PORT)
FORMAT = 'utf-8'

host_pc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host_pc.bind(ADDR)

def handle_client(connection, address):
    print(f"[NEW CONNECTION] {address} connected")
    while True:
        msg = connection.recv(64).decode(FORMAT)
        if msg:
            print(f"[{address}] {msg}")

def start():
    host_pc.listen()
    while True:
        connection, address = host_pc.accept()
        thread = threading.Thread(target=handle_client, args=(connection, address))
        thread.start()
        print(f"[ACTIVE CONNECTION] {threading.active_count() - 1}")

print(f"[START] Server listening on {ADDR}")
start()
