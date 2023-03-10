from abc import ABC, abstractmethod
from functools import partial
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
import sys

class MyWindow(QWidget):
    def __init__(self, application_name):
        super(MyWindow, self).__init__()
        self.InitUI(application_name)

    def InitUI(self, application_name, *args):
        self.setWindowTitle(application_name)
        self.hbox = QHBoxLayout()
        self.push_buttons = []
        for i in range(5):
            self.push_buttons.append(QPushButton(self))
            if i == 0:
                self.push_buttons[i].setText("Turn left")
            if i == 1:
                self.push_buttons[i].setText("Forward")
            if i == 2:
                self.push_buttons[i].setText("Stop")
            if i == 3:
                self.push_buttons[i].setText("Backward")
            if i == 4:
                self.push_buttons[i].setText("Turn right")
            self.push_buttons[i].clicked.connect(partial(self.clicked_respond, i, *args))
            self.hbox.addWidget(self.push_buttons[i])
        self.setLayout(self.hbox)

    # Please implement this function in another file
    def clicked_respond(self, num):
        print(num)


def run_pyqt5(application_name, window, *argv):
    app = QApplication(sys.argv)
    win = window(application_name, *argv)
    win.show()
    sys.exit(app.exec_())

if __name__ == "__main__":
    run_pyqt5("Hello world", MyWindow)
