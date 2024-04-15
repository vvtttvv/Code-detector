import sys
import os
import shutil
import subprocess
from PyQt6.QtCore import QSize, Qt
from PyQt6.QtGui import QColor
from PyQt6.QtWidgets import QApplication, QMainWindow, QPushButton, QVBoxLayout, QWidget, QFileDialog, QHBoxLayout, QTextEdit


class RoundedButton(QPushButton):
    def __init__(self, text):
        super().__init__(text)
        self.setFixedSize(120, 40)
        self.setStyleSheet(
            "QPushButton {"
            "   background-color: #F5F5DC;" 
            "   color: #444444;"  
            "   border: 2px solid #FFFFFF;"
            "   border-radius: 20px;" 
            "}"
            "QPushButton:hover {"
            "   background-color: #DDDDDD;" 
            "}"
        )
        self.setCursor(Qt.CursorShape.PointingHandCursor)


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("My App")

        upload_button = RoundedButton("Upload files")
        upload_button.clicked.connect(self.open_file_dialog)

        original_file_button = RoundedButton("Original file")
        original_file_button.clicked.connect(self.create_original_folder)

        lev_button = RoundedButton("Levenshtein distance")
        lev_button.clicked.connect(self.run_lev_program)

        cos_button = RoundedButton("Cosine method")
        cos_button.clicked.connect(self.run_cos_program)

        button_layout = QVBoxLayout()
        button_layout.addWidget(upload_button)
        button_layout.addWidget(original_file_button)
        button_layout.addWidget(lev_button)
        button_layout.addWidget(cos_button)

        button_widget = QWidget()
        button_widget.setLayout(button_layout)

        self.result_text_edit = QTextEdit()
        self.result_text_edit.setReadOnly(True)
        self.result_text_edit.setStyleSheet(
            "background-color: #F5F5DC;"
            "color: #000000;"  
        )

        main_layout = QHBoxLayout()
        main_layout.addWidget(button_widget)
        main_layout.addWidget(self.result_text_edit)

        main_widget = QWidget()
        main_widget.setLayout(main_layout)

        self.setCentralWidget(main_widget)

        self.resize(QSize(800, 600))

        self.setStyleSheet("background-color: #333333;")


    def open_file_dialog(self):
        file_dialog = QFileDialog(self)
        file_dialog.setFileMode(QFileDialog.FileMode.ExistingFiles)
        file_dialog.setNameFilter("All Files (*)")

        if file_dialog.exec():
            selected_files = file_dialog.selectedFiles()
            print("Selected files:", selected_files)
            for file_path in selected_files:
                file_name = os.path.basename(file_path)
                destination_path = os.path.join(os.getcwd(), "files", file_name)
                shutil.copy(file_path, destination_path)
                print(f"Copied {file_name} to 'files' folder.")


    def create_original_folder(self):
        original_folder_path = os.path.join(os.getcwd(), "original_file")
        if not os.path.exists(original_folder_path):
            os.makedirs(original_folder_path)
            print("Created 'original_file' folder.")

        file_dialog = QFileDialog(self)
        file_dialog.setFileMode(QFileDialog.FileMode.ExistingFiles)
        file_dialog.setNameFilter("All Files (*)")

        if file_dialog.exec():
            selected_files = file_dialog.selectedFiles()
            print("Selected files:", selected_files)
            for file_path in selected_files:
                file_name = os.path.basename(file_path)
                destination_path = os.path.join(original_folder_path, file_name)
                shutil.copy(file_path, destination_path)
                print(f"Copied {file_name} to 'original_file' folder.")


    def run_lev_program(self):
        lev_program_path = os.path.join(os.getcwd(), "lev.cpp")
        
        if not os.path.exists(lev_program_path):
            print("Error: lev.cpp not found.")
            return

        try:
            subprocess.run(["g++", "-o", "lev", "lev.cpp"], check=True)
            subprocess.run(["./lev"], check=True)
        except subprocess.CalledProcessError as e:
            print("Error:", e)

        result_file_path = os.path.join(os.getcwd(), "result", "result.txt")
        if os.path.exists(result_file_path):
            with open(result_file_path, "r") as file:
                result_text = file.read()
                self.result_text_edit.setPlainText(result_text)
        else:
            self.result_text_edit.setPlainText("Result file not found.")


    def run_cos_program(self):
        cos_program_path = os.path.join(os.getcwd(), "cos.cpp")
        
        if not os.path.exists(cos_program_path):
            print("Error: cos.cpp not found.")
            return

        try:
            subprocess.run(["g++", "-o", "cos", "cos.cpp"], check=True)
            subprocess.run(["./cos"], check=True)
        except subprocess.CalledProcessError as e:
            print("Error:", e)

        result_file_path = os.path.join(os.getcwd(), "result", "result.txt")
        if os.path.exists(result_file_path):
            with open(result_file_path, "r") as file:
                result_text = file.read()
                self.result_text_edit.setPlainText(result_text)
        else:
            self.result_text_edit.setPlainText("Result file not found.")


if __name__ == "__main__":
    if not os.path.exists("files"):
        os.makedirs("files")

    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())
