//Name: Quinn Hackenberg
//Class: CS2060 T/R 1:40PM - 2:55PM 
//Windows OS
//Description: ////////////////////////////////////

#include <stdio.h>
#include <stdbool.h>
#include <string>

//Maximum length of a string
#define STRING_LENGTH 80
//Two dimensional array storage amounts for rows and columns of surve data
#define VACATION_RENTERS 5
#define RENTER_SURVEY_CATEGORIES 3
//Rental property login and sentinal values
#define CORRECT_ID "id1"
#define CORRECT_PASSCODE "ABCD"
#define LOGIN_MAX_ATTEMPTS 3
#define SENTINAL_NEG1 -1
//rental property constant ranges
#define MIN_RENTAL_NIGHTS 1
#define MAX_RENTAL_NIGHTS 14
#define MIN_RATE 1
#define MAX_RATE 1000
#define DISCOUNT_MULTIPLIER 2

// Function prototypes
void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount);
int getValidInt(int min, int max, int sentinel);
double calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount);
void printNightsCharges(unsigned int nights, double charges);

// New Function prototypes
bool ownerLogin();


int main(void) {

	if (ownerLogin()) {


	}

	do {

		printRentalPropertyInfo(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, INTERVAL_1_NIGHTS, 
			INTERVAL_2_NIGHTS, RENTAL_RATE, DISCOUNT);

		daysInput = getValidInt(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, SENTINEL_NEG1);

		if (daysInput != -1) {

			totalNights += daysInput;

			int cost = calculateCharges(daysInput, INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS,
				RENTAL_RATE, DISCOUNT);
			totalCost += cost;

			puts("Rental Charges\n");
			printNightsCharges(daysInput, cost);
		}

	} while (daysInput != -1);

	puts("Rental Prooperty Owner Total Summary\n");
	printNightsCharges(totalNights, totalCost);

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

		if ((inputID == CORRECT_ID) && (inputPass == CORRECT_PASSCODE)) {

			access = 1;
		}

		attemptNum++;
	}
}



////////////////////////////////////////////////////////////////
/*
* Displays the relevant info for the rental property
* Parameters: int minNights, int maxNights, int interval1Nights, int interval2Nights, double rate, double discount
* Returns: void
*/
void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount) {

	printf("- Rental propert can be rented for %d to %d nights.\n", minNights, maxNights);
	printf("- $%3.f rate a night for the first %d nights.\n", rate, interval1Nights);
	printf("- $%3.f discounted rate a night for nights %d to %d.\n", rate - discount, interval1Nights + 1, interval2Nights);
	printf("- $%3.f discounted rate for each remaining night over %d.\n\n", rate - discount *2, interval2Nights);
} 

/*
* Requests an input from the user and validates the input
* Parameters: int min, int max, int sentinel
* Returns: An int representing the users input
*/
int getValidInt(int min, int max, int sentinel) {

	bool validInput = false;
	int userInput = 0;

	puts("Please enter the number of nights you want to rent the property:");

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

			puts("\nError: Input is not valid.\nPlease enter the number of nights you want to rent the property:\n");

			while ((getchar()) != '\n');

		}
	}

	return userInput;
}

/*
* Determines the total cost for total amount of nights selected
* Parameters: int nights, int interval1Nights, int interval2Nights, double rate, double discount
* Returns: A double representing the total cost
*/
double calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount) {

	int currentCost = 0;

	if (nights <= interval1Nights) {

		currentCost = rate * nights;
	}

	else if (nights <= interval2Nights) {

		currentCost += rate * interval1Nights;
		currentCost += (rate - discount) * (nights - interval1Nights);
	}

	else {

		currentCost += rate * interval1Nights;
		currentCost += (rate - discount) * (interval2Nights - interval1Nights);
		currentCost += (rate - discount*2) * (nights- interval2Nights);
	}
	
	return currentCost;
}

/*
* Displays the nights and total cost passed to the function
* Parameters: int nights, double charges
* Returns: void
*/
void printNightsCharges(unsigned int nights, double charges) {

	printf("\nNights\tCharge\n%d\t$%.0f\n--------------\n\n", nights, charges);
}