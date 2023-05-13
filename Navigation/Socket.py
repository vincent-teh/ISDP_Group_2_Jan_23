# Pending to add disconnected warning to make the code robust

import socket
from cv_stream import Streamer


class MySocket:
    def __init__(self, addr, vid_url) -> None:
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.bind(addr)
        self.url = vid_url

    def start(self, streamer: Streamer) -> None:
        self.server.listen()
        connection, address = self.server.accept()
        streamer.run_stream(self.url, connection)
