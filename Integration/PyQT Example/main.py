import cv2
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
import sys

APPLICATION_NAME = "PyQT Demo"

class MyWindow(QWidget):
    def __init__(self):
        super(MyWindow, self).__init__()
        # self.setGeometry(200, 200, 300, 300)
        self.setWindowTitle(APPLICATION_NAME)

        self.hbox = QVBoxLayout()

        self.video_frame = QLabel()
        self.hbox.addWidget(self.video_frame)

        self.b1 = QPushButton(self)
        self.b1.setText("Click me")
        self.b1.clicked.connect(self.clicked)
        self.hbox.addWidget(self.b1)

        self.video_thread = WorkerThread()
        self.video_thread.start()
        self.video_thread.ImageUpdate.connect(self.ImageUpdateSlot)

        self.setLayout(self.hbox)

    def clicked(self):
        print("Button 1 pressed")
        self.video_thread.stop()

    def ImageUpdateSlot(self, Image):
        self.video_frame.setPixmap(QPixmap.fromImage(Image))


class WorkerThread(QThread):
    ImageUpdate = pyqtSignal(QImage)
    def run(self):
        self.ThreadActive = True
        # Source of the video, change what Capture is equal to.
        Capture = cv2.VideoCapture(0)
        while self.ThreadActive:
            ret, frame = Capture.read()
            if ret:
                Image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
                FlippedImage = cv2.flip(Image, 1)
                ConvertToQtFormat = QImage(FlippedImage.data,
                                           FlippedImage.shape[1],
                                           FlippedImage.shape[0],
                                           QImage.Format_RGB888)
                Pic = ConvertToQtFormat.scaled(640, 480, Qt.KeepAspectRatio)
                self.ImageUpdate.emit(Pic)

    def stop(self):
        self.ThreadActive = False
        self.quit()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = MyWindow()
    win.show()
    sys.exit(app.exec_())