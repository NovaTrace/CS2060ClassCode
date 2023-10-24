/*******************
 Understanding pointers

 Add comments to explain the code
**************/

#include <stdio.h>


int main ()
{
	// Initalize houseNum
	int houseNum = 13;
	int calcHouseNum1 = 0;
	int calcHouseNum2 = 0;
	int *houseNumPtr = &houseNum;
	
	//Prints the value of houseNum
	printf("houseNum %d\n", houseNum);

	//Prints the address of houseNum
	printf("&houseNum %p\n\n", &houseNum);

	//Prints the value at the address stored in houseNumPtr which is the address of houseNum
	printf ("*houseNumPtr  %d\n", *houseNumPtr);

	//Prints the address stored in houseNumPtr
	printf ("houseNumPtr %p\n\n", houseNumPtr);

	//Prints the address of the variable houseNumPtr. aka the address where the address of houseNum is stored
	printf ("&houseNumPtr %p\n\n", &houseNumPtr);

	//Adds together the values at the address pointed to
	calcHouseNum1 =  *houseNumPtr + *houseNumPtr;

	//Prints the value of calcHouseNum1
	printf("*houseNumPtr + *houseNumPtr is %d\n\n", calcHouseNum1);
	
	//Multiplies the value at the address pointed to by 2
	calcHouseNum2 = 2 * (*houseNumPtr);

	//Prints the value of calHouseNum2
	printf("2 * (*houseNumPtr) is %d\n\n", calcHouseNum2);

	//The & and the * cancel out by getting the value pointedto by the address or vice versa
	printf("\n&*houseNumPtr = %p"
		"\n*&houseNumPtr = %p\n", &*houseNumPtr, *&houseNumPtr);
			
	return 0;
}
