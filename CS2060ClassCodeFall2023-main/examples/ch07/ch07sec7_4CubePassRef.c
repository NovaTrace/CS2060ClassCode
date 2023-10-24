// Passing Primitive Data Types and pointers
//Add comments to explain the code

#include <stdio.h>	
#include <stdlib.h>

int cubePass1(int number);
int cubePass2(int * numberPtr);

#define RENTER_SURVEY_CATEGORIES 3
int main(void) {

	int numberMain = 5;
	int result = 0;
	
	const char* surveyCategories[RENTER_SURVEY_CATEGORIES] = { "Check-in Process", "Cleanliness", "Amenities" };

	for (int i = 0; i < RENTER_SURVEY_CATEGORIES; i++) {

		puts(surveyCategories[i]);
	}

	printf ("In main before cubePass1  numberMain = %d\n", numberMain);
	printf("&numberMain = %p\n", &numberMain);
	result = cubePass1(numberMain);
	printf ("In main after cubePass1  numberMain = %d\n", numberMain);
	printf ("Result = %d\n", result);
	printf("\nIn main before cubePass2  numberMain = %d\n", numberMain);
	result = cubePass2(&numberMain);
	printf("\nIn main after cubePass2  numberMain = %d\n", numberMain);
	printf("result = %d\n", result);

} // main

//Passes variable by value
int cubePass1 (int number) 
{
	int cube = 0;
	puts("\nIn cubePass1");
	printf("number = %d\n", number);
	//number in cubePass1 has different address than numberMain
	printf("&number = %p\n", &number);
	cube = number * number * number;
	printf("cube  = %d\n", cube);
	number = cube;
	printf("number = %d\n", number);
	return cube;
} 

//passes the address of the variable
//effectively is now pass by reference
int cubePass2 (int * numberPtr) 
{
	int cube = 0;
	puts ("\nIn cubePass2");
	//Same address as numberMain
	printf("numberPtr = %p\n", numberPtr);
	printf ("*numberPtr = %d\n", *numberPtr);
	//Same address as number in cubePass1 | unsure why
	printf("&numberPtr = %p\n", &numberPtr);
	cube = (* numberPtr )* (* numberPtr )* (* numberPtr); 
	*numberPtr = cube;
	printf ("*numberPtr = %d\n", *numberPtr);
	return cube;
} 


