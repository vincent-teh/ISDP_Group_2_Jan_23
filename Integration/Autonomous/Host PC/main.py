import socket
import threading
from application import run_pyqt5, MyWindow

APPLICATION_NAME = "PyQT Demo"


PORT = 5050
# SERVER = socket.gethostbyname(socket.gethostname())
SERVER = "192.168.137.1"
ADDR = (SERVER, PORT)
FORMAT = "utf-8"

output_msg = ""

class main_window(MyWindow):
    def clicked_respond(self, num):
        output_msg = str(num).encode(FORMAT)

def handle_client(connection, address):
    print(f"[NEW CONNECTION] {address} connected")
    while True:
        input_msg = connection.recv(64).decode(FORMAT)
        if input_msg:
            print(f"[{address}] {input_msg}")
        if output_msg:
            connection.send(output_msg)
            print(f"[Singal sent] number {output_msg}")
            output_msg = ""

def start():
    host_pc.listen()
    while True:
        connection, address = host_pc.accept()
        thread = threading.Thread(target=handle_client, args=(connection, address))
        thread.start()
        print(f"[ACTIVE CONNECTION] {threading.active_count() - 1}")

host_pc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host_pc.bind(ADDR)
print(f"[START] Server listening on {ADDR}")

if __name__ == "__main__":
    run_pyqt5("Autonomous navigation", main_window)
