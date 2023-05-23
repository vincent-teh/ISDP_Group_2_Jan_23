# Pending create a proper way of stopping the connection.
# Pending create one button to stop all threads

from cv_stream import Streamer
from Socket import MySocket


PORT = 5050
# SERVER = socket.gethostbyname(socket.gethostname())
SERVER = "192.168.137.1"
ADDR = (SERVER, PORT)
FORMAT = 'utf-8'
URL = "http://192.168.137.190:8080/stream/video.mjpeg"

server = MySocket(ADDR, URL)
streamer = Streamer()
server.start(streamer)
