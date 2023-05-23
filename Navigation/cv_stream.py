import cv2
import socket
import threading
import queue
from time import sleep

# Set the IP camera URL
URL = "http://192.168.137.35:8000/stream.mjpg"


class Streamer:
    def __init__(self) -> None:
        self.msg_queue = queue.Queue()

    # This stream function takes in a url to perform streaming.
    # Please overload this function by your own image processing function.
    def stream(self, url):
        # Initialize counter for sending output
        i:int = 0

        # Open the video stream
        capture = cv2.VideoCapture(url)

        # Loop through the frames from the video stream
        while True:
            # Read a frame from the video stream
            ret, frame = capture.read()

            # Check if the frame was successfully captured
            if not ret:
                print("Error: Failed to capture frame")
                break

            # Display the frame
            cv2.imshow("IP Camera Stream", frame)

            if self.msg_queue.empty() == True:
                i = i+1
                self.msg_queue.put(i)

            # Exit if the 'q' key is pressed
            if cv2.waitKey(1) == ord('q'):
                break

        # Release the video stream and close all windows
        capture.release()
        cv2.destroyAllWindows()

    # This function creates a thread that handles streaming and sending
    # messages seperately. This is to avoid sending data to the slave
    # devices rapidly. Change the interval of data sending for optimum
    # performance.
    def run_stream(self, url: str, connection: socket.socket):
        thread_stream = threading.Thread(target=self.stream, args=(url,))
        thread_stream.start()
        while True:
            if self.msg_queue.empty() == False:
                message = self.msg_queue.get()
                connection.send(f"Received {message}".encode("utf-8"))
                sleep(2)

if __name__ == "__main__":
    streamer = MyCv("http://192.168.137.190:8080/stream")
    streamer.start()
