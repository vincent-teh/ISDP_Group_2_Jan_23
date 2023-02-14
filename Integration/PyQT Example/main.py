from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton
import sys

APPLICATION_NAME = "PyQT Demo"

class MyWindow(QMainWindow):
	def __init__(self):
		super(MyWindow, self).__init__()
		self.setGeometry(200, 200, 300, 300)
		self.setWindowTitle(APPLICATION_NAME)
		self.initUI()

	def initUI(self):
		self.button = QPushButton(self)
		self.button.setText("Click me")
		self.button.clicked.connect(self.clicked)

	def clicked(self):
		print("Button 1 pressed")


if __name__ == "__main__":
	app = QApplication(sys.argv)
	win = MyWindow()
	win.show()
	sys.exit(app.exec_())