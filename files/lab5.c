#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int trainNumber;
    char destination[50];
    int departureHour;
    int departureMinute;
    int arrivalHour;
    int arrivalMinute;
    char circulationDays[20];
} Train;

void createFile(char *filename);
void enterTrainData(FILE *file);
void displayTrainData(char *filename);
void separateTrainData(char *filename);
void mergeFiles(char *resultFilename, char *file1, char *file2, char *file3);

int main() {
    char filename[] = "experiment.txt";
    createFile(filename);
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    } else {
        printf("File created and opened!\n");
    }

    int numTrains;
    printf("Enter the number of trains you want to enter: ");
    scanf("%d", &numTrains);

    for (int i = 0; i < numTrains; i++) {
        printf("\nEnter details for Train %d:\n", i + 1);
        enterTrainData(file);
    }

    fclose(file);

    printf("\nTrain data entered:\n");
    displayTrainData(filename);

    separateTrainData(filename);

    char resultFilename[] = "result.txt";
    mergeFiles(resultFilename, "otput_par.txt", "otput_impar.txt", "otput_daily.txt");

    return 0;
}

// Function to create a text file
void createFile(char *filename) {
    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        fclose(file);
        printf("File '%s' created.\n", filename);
    } else {
        printf("Error creating file '%s'.\n", filename);
    }
}

// Function to enter train data into the file
void enterTrainData(FILE *file) {
    Train train;

    printf("Train Number: ");
    scanf("%d", &train.trainNumber);
    printf("Destination: ");
    scanf("%s", train.destination);
    printf("Departure Time (HH MM): ");
    scanf("%d %d", &train.departureHour, &train.departureMinute);
    printf("Arrival Time (HH MM): ");
    scanf("%d %d", &train.arrivalHour, &train.arrivalMinute);
    printf("Days of Circulation (Daily/Odd/Even): ");
    scanf("%s", train.circulationDays);

    fprintf(file, "%d %s %02d:%02d %02d:%02d %s\n", train.trainNumber, train.destination,
            train.departureHour, train.departureMinute, train.arrivalHour, train.arrivalMinute,
            train.circulationDays);
}

// Function to display train data from the file
void displayTrainData(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        char line[100];
        while (fgets(line, sizeof(line), file) != NULL) {
            printf("%s", line);
        }
        fclose(file);
    } else {
        printf("Error opening file '%s' for reading.\n", filename);
    }
}

// Function to separate train data based on running days
void separateTrainData(char *filename) {
    FILE *file = fopen(filename, "r");
    FILE *filePar = fopen("otput_par.txt", "w");
    FILE *fileImpar = fopen("otput_impar.txt", "w");
    FILE *fileDaily = fopen("otput_daily.txt", "w");
    
    if (file != NULL && filePar != NULL && fileImpar != NULL && fileDaily != NULL) {
        char line[100];
        while (fgets(line, sizeof(line), file) != NULL) {
            Train train;
            sscanf(line, "%d %s %d:%d %d:%d %s", &train.trainNumber, train.destination,
                   &train.departureHour, &train.departureMinute, &train.arrivalHour, &train.arrivalMinute,
                   train.circulationDays);

            if (strcmp(train.circulationDays, "Daily") == 0) {
                fprintf(fileDaily, "%s", line);
            } else if (strcmp(train.circulationDays, "Odd") == 0) {
                fprintf(fileImpar, "%s", line);
            } else if (strcmp(train.circulationDays, "Even") == 0) {
                fprintf(filePar, "%s", line);
            }
        }
        fclose(file);
        fclose(filePar);
        fclose(fileImpar);
        fclose(fileDaily);
        printf("Train data separated and stored in different files.\n");
    } else {
        printf("Error opening files for writing.\n");
    }
}

// Function to merge output files into result.txt
void mergeFiles(char *resultFilename, char *file1, char *file2, char *file3) {
    FILE *resultFile = fopen(resultFilename, "w");
    if (resultFile != NULL) {
        FILE *file;
        char line[100];

        file = fopen(file1, "r");
        if (file != NULL) {
            while (fgets(line, sizeof(line), file) != NULL) {
                fprintf(resultFile, "%s", line);
            }
            fclose(file);
        }

        file = fopen(file2, "r");
        if (file != NULL) {
            while (fgets(line, sizeof(line), file) != NULL) {
                fprintf(resultFile, "%s", line);
            }
            fclose(file);
        }

        file = fopen(file3, "r");
        if (file != NULL) {
            while (fgets(line, sizeof(line), file) != NULL) {
                fprintf(resultFile, "%s", line);
            }
            fclose(file);
        }

        fclose(resultFile);
        printf("Output files merged into '%s'.\n", resultFilename);
    } else {
        printf("Error opening file '%s' for writing.\n", resultFilename);
    }
}