#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h> 

#define TABLE_SIZE 101 
#define NAME_LENGTH 50
#define PHONE_LENGTH 15

typedef struct Contact {
    char name[NAME_LENGTH];
    char phone[PHONE_LENGTH];
    struct Contact* next;
} Contact;

Contact* hashTable[TABLE_SIZE];

double totalInsertTime = 0.0;
double totalSearchTime = 0.0;
int insertCount = 0;
int searchCount = 0;

unsigned int hashFunction(const char* name) {
    unsigned int hash = 0;
    while (*name) {
        hash = (hash * 31) + *name++;
    }
    return hash % TABLE_SIZE;
}

Contact* createContact(const char* name, const char* phone) {
    Contact* newContact = (Contact*)malloc(sizeof(Contact));
    if (!newContact) {
        printf("Error: Memory allocation failed.\n");
        exit(1);
    }
    strncpy(newContact->name, name, NAME_LENGTH);
    strncpy(newContact->phone, phone, PHONE_LENGTH);
    newContact->next = NULL;
    return newContact;
}

void addContact() {
    char name[NAME_LENGTH], phone[PHONE_LENGTH];
    printf("Enter name: ");
    scanf(" %[^\n]", name);
    printf("Enter phone: ");
    scanf(" %[^\n]", phone);

    unsigned int index = hashFunction(name);

    clock_t start = clock();

    Contact* current = hashTable[index];
    while (current) {
        if (strcmp(current->name, name) == 0) {
            printf("Error: Duplicate name detected.\n");
            return;
        }
        current = current->next;
    }

    Contact* newContact = createContact(name, phone);
    newContact->next = hashTable[index];
    hashTable[index] = newContact;

    clock_t end = clock();
    double elapsedTime = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
    totalInsertTime += elapsedTime;
    insertCount++;

    printf("Contact added successfully. Time taken: %.3f ms\n", elapsedTime);
}

int caseInsensitiveCompare(const char* str1, const char* str2) {
    while (*str1 && *str2) {
        if (tolower(*str1) != tolower(*str2)) {
            return 0;
        }
        str1++;
        str2++;
    }
    return *str1 == '\0' && *str2 == '\0';
}

void searchContact() {
    char name[NAME_LENGTH];
    printf("Enter the name to search: ");
    scanf(" %[^\n]", name);

    int found = 0;
    clock_t start = clock();

    printf("\n--- Search Results ---\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        Contact* current = hashTable[i];
        while (current) {
            if (caseInsensitiveCompare(current->name, name)) {
                printf("Name: %s, Phone: %s\n", current->name, current->phone);
                found = 1;
            }
            current = current->next;
        }
    }

    clock_t end = clock();
    double elapsedTime = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
    totalSearchTime += elapsedTime;
    searchCount++;

    if (!found) {
        printf("No contacts found matching '%s'.\n", name);
    }

    printf("Search completed in %.3f ms\n", elapsedTime);
}

void displayAverageTimes() {
    printf("\n--- Performance Metrics ---\n");
    if (insertCount > 0) {
        printf("Average Insert Time: %.3f ms\n", totalInsertTime / insertCount);
    } else {
        printf("Average Insert Time: No insert operations performed.\n");
    }
    if (searchCount > 0) {
        printf("Average Search Time: %.3f ms\n", totalSearchTime / searchCount);
    } else {
        printf("Average Search Time: No search operations performed.\n");
    }
}

void removeContact() {
    char name[NAME_LENGTH];
    printf("Enter the name to remove: ");
    scanf(" %[^\n]", name);

    unsigned int index = hashFunction(name);
    Contact* current = hashTable[index];
    Contact* prev = NULL;

    while (current) {
        if (strcmp(current->name, name) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                hashTable[index] = current->next;
            }
            free(current);
            printf("Contact removed successfully.\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Error: Contact not found.\n");
}

void displayContacts() {
    int empty = 1;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Contact* current = hashTable[i];
        while (current) {
            printf("Name: %s, Phone: %s\n", current->name, current->phone);
            current = current->next;
            empty = 0;
        }
    }
    if (empty) {
        printf("No contacts to display.\n");
    }
}

void freeMemory() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Contact* current = hashTable[i];
        while (current) {
            Contact* temp = current;
            current = current->next;
            free(temp);
        }
        hashTable[i] = NULL;
    }
}

int main() {
    int choice;

    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }

do {
        printf("\n--- Contact Manager ---\n");
        printf("1 - Add Contact\n");
        printf("2 - Search Contact by Name\n");
        printf("3 - Remove Contact\n");
        printf("4 - Display All Contacts\n");
        printf("5 - Display Average Times\n");
        printf("0 - Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Error: Invalid input. Please enter a number.\n");

            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                searchContact();
                break;
            case 3:
                removeContact();
                break;
            case 4:
                displayContacts();
                break;
            case 5:
                displayAverageTimes();
                break;
            case 0:
                printf("Exiting program.\n");
                freeMemory();
                break;
            default:
                printf("Error: Invalid choice.\n");
        }
    } while (choice != 0);

    return 0;
}
