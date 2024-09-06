import sys
from PyQt6.QtWidgets import QApplication, QWidget

class MainApp(QWidget):
    def __init__(self):
        super(MainApp, self).__init__()

if __name__=="__main__":
    app = QApplication(sys.argv)