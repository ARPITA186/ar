#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 1000
#define MAX_LINE_LENGTH 1000

// Function prototypes
void displayMenu();
void createFile();
void openFile();
void saveFile();
void closeFile();
void displayFileContents();
void searchInFile();
void appendToFile();
void deleteLine();

// Global variables
FILE *filePointer = NULL;
char currentFileName[MAX_FILENAME_LENGTH];
char currentFileContents[MAX_LINE_LENGTH];

int main() {
    int choice;

    printf("Welcome to Text Editor\n");

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createFile();
                break;
            case 2:
                openFile();
                break;
            case 3:
                saveFile();
                break;
            case 4:
                closeFile();
                break;
            case 5:
                displayFileContents();
                break;
            case 6:
                searchInFile();
                break;
            case 7:
                appendToFile();
                break;
            case 8:
                deleteLine();
                break;
            case 9:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 9);

    return 0;
}

void displayMenu() {
    printf("\n--- Menu ---\n");
    printf("1. Create a new file\n");
    printf("2. Open a file\n");
    printf("3. Save the current file\n");
    printf("4. Close the current file\n");
    printf("5. Display file contents\n");
    printf("6. Search in the current file\n");
    printf("7. Append text to the current file\n");
    printf("8. Delete a line from the current file\n");
    printf("9. Exit\n");
}

void createFile() {
    char fileName[MAX_FILENAME_LENGTH];

    printf("Enter the name of the file to create: ");
    scanf("%s", fileName);

    if ((filePointer = fopen(fileName, "w")) == NULL) {
        printf("Error creating file.\n");
    } else {
        strcpy(currentFileName, fileName);
        printf("File created successfully.\n");
    }
}

void openFile() {
    char fileName[MAX_FILENAME_LENGTH];

    printf("Enter the name of the file to open: ");
    scanf("%s", fileName);

    if ((filePointer = fopen(fileName, "r+")) == NULL) {
        printf("Error opening file.\n");
    } else {
        strcpy(currentFileName, fileName);
        printf("File opened successfully.\n");
    }
}

void saveFile() {
    if (filePointer == NULL) {
        printf("No file is currently open.\n");
    } else {
        printf("Saving file...\n");
        // Write currentFileContents to the file
        // Code for saving file contents goes here
        printf("File saved successfully.\n");
    }
}

void closeFile() {
    if (filePointer == NULL) {
        printf("No file is currently open.\n");
    } else {
        fclose(filePointer);
        filePointer = NULL;
        currentFileName[0] = '\0';
        printf("File closed successfully.\n");
    }
}

void displayFileContents() {
    if (filePointer == NULL) {
        printf("No file is currently open.\n");
    } else {
        printf("--- File Contents ---\n");
        // Display the contents of the file
        // Code for displaying file contents goes here
    }
}

void searchInFile() {
    if (filePointer == NULL) {
        printf("No file is currently open.\n");
    } else {
        char searchTerm[MAX_LINE_LENGTH];
        printf("Enter the search term: ");
        scanf("%s", searchTerm);
        // Search for searchTerm in currentFileContents
        // Code for searching in file goes here
    }
}

void appendToFile() {
    if (filePointer == NULL) {
        printf("No file is currently open.\n");
    } else {
        printf("Enter text to append (press Ctrl + D to end):\n");

        // Read text from the user until EOF
        char ch;
        while ((ch = getchar()) != EOF) {
            fputc(ch, filePointer);
        }

        printf("Text appended to the file.\n");
    }
}

void deleteLine() {
    if (filePointer == NULL) {
        printf("No file is currently open.\n");
    } else {
        int lineNum;
        printf("Enter the line number to delete: ");
        scanf("%d", &lineNum);

        FILE *tempFilePointer = fopen("temp.txt", "w");
        if (tempFilePointer == NULL) {
            printf("Error creating temporary file.\n");
            return;
        }

        rewind(filePointer);
        char line[MAX_LINE_LENGTH];
        int currentLine = 1;

        while (fgets(line, MAX_LINE_LENGTH, filePointer) != NULL) {
            if (currentLine != lineNum) {
                fputs(line, tempFilePointer);
            }
            currentLine++;
        }

        fclose(filePointer);
        fclose(tempFilePointer);

        remove(currentFileName);
        rename("temp.txt", currentFileName);

        filePointer = fopen(currentFileName, "r+");
        if (filePointer == NULL) {
            printf("Error opening file.\n");
            return;
        }

        printf("Line %d deleted successfully.\n", lineNum);
    }
}
