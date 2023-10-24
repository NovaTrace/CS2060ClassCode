
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define LENGTH 13

void exploreValidateInt(const char* buff);
bool validateInt(char* buff, int* const validInt);
void printLimits();
bool intValidation(char* stringIn, int* validInt, int rangeMin, int rangeMax);

int main(void)
{

	char inputStr[LENGTH]; // create char arintray
	size_t inputLength = 0; 

	printLimits();

	for (unsigned int counter = 1; counter < 6; counter++)
	{
		bool validInput = 0;
		int validInt = 0;
		puts("\nEnter an integer");
		fgets(inputStr, LENGTH, stdin);
		
		exploreValidateInt(inputStr);
		validInput = intValidation(&inputStr, &validInt, INT_MIN, INT_MAX);
		printf("Valid int: %d", validInput);
	}

}



void printLimits()
{
	printf("The number of bits in a byte %d\n", CHAR_BIT);

	printf("The minimum value of SIGNED CHAR = %d\n", SCHAR_MIN);
	printf("The maximum value of SIGNED CHAR = %d\n", SCHAR_MAX);
	printf("The maximum value of UNSIGNED CHAR = %d\n", UCHAR_MAX);

	printf("The minimum value of SHORT INT = %d\n", SHRT_MIN);
	printf("The maximum value of SHORT INT = %d\n", SHRT_MAX);

	printf("The minimum value of INT = %d\n", INT_MIN);
	printf("The maximum value of INT = %d\n", INT_MAX);

	printf("The minimum value of CHAR = %d\n", CHAR_MIN);
	printf("The maximum value of CHAR = %d\n", CHAR_MAX);

	printf("The minimum value of LONG = %ld\n", LONG_MIN);
	printf("The maximum value of LONG = %ld\n", LONG_MAX);
}


void exploreValidateInt(const char* buff)
{
	char* end;
	errno = 0;
	int validInt = 0;
	long intTest = strtol(buff, &end, 10);

	for (int i = 0; end[i] != '\0'; i++) {

		if (end[i] == '\n') {

			end[i] = '\0';
		}
	}

	if (end == buff) {
		fprintf(stderr, "%s: not a decimal number\n", buff);
	}
	else if ('\0' != *end) {
		fprintf(stderr, "%s: extra characters at end of input: %s\n", buff, end);
	}
	else if ((LONG_MIN == intTest || LONG_MAX == intTest) && ERANGE == errno) {
		fprintf(stderr, "%s out of range of type long\n", buff);
	}
	else if (intTest > INT_MAX) {
		fprintf(stderr, "%ld greater than INT_MAX\n", intTest);
	}
	else if (intTest < INT_MIN) {
		fprintf(stderr, "%ld less than INT_MIN\n", intTest);
	}
	else {
		validInt = (int)intTest;
		printf("%d is integer value ", validInt);
	}
}

bool intValidation(char* stringIn, int* validInt, int rangeMin, int rangeMax) {

	char* end;
	errno = 0;
	long intTest = strtol(stringIn, &end, 10);

	if ((end == stringIn) || (intTest < rangeMin) || (intTest > rangeMax) || (ERANGE == errno)){

		puts("Invalid input");
		return 0;
	}
	else{
		
		*validInt = (int)intTest;
		return 1;
	}
}
