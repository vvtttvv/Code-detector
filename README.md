# Code-detector
I implemented a plagiarism checker program in C++ for the SDA course.

# Methods:
Cosine method:
This code performs plagiarism detection by comparing files. It starts by reading words from the files and creating arrays containing unique words and their frequencies. Then, the program calculates the cosine similarity between the frequency vectors of words, which allows determining the degree of similarity between the texts. If the similarity level between the files exceeds a certain threshold (in this case, 45 degrees), the program considers the files to be plagiarized.

Levenshtein distance
This code also performs plagiarism detection, but it uses the Levenshtein algorithm to estimate the distance between strings instead of cosine similarity. The program starts by reading text from a file, then compares each  file in the "files" directory with the original file using the Levenshtein algorithm. The comparison results are written to the "result.txt" file, indicating the similarity level in percentage and determining whether the file is plagiarized.

# Visualisation
This code represents a PyQt6-based graphical interface program that allows users to upload files for plagiarism detection and run two different methods of checking: cosine similarity and Levenshtein distance.
After the user selects files, they are copied to the "files" folder. The "Original file" button allows choosing an original file to compare with others. The "Levenshtein distance" and "Cosine method" buttons run the corresponding C++ programs that perform plagiarism detection. The results are displayed in the text field of the interface.
