#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char name[35];
    double totalDuration;
} Attendee;

int compareUsers(const Attendee* a, const Attendee* b) {
    // Getting surnames as last word
    // to avoid getting middle names.
    char surnameFirst[30];
    char surnameSecond[30];
    getSurnameLastWord(a->name, surnameFirst);
    getSurnameLastWord(b->name, surnameSecond);

    // Comparing surnames without case sensitive
    int surnameCompare = strcasecmp(surnameFirst, surnameSecond);
    if (surnameCompare != 0) {
        return surnameCompare;
    }

    // Getting first and middle names from the names
    char firstAndMiddleNamesFirst[30];
    char firstAndMiddleNamesSecond[30];
    getFirstAndMiddleNames(a->name, firstAndMiddleNamesFirst);
    getFirstAndMiddleNames(b->name, firstAndMiddleNamesSecond);

    // Compare first and middle names without case sensitive
    return strcasecmp(firstAndMiddleNamesFirst, firstAndMiddleNamesSecond);
}

// since last word of names are surnames in txt file
void getSurnameLastWord(const char* str, char* lastWord) {
    int length = strlen(str);
    int index = length - 1;
    while (index >= 0 && str[index] != ' ') {
        index--;
    }
    strcpy(lastWord, &str[index + 1]);
}

// dividing name
void getFirstAndMiddleNames(const char* str, char* firstAndMiddleNames) {
    int length = strlen(str);
    int index = length - 1;
    while (index >= 0 && str[index] != ' ') {
        index--;
    }
    strncpy(firstAndMiddleNames, str, index);
    firstAndMiddleNames[index] = '\0';
}

// swap method to use for selection sort
void swapAttendees(Attendee* a, Attendee* b) {
    Attendee temp = *a;
    *a = *b;
    *b = temp;
}

// selection sort method to sort attendees
void selectionSort(Attendee* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (compareUsers(&arr[j], &arr[minIndex]) < 0) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swapAttendees(&arr[i], &arr[minIndex]);
        }
    }
}


int main() {
    char txtFileName[50];
    printf("Enter the input file name: ");
    scanf("%s", txtFileName);

    FILE* txtFile = fopen(txtFileName, "r");
    if (txtFile == NULL) {
        printf("Failed to open the input file.\n");
        return 1;
    }

    Attendee attendees[100];
    int numAttendees = 0;

    // to skip the first line
    char firstLine[200];
    fgets(firstLine, sizeof(firstLine), txtFile);

    // lines that contains attendees
    char lineofTxt[200];
    while (fgets(lineofTxt, sizeof(lineofTxt), txtFile) != NULL && numAttendees < 100) {
        char date[30];
        char name[50];
        double duration;

        // using %[^,] to reads characters until a comma (*) to skip over some input.
        sscanf(lineofTxt, "%[^,],%*[^,],%lf,%[^,],%*s", date, &duration, name);

        int duplicateCheckBoolean = 0;
        for (int i = 0; i < numAttendees; i++) {
            if (strcasecmp(attendees[i].name, name) == 0) {
                attendees[i].totalDuration += duration;
                duplicateCheckBoolean = 1;
                break;
            }
        }

        if (!duplicateCheckBoolean) {
            strcpy(attendees[numAttendees].name, name);
            attendees[numAttendees].totalDuration = duration;
            numAttendees++;
        }
    }

    fclose(txtFile);

    char userInput[3];
    printf("Sort the results? (yes/no): ");
    scanf("%s", userInput);

    if (strcmp(userInput, "yes") == 0) {
        selectionSort(attendees, numAttendees);
    }

    // printing
    for (int i = 0; i < numAttendees; i++) {
        char surname[50];
        getSurnameLastWord(attendees[i].name, surname);
        char firstAndMiddleNames[50];
        getFirstAndMiddleNames(attendees[i].name, firstAndMiddleNames);
        printf("%s %s %.2lf\n", surname, firstAndMiddleNames, attendees[i].totalDuration);
    }

    return 0;
}
