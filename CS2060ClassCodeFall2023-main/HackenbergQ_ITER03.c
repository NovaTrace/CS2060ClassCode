//Name: Quinn Hackenberg
//Class: CS2060 T/R 1:40PM - 2:55PM 
//Windows OS
//Description: Rental property interface for owners and renters. Includes an owner sign in, property set-up, 
//limited user rentals, user ratings and password protected program exit with data summery

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Maximum length of a string
#define STRING_LENGTH 80
// Two dimensional array storage amounts for rows and columns of surve data
#define VACATION_RENTERS 5
#define RENTER_SURVEY_CATEGORIES 3
// Rental property login and sentinal values
#define CORRECT_ID "id1"
#define CORRECT_PASSCODE "ABCD"
#define LOGIN_MAX_ATTEMPTS 3
#define SENTINAL_NEG1 -1
// Rental property constant ranges
#define MIN_RENTAL_NIGHTS 1
#define MAX_RENTAL_NIGHTS 14
#define MIN_RATE 1
#define MAX_RATE 1000
#define DISCOUNT_MULTIPLIER 2

#define MIN_RATINGS 1
#define MAX_RATINGS 5

// Property struct
typedef struct property {
	int totalRenters;
	int interval1;
	int interval2;
	double rate;
	double discount;
	char name[STRING_LENGTH];
	char location[STRING_LENGTH];
	int surveyResults[VACATION_RENTERS][RENTER_SURVEY_CATEGORIES];
} Property;

// Node struct
typedef struct node {
	Property data;
	struct node* nextPtr;
} Node;

// Function prototypes
bool ownerLogin();
void setPropertyInfo(Node** headPtr);
void insertProperty(Property* newProperty, Node** headPtr);
int compareStrings(char inputChar1[], char inputChar2[]);
int getValidInt(int min, int max, int sentinel);
void printRentalPropertyInfo(Node** headPtr, char* surveyCategories[]);
Node* getRentalLocation(Node** headPtr);
double calculateCharges(unsigned int userInput, Property* propertyInfo);
void printNightsCharges(unsigned int nights, double charges);
void getRatings(Property* selectedProperty, char* surveyCategories[]);
void printOwnerReport(Node** headPtr, char* surveyCategories[], int totalNights, double totalCost);

int main(void) {

	const char* surveyCategories[RENTER_SURVEY_CATEGORIES] = { "Check-in Process", "Cleanliness", "Amenities" };

	bool rentalMode = true;
	int userInput;
	int totalNights = 0;
	double totalCost = 0;

	if (ownerLogin()) {

		Node* head = malloc(sizeof(Node));
		Node** headPtr = &head;

		setPropertyInfo(headPtr);

		// Main Rental loop
		do {
			
			printRentalPropertyInfo(headPtr, surveyCategories);
			Node* selectedLocation = getRentalLocation(headPtr);

			printf("\nPlease enter the number of nights you wish to stay from %d to %d\n", MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS);
			userInput = getValidInt(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, SENTINAL_NEG1);
			
			if ((userInput != SENTINAL_NEG1) && (selectedLocation->data.totalRenters < VACATION_RENTERS)) {

				double cost = calculateCharges(userInput, &selectedLocation->data);
				printNightsCharges(userInput, cost);
				getRatings(&selectedLocation->data, surveyCategories);

				totalNights += userInput;
				totalCost += cost;
				selectedLocation->data.totalRenters++;
			}
			
			// Output when array is full
			else if ((userInput != SENTINAL_NEG1) && (selectedLocation->data.totalRenters >= VACATION_RENTERS)) {

				puts("Sorry, the maximum amount of renters have made reservations");
			}

			// Password protected function exit
			else if (ownerLogin()) {

				puts("");
				rentalMode = false;
			}

		} while (rentalMode);

		printOwnerReport(headPtr, surveyCategories, totalNights, totalCost);
	}

	puts("Exiting AirUCCS");
	return false;
}

/*
* Checks user login Property against defined username and password
* Parameters: void
* Returns: A bool if the login is successful 
*/
bool ownerLogin() {

	int attemptNum = 0;
	bool access = false;
	while ((attemptNum < LOGIN_MAX_ATTEMPTS) && (access == false)){

		char inputID[STRING_LENGTH];
		char inputPass[STRING_LENGTH];

		puts("Enter username");
		fgets(&inputID, STRING_LENGTH, stdin);
		inputID[strcspn(inputID, "\n")] = '\0';

		puts("Enter password");
		fgets(&inputPass, STRING_LENGTH, stdin);
		inputPass[strcspn(inputPass, "\n")] = '\0';

		attemptNum++;

		// Checks Credentials 
		if ((strcmp(inputID, CORRECT_ID) == 0) && (strcmp(inputPass, CORRECT_PASSCODE) == 0)) {

			access = true;
			puts("");
		}

		else if (attemptNum < LOGIN_MAX_ATTEMPTS) {

			printf("%d failed attempts. Please try again\n\n", attemptNum);
		}
	}

	return access;
}

/*
* Requests an input from the user and validates the input
* Parameters: int min, int max, int sentinel
* Returns: An int representing the users input
*/
int getValidInt(int min, int max, int sentinel) {

	bool validInput = false;
	int userInput = 0;

	while (validInput == false) {
		
		// Ensures input is an int
		if ((scanf("%d", &userInput) == true) && (getchar() == '\n')) {


			// Ensures input is within valid range
			if ((userInput == sentinel) || ((userInput >= min) && (userInput <= max))) {

				validInput = true;
			}

			else {

				printf("\nError: Input not in valid range.\nPlease enter a value between %d and %d:\n", min, max);
			}
		}

		// Clears buffer when recieving invalid input
		else {

			printf("\nError: Input is not valid.\nPlease enter a value between %d and %d:\n", min, max);
			while ((getchar()) != '\n');
		}
	}

	return userInput;
}

/*
* Creates Properties with related info until owner ends function
* Parameters: Node** headPtr
* Returns: void
*/
void setPropertyInfo(Node** headPtr) {

	char addProperty = 'y';
	while (addProperty == 'y') {

		Property* newProperty = malloc(sizeof(Property));

		newProperty->totalRenters = 0;

		puts("Enter the number of nights until the first discount:");
		newProperty->interval1 = getValidInt(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, SENTINAL_NEG1);

		puts("");
		puts("Enter the number of nights until the second discount:");
		newProperty->interval2 = getValidInt(newProperty->interval1, MAX_RENTAL_NIGHTS, SENTINAL_NEG1);

		puts("");
		puts("Enter the nightly rental rate:");
		newProperty->rate = getValidInt(MIN_RATE, MAX_RATE, SENTINAL_NEG1);

		puts("");
		puts("Enter the discount:");
		newProperty->discount = getValidInt(MIN_RATE, newProperty->rate / 2, SENTINAL_NEG1);

		puts("");;
		puts("Enter the property name:");
		fgets(newProperty->name, STRING_LENGTH, stdin);

		puts("");
		puts("Enter the property location:");
		fgets(newProperty->location, STRING_LENGTH, stdin);

		insertProperty(newProperty, headPtr);

		puts("");
		puts("Type (y)es or (n)o to add another property:");

		scanf(" %c", &addProperty);
		addProperty = tolower(addProperty);
		while ((getchar()) != '\n');
	}

}

/*
* Sorts the property into the linked list 
* Parameters: Property* newProperty, Node** headPtr
* Returns: void
*/
void insertProperty(Property* newProperty, Node** headPtr) {

	bool insert = true;
	Node* newNode = malloc(sizeof(Node));
	Node* currentNode = *headPtr;
	Node* previousNode = NULL;

	while (insert) {

		if (compareStrings(&newNode->data.name, &currentNode->data.name) < 0) {

			if (currentNode == *headPtr) {

				newNode->nextPtr = currentNode;
				*headPtr = newNode;
			}

			else if (currentNode == NULL) {

				previousNode->nextPtr = newNode;
			}

			else {

				newNode->nextPtr = currentNode;
				previousNode->nextPtr = newNode;
			}

			insert = false;
		}

		else {

			previousNode = currentNode;
			currentNode = currentNode->nextPtr;
		}
	}
}

/*
* Compares the names of 2 properties
* Parameters: Property* newProperty, Property* nodeProperty
* Returns: An int representing respective difference between the two strings
*/
int compareStrings(char inputChar1[], char inputChar2[]) {

	//char tempChar1[STRING_LENGTH];
	//char tempChar2[STRING_LENGTH];

	//strcpy(tempChar1, inputChar1);
	//strcpy(tempChar2, inputChar2);

	int i = 0;
	do {

		inputChar1[i] = tolower(inputChar1[i]);
		i++;
	} while (inputChar1[i] != '\0');

	i = 0;
	do {

		inputChar2[i] = tolower(inputChar2[i]);
		i++;
	} while (inputChar2[i] != '\0');

	return strcmp(inputChar1, inputChar2);
}

Node* getRentalLocation(Node** headPtr) {

	Node* currentNode = *headPtr;
	int compareResult = 1;
	char nameInput[STRING_LENGTH];

	while (compareResult != 0) {

		do {

			fgets(nameInput, STRING_LENGTH, stdin);
			compareResult = compareStrings(nameInput, currentNode->data.name);
			currentNode = currentNode->nextPtr;

		} while ((compareResult != 0) && (currentNode != NULL));
		
		if (compareResult != 0) {

			puts("Error: The property you entered doesn�t match. Enter the property again.");
		}
	}

	return currentNode;
} // Computationally inefficient, should use premade array of lowercase names

/*
* Determines the total cost for total amount of nights selected
* Parameters: int nights, int interval1Nights, int interval2Nights, double rate, double discount
* Returns: A double representing the total cost
*/
double calculateCharges(unsigned int userInput, Property* propertyInfo) {

	int currentCost = 0;

	if (userInput <= propertyInfo->interval1) {

		currentCost = propertyInfo->rate * userInput;
	}

	else if (userInput <= propertyInfo->interval2) {

		currentCost += propertyInfo->rate * propertyInfo->interval1;
		currentCost += (propertyInfo->rate - propertyInfo->discount) * (userInput - propertyInfo->interval1);
	}

	else {

		currentCost += propertyInfo->rate * propertyInfo->interval1;
		currentCost += (propertyInfo->rate - propertyInfo->discount) * (propertyInfo->interval2 - propertyInfo->interval1);
		currentCost += (propertyInfo->rate - propertyInfo->discount*2) * (userInput- propertyInfo->interval2);
	}
	
	return currentCost;
}

/*
* Requests entry from the user and saves inputs in the ratings array
* Parameters: Property* selectedProperty, char* surveyCategories[]
* Returns: void
*/
void getRatings(Property* selectedProperty, char* surveyCategories[]) {

	puts("We want to know how your experience was renting our property.");
	puts("Using the rating system 1 to 5 enter your rating for each category:");
	puts("");

	for (int i = 0; i < RENTER_SURVEY_CATEGORIES; i++) {

		printf("%d: %s\n", i + 1, surveyCategories[i]);
	}

	for (int i = 0; i < RENTER_SURVEY_CATEGORIES; i++) {

		printf("\nEnter your rating for Category %d:\n", i + 1);
		selectedProperty->surveyResults[selectedProperty->totalRenters][i] = getValidInt(MIN_RATINGS, MAX_RATINGS, SENTINAL_NEG1);
	}
}

/*
* Displays the relevant Property for the rental property
* Parameters: Property *propertyInfo, int surveyResults[]
* Returns: void
*/
void printRentalPropertyInfo(Node** headPtr, char* surveyCategories[]) {

	Node* currentNode = *headPtr;
	while (currentNode != NULL) {

		printf("\n-------------------------------------------------\nName: %s", currentNode->data.name);
		printf("Location: %s\n", currentNode->data.location);
		printf("- Rental propert can be rented for %d to %d nights.\n", MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS);
		printf("- $%.f rate a night for the first %d nights.\n", currentNode->data.rate, currentNode->data.interval1);
		printf("- $%.f discount for nights %d to %d.\n", currentNode->data.discount, currentNode->data.interval1 + 1, currentNode->data.interval2);
		printf("- $%.f discount for each remaining night over %d.\n\n", currentNode->data.discount * 2, currentNode->data.interval2);

		puts("Survey Results:");

		if (currentNode->data.totalRenters == 0) {

			puts("No Ratings Currently");
		}

		else {

			printf("Rating Categories:");
			for (int i = 0; i < RENTER_SURVEY_CATEGORIES; i++) {

				printf("\t%d.%s", i + 1, surveyCategories[i]);
			}

			for (int i = 0; i < currentNode->data.totalRenters; i++) {

				printf("\nSurvey %d:\t\t  ", i + 1);

				for (int j = 0; j < RENTER_SURVEY_CATEGORIES; j++) {

					printf("%d%*s", currentNode->data.surveyResults[i][j], strlen(surveyCategories[j]), "\t  ");
				}
			}
		}
		puts("");
	}

	puts("---------------------------------------------------------------------------");
}

/*
* Displays the nights and total cost passed to the function
* Parameters: int nights, double charges
* Returns: void
*/
void printNightsCharges(unsigned int nights, double charges) {

	printf("\nNights\tCharge\n%d\t$%.0f\n--------------\n\n", nights, charges);
} // Currently vestigial function


//fix this for headPtr. start on user story 4
/*
* Displays all pertinent data as a close to the program, calculates rating averages
* Parameters: Property* propertyInfo, int surveyResults[][], char surveyCategories[][STRING_LENGTH], int totalRenters, int totalNights, double totalCost
* Returns: void
*/
void printOwnerReport(Node** headPtr, char* surveyCategories[], int totalNights, double totalCost) {

	puts("--------------------------------");
	puts("Rental Property Report:");
	printf("Name: %s", propertyInfo->name);
	printf("Location: %s\n", propertyInfo->location);

	puts("Rental Property Totals:");
	puts("-----------------------");
	puts("Renters	Nights	Charges");
	printf("%d\t%d\t$%0.2f\n\n", totalRenters, totalNights, totalCost);



	puts("Category Rating Averages");
	puts("------------------------");

	for (int i = 0; i < RENTER_SURVEY_CATEGORIES; i++) {

		int ratingSum = 0;
		for (int j = 0; j < totalRenters; j++) {

			ratingSum += surveyResults[j][i];
		}
		
		printf("%s: %0.1f\n", surveyCategories[i], (float)ratingSum/totalRenters);
	}

	puts("--------------------------------");
	puts("");
}

// Do functions need to define column count in 2D arrays they take
// Printing out a string from a string array using character call or pointers?
// Initializing char* (userID etc) with '=NULL'?
// Alternative to generics to call getValid_ for ints vs doubles
// getRatings crashes if called after array is full. main prevents call. Should function have internal crash prevention