from application import run_pyqt5, MyWindow
import socket
import threading
import queue

APPLICATION_NAME = "PyQT Demo"

is_debug = True


PORT = 5050
# SERVER = socket.gethostbyname(socket.gethostname())
SERVER = "192.168.137.1"
ADDR = (SERVER, PORT)
FORMAT = "utf-8"

output_msg_queue = queue.Queue()

host_pc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host_pc.bind(ADDR)
print(f"[START] Server listening on {ADDR}")


class main_window(MyWindow):
    def __init__(self, application_name, out_msg_queue):
        super(MyWindow, self).__init__()
        self.InitUI(application_name, out_msg_queue)

    def clicked_respond(self, num, out_msg_queue):
            output_msg = str(num)
            out_msg_queue.put(output_msg)

def handle_client(connection, address, msg_queue):
    print(f"[NEW CONNECTION] {address} connected")
    recv_thread = threading.Thread(target=RecvData, args=connection)
    recv_thread.start()

    # This original handle client thread will handle sending msg
    while True:
        if not output_msg_queue.empty():
            output_msg = output_msg_queue.get()
            SendData(connection, output_msg)

def start(output_msg_queue):
    host_pc.listen()
    while True:
        connection, address = host_pc.accept()
        thread = threading.Thread(target=handle_client, args=(connection, address, output_msg_queue))
        thread.start()
        print(f"[ACTIVE CONNECTION] {threading.active_count() - 1}")

def RecvData(connection):
    while True:
        input_msg = connection.recv(64).decode(FORMAT)
        print(input_msg)

def SendData(connection, msg_to_send):
    connection.send(msg_to_send.encode(FORMAT))
    print(f"[Singal sent] {msg_to_send}")

if __name__ == "__main__":
    pyqt5_thread = threading.Thread(target=run_pyqt5, args=("Autonomous navigation", main_window, output_msg_queue))
    pyqt5_thread.start()
    start(output_msg_queue)
