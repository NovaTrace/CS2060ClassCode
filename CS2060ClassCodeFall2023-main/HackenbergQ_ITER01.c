#include <stdio.h>
#include <stdbool.h>

// Define rates
#define baseRate 400
#define firstDiscount 50
#define secondDiscount 100

// Define ranges for nights
#define interval1 3
#define interval2 6
#define intervalMin 1
#define intervalMax 14

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

	printf("- Rental propert can be rented for %d to %d nights.\n", intervalMin, intervalMax);
	printf("- $%d rate a night for the first %d nights.\n", baseRate, interval1);
	printf("- $%d discounted rate a night for nights %d to %d.\n", baseRate - firstDiscount, interval1 + 1, interval2);
	printf("- $%d discounted rate for each remaining night over %d.\n\n", baseRate - secondDiscount, interval2);
} 

int userInput() {

	bool validInput = false;
	int userInput = 0;

	puts("Please enter the number of nights you want to rent the property:");

	while (validInput == false) {

		// Ensures input is an int
		if (scanf("%d", &userInput) == true) {

			// Ensures input is within valid range
			if ((userInput == -1) || ((userInput >= intervalMin) && (userInput <= intervalMax))) {

				validInput = true;
			}

			else {

				printf("\nError: Input not in valid range.\nPlease enter a value between %d and %d:\n", intervalMin, intervalMax);
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

	if (daysInput <= interval1) {

		currentCost = baseRate * daysInput;
	}

	else if (daysInput <= interval2) {

		currentCost += baseRate * interval1;
		currentCost += (baseRate - firstDiscount) * (daysInput - interval1);
	}

	else {

		currentCost += baseRate * interval1;
		currentCost += (baseRate - firstDiscount) * (interval2 - interval1);
		currentCost += (baseRate - secondDiscount) * (daysInput - interval2);
	}
	
	return currentCost;
}

void rentalCost(int daysInput, int cost) {

	printf("\n--------------\nRental Charge:\n\nNights\tCharge\n%d\t$%d\n--------------\n\n", daysInput, cost);
}

void rentalSummery(int totalCost, int totalNights) {

	printf("\n------------------------\nRental property summary:\n\nNights\tCharge\n%d\t$%d\n------------------------\n", totalNights, totalCost);
}