#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Bicycle {
    int number;
    bool isAvailable;
    int studentID;
    struct Bicycle* next;
} Bicycle;


Bicycle* initializeBicycles(int count);
Bicycle* addBicycle(Bicycle* list);
Bicycle* deleteBicycle(Bicycle* list, int bicycleNumber);
void displayRiderInfo(Bicycle* list, int bicycleNumber);
void checkoutBicycle(Bicycle* list, int studentID, char section);
void checkinBicycle(Bicycle* head, int bicycleNumber);
void displayBicycleInfo(Bicycle* head);
void userMenu(Bicycle* bicycleList);
void adminMenu(Bicycle** bicycleList);
void printWelcomeMessage();
void printUserTypeMenu();
void printInvalidUserType();
void printExitMessage();
int getUserType();

int main() {
    int totalBicycles = 50;
    Bicycle* bicycleList = initializeBicycles(totalBicycles);

    printWelcomeMessage();

    int userType;
    printUserTypeMenu();
    userType = getUserType();

    switch (userType) {
        case 1:
            userMenu(bicycleList);
            break;
        case 2:
            adminMenu(&bicycleList);
            break;
        default:
            printInvalidUserType();
            break;
    }

    printExitMessage();

    return 0;
}

Bicycle* initializeBicycles(int count) {
    Bicycle* head = NULL;
    Bicycle* current = NULL;

    for (int i = 1; i <= count; i++) {
        Bicycle* newBike = (Bicycle*)malloc(sizeof(Bicycle));
        newBike->number = i;
        newBike->isAvailable = true;
        newBike->studentID = 0;
        newBike->next = NULL;

        if (head == NULL) {
            head = newBike;
            current = newBike;
        } else {
            current->next = newBike;
            current = newBike;
        }
    }

    return head;
}

Bicycle* addBicycle(Bicycle* list) {
    Bicycle* newBike = (Bicycle*)malloc(sizeof(Bicycle));
    newBike->number = list->number + 50;
    newBike->isAvailable = true;
    newBike->studentID = 0;
    newBike->next = NULL;

    if (list == NULL) {

        printf("\nBicycle %d has been added.\n", newBike->number);
        return newBike;
    }


    Bicycle* current = list;
    while (current->next != NULL) {
        current = current->next;
    }

    // Add the new bicycle at the end
    current->next = newBike;

    printf("\nBicycle %d has been added.\n", newBike->number);

    return list;
}

Bicycle* deleteBicycle(Bicycle* list, int bicycleNumber) {
    Bicycle* current = list;
    Bicycle* prev = NULL;

    while (current != NULL) {
        if (current->number == bicycleNumber) {
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                list = current->next;
            }

            free(current);
            printf("\nBicycle %d has been removed for servicing.\n", bicycleNumber);
            return list;
        }
        prev = current;
        current = current->next;
    }

    printf("\nBicycle %d not found.\n", bicycleNumber);
    return list;
}

void displayRiderInfo(Bicycle* list, int bicycleNumber) {
    Bicycle* current = list;

    while (current != NULL) {
        if (current->number == bicycleNumber) {
            if (current->isAvailable) {
                printf("\nBicycle %d is available.\n\n\n", bicycleNumber);
            } else {
                printf("\nBicycle %d is ridden by Student %d.\n\n\n", bicycleNumber, current->studentID);
            }
            return;
        }
        current = current->next;
    }

    printf("\nBicycle %d not found.\n\n", bicycleNumber);
}

void checkoutBicycle(Bicycle* list, int studentID, char section) {
    Bicycle* current = list;

    while (current != NULL) {
        if (current->isAvailable) {
            current->isAvailable = false;
            current->studentID = studentID;
            printf("\nStudent %d in Section %c checked out Bicycle %d.\n\n", studentID, section, current->number);
            return;
        }
        current = current->next;
    }
}

void checkinBicycle(Bicycle* head, int bicycleNumber) {
    Bicycle* current = head;
    while (current != NULL) {
        if (current->number == bicycleNumber) {
            if (current->isAvailable) {
                printf("\nBicycle %d is already checked in.\n\n", bicycleNumber);
            } else {
                current->isAvailable = true;
                current->studentID = 0;
                printf("\nBicycle %d has been checked in.\n\n", bicycleNumber);
            }
            return;
        }
        current = current->next;
    }
    printf("\nInvalid bicycle number.\n");
}

void displayBicycleInfo(Bicycle* head) {
    printf("\nBicycle Information:\n");
    printf("+----------------------+----------------------+-----------------------+\n");
    printf("| %-20s | %-20s | %-21s |\n", "Bicycle Number", "Availability", "Student ID");
    printf("+----------------------+----------------------+-----------------------+\n");

    for (Bicycle* current = head; current != NULL; current = current->next) {
        printf("| %-20d | %-20s |", current->number, (current->isAvailable ? "Available" : "Rented"));

        if (!current->isAvailable) {
            printf(" %-21d |\n", current->studentID);
        } else {
            printf(" %-21s |\n", "-");
        }
    }

    printf("+----------------------+----------------------+-----------------------+\n");
}

void userMenu(Bicycle* bicycleList) {
    int studentID;
    char section;
    int choice, bicycleNumber;

    printf("\nWelcome, User!\n");

    while (1) {
        printf("********************************\n");
        printf("1. Check Out Bicycle\n");
        printf("2. Check In Bicycle\n");
        printf("3. Show Available Bicycles\n");
        printf("4. Quit\n");
        printf("********************************\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEnter student ID: ");
                scanf("%d", &studentID);
                printf("Enter your Section: ");
                scanf(" %c", &section);
                checkoutBicycle(bicycleList, studentID, section);
                break;
            case 2:
                printf("\nEnter bicycle number to check in: ");
                scanf("%d", &bicycleNumber);
                checkinBicycle(bicycleList, bicycleNumber);
                break;
            case 3:
                printf("\nAvailable Bicycles: ");
                for (Bicycle* current = bicycleList; current != NULL; current = current->next) {
                    if (current->isAvailable) {
                        printf("%d ", current->number);
                    }
                }
                printf("\n");
                break;
            case 4:
                printf("\nExit from the program.\n");
                exit(0);
            default:
                printf("\nInvalid choice!! Try again.\n");
        }

        displayBicycleInfo(bicycleList);
    }
}

void adminMenu(Bicycle** bicycleList) {
    int adminChoice;
    int bicycleNumber;

    printf("\nWelcome, Admin!\n");

    while (1) {
        printf("********************************\n");
        printf("1. Add Bicycle\n");
        printf("2. Remove Bicycle\n");
        printf("3. Display Rider Info\n");
        printf("4. Show Available Bicycles\n");
        printf("5. Quit\n");
        printf("********************************\n");
        printf("Enter your choice: ");
        scanf("%d", &adminChoice);

        switch (adminChoice) {
            case 1:
                *bicycleList = addBicycle(*bicycleList);
                break;
            case 2:
                printf("\nEnter bicycle number to delete: ");
                scanf("%d", &bicycleNumber);
                *bicycleList = deleteBicycle(*bicycleList, bicycleNumber);
                break;
            case 3:
                printf("\nEnter bicycle number: ");
                scanf("%d", &bicycleNumber);
                displayRiderInfo(*bicycleList, bicycleNumber);
                break;
            case 4:
                printf("\nAvailable Bicycles: ");
                for (Bicycle* current = *bicycleList; current != NULL; current = current->next) {
                    if (current->isAvailable) {
                        printf("%d ", current->number);
                    }
                }
                printf("\n");
                break;
            case 5:
                printf("\nExit from the program.\n");
                exit(0);
            default:
                printf("\nInvalid choice!! Try again.\n");
        }
    }
}

void printWelcomeMessage() {
    printf("\n******************************************\n");
    printf("*     Welcome to DIU Bicycle Club!      *\n");
    printf("******************************************\n");
}

void printUserTypeMenu() {
    printf("\n******************************************\n");
    printf("*             User Type Menu             *\n");
    printf("******************************************\n");
    printf("Please choose your user type:\n");
    printf("1. Regular User\n");
    printf("2. Administrator\n");
    printf("Enter the number corresponding to your choice: ");
}

void printInvalidUserType() {
    printf("\nInvalid user type. Please choose 1 or 2.\n");
}

void printExitMessage() {
    printf("\nExiting from the program. Goodbye!\n");
}

int getUserType() {
    int userType;
    scanf("%d", &userType);
    return userType;
}

