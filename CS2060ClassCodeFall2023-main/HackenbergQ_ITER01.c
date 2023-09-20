#include <stdio.h>
#include <stdbool.h>

#define baseRate 400
#define firstDiscount 50
#define secondDiscount 100

#define interval1 3
#define interval2 6
#define intervalMin 1
#define intervalMax 14


void propertyInformation();
int userInput();

int main(void) {

	propertyInformation();

	userInput();


	return 0;
}

void propertyInformation() {

	printf("- Rental propert can be rented for %d to %d nights.\n", intervalMin, intervalMax);
	printf("- $%d rate a night for the first %d nights.\n", baseRate, interval1);
	printf("- $%d discounted rate a night for nights %d to %d.\n", baseRate - firstDiscount, interval1 + 1, interval2);
	printf("- $%d discounted rate for each remaining night over %d.\n\n", baseRate - secondDiscount, interval2);
}

int userInput() {

	bool validInput = 0;
	int userInput = 0;

	while (validInput = 0) {

		if (scanf("%d", &userInput) == 0){

			if ((userInput == -1) || ((userInput > 0) && (userInput < 15))) {

			}
		}
	}

}