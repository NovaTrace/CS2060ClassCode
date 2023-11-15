//Name: Quinn Hackenberg
//Class: CS2060 T/R 1:40PM - 2:55PM 
//Windows OS
//Description: Manipulating strings and ints in a linked list to create a memory controlled list of pets

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define STRING_LENGTH 80

typedef struct pet {
	int age;
	char name[STRING_LENGTH];
}Pet;

typedef struct node {
	Pet data;
	struct node *nextPtr;
}Node;

// Function prototypes
int stringCompare(Pet *pet1, Pet *pet2);
void insertPets(Node** headPtr);
void displayPets(Node* head);
void writeToFile(Node* head);
void removePets(Node* head);
void removeAllPets(Node* head);

int main(void) {

	Node* head = malloc(sizeof(Node));
	Node** headPtr = &head;

	insertPets(headPtr);

	displayPets(head);

	writeToFile(head);

	removePets(head);

	removeAllPets(head);

	displayPets(head);
}

int stringCompare(Pet *pet1, Pet *pet2) {

	char tempChar1[STRING_LENGTH];
	char tempChar2[STRING_LENGTH];

	strcpy(tempChar1, pet1->name);
	strcpy(tempChar2, pet2->name);

	for (int i = 0; i < STRING_LENGTH; i++) {

		tempChar1[i] = tolower(tempChar1[i]);
		tempChar2[i] = tolower(tempChar2[i]);
	}

	return strcmp(tempChar1, tempChar2);
}

//Should be 2 functions not 1
void insertPets(Node** headPtr) {

	Node* currentPtr = *headPtr;
	Pet *pet = malloc(sizeof(Pet));

	currentPtr->data = *pet;
	puts("Enter name:");
	fgets(&pet->name, STRING_LENGTH, stdin);

	puts("Enter age:");
	scanf("%d", &pet->age);

	char addingPets = 'y';

	puts("");
	puts("Do you want to add another pet? Please enter (y)es or (n)o:");
	scanf(" %c", &addingPets);

	while (addingPets == 'y') {

		Pet* newPet = malloc(sizeof(Pet));
		puts("Enter name:");
		fgets(&newPet->name, STRING_LENGTH, stdin);

		puts("Enter age:");
		scanf("%d", &newPet->age);
		
		Node *newNode = malloc(sizeof(Node));
		newNode->data = *newPet;

		bool insert = false;
		Node* currentNode = head;
		Node* previousNode = NULL;
		while (!insert) {

			if ((stringCompare(&currentNode->data, &newNode->data) > 0 )||(currentNode = NULL)) {

				newNode->nextPtr = &currentNode;
				insert = true;

				if (previousNode != NULL) {

					previousNode->nextPtr = &newNode;
				}
			}

			else {

				previousNode = currentNode;
				currentNode = currentNode->nextPtr;
			}
		}

		puts("");
		puts("Do you want to add another pet? Please enter (y)es or (n)o:");
		scanf(" %c", &addingPets);
	}
}

void displayPets(Node* head) {

	Node *currentNode = &head;
	puts("The names in alphebetical order:");
	if (head != NULL) {

		do {

			Pet* currentPet = &currentNode->data;
			printf("%s is %d years old\n", &currentPet->name, &currentPet->age);
		} while (currentNode->nextPtr != NULL);
	}

	else {

		puts("There aren't any names in the list.");
	}
}

void writeToFile(Node* head) {

	FILE* filePtr;
	filePtr = fopen("pets.txt", "w");

	Node* currentNode = &head;
	do {

		Pet* currentPet = &currentNode->data;
		printf("%s is %d years old\n", &currentPet->name, &currentPet->age);
	} while (currentNode->nextPtr != NULL);
}

void removePets(Node* head) {

	char removingPets = "y";
	puts("");
	puts("Do you want to remove a pet? Please enter (y)es or (n)o:");
	fgets(removingPets, 1, stdin);

	while (removingPets == ("y"||"Y")) {

		Pet *removePet = NULL;
		puts("Enter name of pet to be removed:");
		fgets(&removePet->name, STRING_LENGTH, stdin);

		Node* currentNode = &head;
		Node* previousNode = NULL;
		bool petRemoved = false;
		do {

			if (stringCompare(currentNode, removePet) == 0) {

				if (previousNode != NULL) {

					previousNode->nextPtr = currentNode->nextPtr;
					free(currentNode);
					petRemoved = true;
				}
			}

			else {

				previousNode = currentNode;
				currentNode = currentNode->nextPtr;
			}
		}while ((currentNode->nextPtr != NULL) && (petRemoved = false));

		if (!petRemoved) {

			printf("\n%s is not found in the list", &removePet->name);
		}

		puts("");
		puts("Do you want to remove another pet? Please enter (y)es or (n)o:");
		fgets(removingPets, 1, stdin);
	}
}

void removeAllPets(Node* head) {

	puts("Removing all pets from memory...");
	Node* currentNode = &head;
	Node* nextNode = NULL;
	head = NULL;
	do {

		nextNode = currentNode->nextPtr;
		free(currentNode);
		currentNode = nextNode;
		
	} while (currentNode->nextPtr != NULL);
	free(currentNode);
}

//using malloc or by directly creating a Pet variable.
// Difference between dynamic allocation and alternative?