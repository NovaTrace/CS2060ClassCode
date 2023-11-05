//Name: Quinn Hackenberg
//Class: CS2060 T/R 1:40PM - 2:55PM 
//Windows OS
//Description: ////////////////////////////////////

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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

// Property Info struct
typedef struct info {
	int interval1;
	int interval2;
	double rate;
	double discount;
	char name[STRING_LENGTH];
	char location[STRING_LENGTH];
} Info;

// Function prototypes
int getValidInt(int min, int max, int sentinel);
double calculateCharges(unsigned int userInput, Info *propertyInfo);
void printNightsCharges(unsigned int nights, double charges);

// New Function prototypes
void setPropertyInfo(Info *propertyInfo);
bool ownerLogin();
void printRentalPropertyInfo(Info* propertyInfo, int totalRenters, int surveyResults[][RENTER_SURVEY_CATEGORIES], char surveyCategories[][STRING_LENGTH]);
void getRatings(int totalRenters, int surveyResults[][RENTER_SURVEY_CATEGORIES], char surveyCategories[][STRING_LENGTH]);
void printOwnerReport(Info* propertyInfo, int surveyResults[][RENTER_SURVEY_CATEGORIES], int totalRenters, int totalNights, double totalCost);

int main(void) {

	if (ownerLogin()) {

		Info propertyInfo1;
		setPropertyInfo(&propertyInfo1);
		
		int surveyResults[VACATION_RENTERS][RENTER_SURVEY_CATEGORIES];
		char surveyCategories[RENTER_SURVEY_CATEGORIES][STRING_LENGTH] = { "Check-in Process", "Cleanliness", "Amenities" };

		bool rentalMode = 1;
		int userInput;
		int totalRenters = 0;
		int totalNights = 0;
		double totalCost = 0;
		do {
			
			printRentalPropertyInfo(&propertyInfo1, totalRenters, surveyResults, surveyResults);

			userInput = getValidInt(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, SENTINAL_NEG1);
			
			if ((userInput != SENTINAL_NEG1) && (totalRenters < VACATION_RENTERS)) {

				double cost = calculateCharges(userInput, &propertyInfo1);
				printNightsCharges(userInput, cost);

				totalNights += userInput;
				totalCost += cost;
				totalRenters++;

				getRatings(totalRenters, surveyResults, surveyCategories);
			}
			
			else if (totalRenters >= VACATION_RENTERS) {

				puts("Sorry, the maximum amount of renters have made reservations");
			}

			else if (ownerLogin()) {

				rentalMode = 0;
			}

		} while (rentalMode);

		printOwnerReport(&propertyInfo1, surveyResults, totalRenters, totalNights, totalCost);
	}

	return 0;
}

/*
* Checks user login info against defined username and password
* Parameters: void
* Returns: A bool if the login is successful 
*/
bool ownerLogin() {

	int attemptNum = 0;
	bool access = 0;
	while ((attemptNum < 3) && (access == 0)){

		char* inputID;
		char* inputPass;

		puts("Enter username");
		fgets(inputID, STRING_LENGTH, stdin);

		puts("Enter password");
		fgets(inputPass, STRING_LENGTH, stdin);

		if ((strcmp(inputID, CORRECT_ID) == 0) && (strcmp(inputPass,CORRECT_PASSCODE) == 0)) {

			access = 1;
		}

		attemptNum++;
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
		if (scanf("%d", &userInput) == true) {

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

			puts("\nError: Input is not valid.\nPlease enter a value between %d and %d:\n", min, max);

			while ((getchar()) != '\n');

		}
	}

	return userInput;
}

/*
* Assigns info for property rentals by reference
* Parameters: Info *propertyInfo
* Returns: void
*/
void setPropertyInfo(Info *propertyInfo) {

	puts("Enter the number of nights until the first discount:");
	propertyInfo->interval1 = getValidInt(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, SENTINAL_NEG1);

	puts("Enter the number of nights until the second discount:");
	propertyInfo->interval2 = getValidInt(propertyInfo->interval1, MAX_RENTAL_NIGHTS, SENTINAL_NEG1);

	puts("Enter the nightly rental rate:");
	propertyInfo->rate = getValidInt(MIN_RATE, MAX_RATE, SENTINAL_NEG1);

	puts("Enter the discount:");
	propertyInfo->discount = getValidInt(MIN_RATE, propertyInfo->rate, SENTINAL_NEG1);

	puts("Enter the property name:");
	fgets(&propertyInfo->name, STRING_LENGTH, stdin);

	puts("Enter the property location:");
	fgets(&propertyInfo->location, STRING_LENGTH, stdin);
}

/*
* Determines the total cost for total amount of nights selected
* Parameters: int nights, int interval1Nights, int interval2Nights, double rate, double discount
* Returns: A double representing the total cost
*/
double calculateCharges(unsigned int userInput, Info* propertyInfo) {

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
* Parameters: int ratings[]
* Returns: void
*/
void getRatings(int totalRenters, int surveyResults[][RENTER_SURVEY_CATEGORIES], char surveyCategories[][STRING_LENGTH]) {

	puts("We want to know how your experience was renting our property. \nUsing the rating system 1 to 5 enter your rating for each category:");
	for (int i = 0; i < RENTER_SURVEY_CATEGORIES; i++) {

		puts("%d: %s", i, surveyCategories[i]);
	}

	for (int i = 0; i < RENTER_SURVEY_CATEGORIES; i++) {

		puts("Enter your rating for Category %d:", i);
		surveyResults[totalRenters][i] = getValidInt(1, 5, SENTINAL_NEG1);
	}
}

/*
* Displays the relevant info for the rental property
* Parameters: Info *propertyInfo, int surveyResults[]
* Returns: void
*/
void printRentalPropertyInfo(Info* propertyInfo, int totalRenters, int surveyResults[][RENTER_SURVEY_CATEGORIES], char surveyCategories[][STRING_LENGTH]) {

	printf("Name: %s\n", propertyInfo->name);
	printf("Location: %s\n", propertyInfo->location);
	printf("- Rental propert can be rented for %d to %d nights.\n", MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS);
	printf("- $%3.f rate a night for the first %d nights.\n", propertyInfo->rate, propertyInfo->interval1);
	printf("- $%3.f discounted rate a night for nights %d to %d.\n", propertyInfo->rate - propertyInfo->discount, propertyInfo->interval1 + 1, propertyInfo->interval2);
	printf("- $%3.f discounted rate for each remaining night over %d.\n\n", propertyInfo->rate - propertyInfo->discount * 2, propertyInfo->interval2);

	puts("Survey Results:\n");

	if (totalRenters = 0) {

		puts("No Ratings Currently");
	}

	else {

		printf("Rating Categories:");
		for (int i = 0; i < RENTER_SURVEY_CATEGORIES; i++) {

			puts("\t%d.%s", i + 1, surveyCategories[i]);
		}

		for (int i = 1; i <= totalRenters; i++) {

			printf("\nSurvey %d:\t", i);

			for (int j = 0; j < RENTER_SURVEY_CATEGORIES; j++) {

				printf("\t%d", surveyResults[i][j]);
			}
		}
	}
}

/*
* Displays the nights and total cost passed to the function
* Parameters: int nights, double charges
* Returns: void
*/
void printNightsCharges(unsigned int nights, double charges) {

	printf("\nNights\tCharge\n%d\t$%.0f\n--------------\n\n", nights, charges);
}

/*
* Displays all pertinent data as a close to the program
* Parameters: Info* propertyInfo, int surveyResults[][], int totalRenters, int totalNights, double totalCost
* Returns: void
*/
void printOwnerReport(Info* propertyInfo, int surveyResults[][RENTER_SURVEY_CATEGORIES], int totalRenters, int totalNights, double totalCost) {

	puts("Rental Property Report");
	printf("Name: %s\n", propertyInfo->name);
	printf("Location: %s\n", propertyInfo->location);

	puts("Rental Property Totals");
	puts("Renters	Nights	Charges");
	printf("%d\t%d\t$%f.2\n", totalRenters, totalNights, totalCost);

	puts("Exiting AirUCCS");
}

// Do functions need to define column count in 2D arrays they take
// Single line print out without \n in printf?
// Printing out a string from a string array using character call or pointers?