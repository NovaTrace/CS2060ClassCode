//Quinn Hackenberg
//C on Windows 11
//Description: This code in its current iteration takes a user input and, using predefined parameters, calculated the cost and summery of costs/nights
//of a rental. 

#include <stdio.h>
#include <stdbool.h>

int const SENTINAL_NEG1 = -1;

// Define rates
double const RENTAL_RATE = 400;
double const DISCOUNT = 50;

// Define ranges for nights
unsigned int const MIN_RENTAL_NIGHTS = 1;
unsigned int const MAX_RENTAL_NIGHTS = 14;
unsigned int const INTERVAL_1_NIGHTS = 3;
unsigned int const INTERVAL_2_NIGHTS = 6;

// Function prototypes
void propertyInformation();
int userInput();
void rentalSummery(int totalCost, int totalNights);
void rentalCost(int daysInput, int cost);
int costCalculation(int daysInput);

int main(void) {

	int totalCost = 0;
	int totalNights = 0;
	int daysInput = 0;

	do {

		// Displays availiable nights and costs
		propertyInformation();

		// Requests and validates user input
		daysInput = userInput();

		// Runs calculations and standard output until program is ended
		if (daysInput != -1) {

			totalNights += daysInput;

			// Calculates the cost for the selected number of nights
			int cost = costCalculation(daysInput);
			totalCost += cost;

			// Displays reciept for the purchase
			rentalCost(daysInput, cost);
		}

	} while (daysInput != -1);

	// Displays program totals when -1 is entered and ends the program
	rentalSummery(totalCost, totalNights);

	return 0;
}



void propertyInformation() {

	printf("- Rental propert can be rented for %d to %d nights.\n", MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS);
	printf("- $%d rate a night for the first %d nights.\n", RENTAL_RATE, INTERVAL_1_NIGHTS);
	printf("- $%d discounted rate a night for nights %d to %d.\n", RENTAL_RATE - DISCOUNT, INTERVAL_1_NIGHTS + 1, INTERVAL_2_NIGHTS);
	printf("- $%d discounted rate for each remaining night over %d.\n\n", RENTAL_RATE - DISCOUNT*2, INTERVAL_2_NIGHTS);
} 

int userInput() {

	bool validInput = false;
	int userInput = 0;

	puts("Please enter the number of nights you want to rent the property:");

	while (validInput == false) {

		// Ensures input is an int
		if (scanf("%d", &userInput) == true) {

			// Ensures input is within valid range
			if ((userInput == -1) || ((userInput >= MIN_RENTAL_NIGHTS) && (userInput <= MAX_RENTAL_NIGHTS))) {

				validInput = true;
			}

			else {

				printf("\nError: Input not in valid range.\nPlease enter a value between %d and %d:\n", MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS);
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

int costCalculation(int daysInput) {

	int currentCost = 0;

	if (daysInput <= INTERVAL_1_NIGHTS) {

		currentCost = RENTAL_RATE * daysInput;
	}

	else if (daysInput <= INTERVAL_2_NIGHTS) {

		currentCost += RENTAL_RATE * INTERVAL_1_NIGHTS;
		currentCost += (RENTAL_RATE - DISCOUNT) * (daysInput - INTERVAL_1_NIGHTS);
	}

	else {

		currentCost += RENTAL_RATE * INTERVAL_1_NIGHTS;
		currentCost += (RENTAL_RATE - DISCOUNT) * (INTERVAL_2_NIGHTS - INTERVAL_1_NIGHTS);
		currentCost += (RENTAL_RATE - DISCOUNT*2) * (daysInput - INTERVAL_2_NIGHTS);
	}
	
	return currentCost;
}

void rentalCost(int daysInput, int cost) {

	printf("\n--------------\nRental Charge:\n\nNights\tCharge\n%d\t$%d\n--------------\n\n", daysInput, cost);
}

void rentalSummery(int totalCost, int totalNights) {

	printf("\n------------------------\nRental property summary:\n\nNights\tCharge\n%d\t$%d\n------------------------\n", totalNights, totalCost);
}



//**Notes**

/*Property Information
* Parameters:
* Return:
* Summary:
*/

//CONSTANTS ALL CAPS