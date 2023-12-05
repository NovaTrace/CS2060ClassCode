//Name: Quinn Hackenberg
//Class: CS2060 T/R 1:40PM - 2:55PM 
//Windows OS
//Description: Rental property interface for owners and renters. Includes an owner sign in, property set-up, 
//limited user rentals, user ratings and password protected program exit with data summery

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Maximum length of a string
#define STRING_LENGTH 80
// Two dimensional array storage amounts for rows and columns of surve data
#define VACATION_RENTERS 5
#define RENTER_SURVEY_CATEGORIES 4
// Rental property login and sentinal values
#define CORRECT_ID "id"
#define CORRECT_PASSCODE "ab"
#define LOGIN_MAX_ATTEMPTS 2
#define SENTINAL_NEG1 -1
// Rental property constant ranges
#define MIN_RENTAL_NIGHTS 1
#define MAX_RENTAL_NIGHTS 14
#define MIN_RATE 1
#define MAX_RATE 1000
#define DISCOUNT_MULTIPLIER 2

#define MIN_RATINGS 1
#define MAX_RATINGS 5

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
bool ownerLogin();
void setPropertyInfo(Info* propertyInfo);
int getValidInt(int min, int max, int sentinel);
void printRentalPropertyInfo(Info* propertyInfo, int totalRenters, int surveyResults[][RENTER_SURVEY_CATEGORIES], char* surveyCategories[]);
double calculateCharges(unsigned int userInput, Info* propertyInfo);
void printNightsCharges(unsigned int nights, double charges);
void getRatings(int totalRenters, int surveyResults[][RENTER_SURVEY_CATEGORIES], char* surveyCategories[]);
void printOwnerReport(Info* propertyInfo, int surveyResults[][RENTER_SURVEY_CATEGORIES], char* surveyCategories[], int totalRenters, int totalNights, double totalCost);

int main(void) {

	if (ownerLogin()) {

		bool rentalMode = 1;
		int userInput;
		int totalRenters = 0;
		int totalNights = 0;
		double totalCost = 0;

		int surveyResults[VACATION_RENTERS][RENTER_SURVEY_CATEGORIES];
		const char* surveyCategories[RENTER_SURVEY_CATEGORIES] = { "Check-in Process", "Cleanliness", "Amenities", "cat4"};

		Info propertyInfo1;
		setPropertyInfo(&propertyInfo1);

		// Main Rental loop
		do {
			
			printRentalPropertyInfo(&propertyInfo1, totalRenters, surveyResults, surveyCategories);

			printf("\nPlease enter the number of nights you wish to stay from %d to %d\n", MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS);
			userInput = getValidInt(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, SENTINAL_NEG1);
			
			if ((userInput != SENTINAL_NEG1) && (totalRenters < VACATION_RENTERS)) {

				double cost = calculateCharges(userInput, &propertyInfo1);
				printNightsCharges(userInput, cost);
				getRatings(totalRenters, surveyResults, surveyCategories);

				totalNights += userInput;
				totalCost += cost;
				totalRenters++;
			}
			
			// Output when array is full
			else if ((userInput != SENTINAL_NEG1) && (totalRenters >= VACATION_RENTERS)) {

				puts("Sorry, the maximum amount of renters have made reservations");
			}

			// Password protected function exit
			else if (ownerLogin()) {

				puts("");
				rentalMode = 0;
			}

		} while (rentalMode);

		printOwnerReport(&propertyInfo1, surveyResults, surveyCategories, totalRenters, totalNights, totalCost);
	}

	puts("Exiting AirUCCS");
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
	while ((attemptNum < LOGIN_MAX_ATTEMPTS) && (access == 0)){

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

			access = 1;
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
	char extraInput;

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
* Assigns info for property rentals by reference
* Parameters: Info *propertyInfo
* Returns: void
*/
void setPropertyInfo(Info *propertyInfo) {

	puts("Enter the number of nights until the first discount:");
	propertyInfo->interval1 = getValidInt(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, SENTINAL_NEG1);

	puts("");
	puts("Enter the number of nights until the second discount:");
	propertyInfo->interval2 = getValidInt(propertyInfo->interval1, MAX_RENTAL_NIGHTS, SENTINAL_NEG1);

	puts("");
	puts("Enter the nightly rental rate:");
	propertyInfo->rate = getValidInt(MIN_RATE, MAX_RATE, SENTINAL_NEG1);

	puts("");
	puts("Enter the discount:");
	propertyInfo->discount = getValidInt(MIN_RATE, propertyInfo->rate/2, SENTINAL_NEG1);

	puts("");
	puts("Enter the property name:");
	fgets(&propertyInfo->name, STRING_LENGTH, stdin);

	puts("");
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
void getRatings(int totalRenters, int surveyResults[][RENTER_SURVEY_CATEGORIES], char* surveyCategories[]) {

	puts("We want to know how your experience was renting our property.");
	puts("Using the rating system 1 to 5 enter your rating for each category:");
	puts("");

	for (int i = 0; i < RENTER_SURVEY_CATEGORIES; i++) {

		printf("%d: %s\n", i + 1, surveyCategories[i]);
	}

	for (int i = 0; i < RENTER_SURVEY_CATEGORIES; i++) {

		printf("\nEnter your rating for Category %d:\n", i + 1);
		surveyResults[totalRenters][i] = getValidInt(MIN_RATINGS, MAX_RATINGS, SENTINAL_NEG1);
	}
}

/*
* Displays the relevant info for the rental property
* Parameters: Info *propertyInfo, int surveyResults[]
* Returns: void
*/
void printRentalPropertyInfo(Info* propertyInfo, int totalRenters, int surveyResults[][RENTER_SURVEY_CATEGORIES], char* surveyCategories[]) {

	printf("\n-------------------------------------------------\nName: %s", propertyInfo->name);
	printf("Location: %s\n", propertyInfo->location);
	printf("- Rental propert can be rented for %d to %d nights.\n", MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS);
	printf("- $%.f rate a night for the first %d nights.\n", propertyInfo->rate, propertyInfo->interval1);
	printf("- $%.f discount for nights %d to %d.\n", propertyInfo->discount, propertyInfo->interval1 + 1, propertyInfo->interval2);
	printf("- $%.f discount for each remaining night over %d.\n\n", propertyInfo->discount * 2, propertyInfo->interval2);

	puts("Survey Results:");

	if (totalRenters == 0) {

		puts("No Ratings Currently");
	}

	else {

		printf("Rating Categories:");
		for (int i = 0; i < RENTER_SURVEY_CATEGORIES; i++) {

			printf("\t%d.%s", i + 1, surveyCategories[i]);
		}

		for (int i = 0; i < totalRenters; i++) {

			printf("\nSurvey %d:\t\t  ", i + 1);

			for (int j = 0; j < RENTER_SURVEY_CATEGORIES; j++) {

				printf("%d%*s", surveyResults[i][j], strlen(surveyCategories[j]), "\t  ");
			}
		}
	}
	puts("");
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

/*
* Displays all pertinent data as a close to the program, calculates rating averages
* Parameters: Info* propertyInfo, int surveyResults[][], char surveyCategories[][STRING_LENGTH], int totalRenters, int totalNights, double totalCost
* Returns: void
*/
void printOwnerReport(Info* propertyInfo, int surveyResults[][RENTER_SURVEY_CATEGORIES], char* surveyCategories[], int totalRenters, int totalNights, double totalCost) {

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