//Quinn Hackenberg
//C on Windows 11
//Description: This code in its current iteration takes a user input and, using predefined parameters, calculated the cost and summery of costs/nights
//of a rental. 

#include <stdio.h>
#include <stdbool.h>

// Function prototypes
void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, unsigned int
	interval1Nights, unsigned int interval2Nights, double rate, double discount);
int getValidInt(int min, int max, int sentinel);
double calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int
	interval2Nights, double rate, double discount);
void printNightsCharges(unsigned int nights, double charges);


int main(void) {

	int const SENTINAL_NEG1 = -1;

	// Define rates
	double const RENTAL_RATE = 400;
	double const DISCOUNT = 50;

	// Define ranges for nights
	unsigned int const MIN_RENTAL_NIGHTS = 1;
	unsigned int const MAX_RENTAL_NIGHTS = 14;
	unsigned int const INTERVAL_1_NIGHTS = 3;
	unsigned int const INTERVAL_2_NIGHTS = 6;

	int totalCost = 0;
	int totalNights = 0;
	int daysInput = 0;

	do {

		// Displays availiable nights and costs
		printRentalPropertyInfo(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, INTERVAL_1_NIGHTS, 
			INTERVAL_2_NIGHTS, RENTAL_RATE, DISCOUNT);

		// Requests and validates user input
		daysInput = getValidInt(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, SENTINAL_NEG1);

		// Runs calculations and standard output until program is ended
		if (daysInput != -1) {

			totalNights += daysInput;

			// Calculates the cost for the selected number of nights
			int cost = calculateCharges(daysInput, INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS,
				RENTAL_RATE, DISCOUNT);
			totalCost += cost;

			// Displays reciept for the purchase
			puts("Rental Charges\n");
			printNightsCharges(daysInput, cost);
		}

	} while (daysInput != -1);

	// Displays program totals when -1 is entered and ends the program
	puts("Rental Prooperty Owner Total Summary\n");
	printNightsCharges(totalNights, totalCost);

	return 0;
}



void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, unsigned int
	interval1Nights, unsigned int interval2Nights, double rate, double discount) {

	printf("- Rental propert can be rented for %d to %d nights.\n", minNights, maxNights);
	printf("- $%3.f rate a night for the first %d nights.\n", rate, interval1Nights);
	printf("- $%3.f discounted rate a night for nights %d to %d.\n", rate - discount, interval1Nights + 1, interval2Nights);
	printf("- $%3.f discounted rate for each remaining night over %d.\n\n", rate - discount *2, interval2Nights);
} 

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

double calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int
	interval2Nights, double rate, double discount) {

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

void printNightsCharges(unsigned int nights, double charges) {

	printf("\nNights\tCharge\n%d\t$%.0f\n--------------\n\n", nights, charges);
}



//**Notes**

/*Property Information
* Parameters:
* Return:
* Summary:
*/

//CONSTANTS ALL CAPS