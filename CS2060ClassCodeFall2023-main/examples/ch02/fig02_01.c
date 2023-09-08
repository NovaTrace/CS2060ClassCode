// fig02_01.c
// A first program in C.
#include <stdio.h>



// function main begins program execution 
int main(void) {

	int length = 0;
	int width = 0;
	int area = 0;


   printf("Welcome to C!\n");

   // Part 1
   puts("Enter the length");
   scanf("%d", &length);

   puts("Enter the width");
   scanf("%d", &width);

   area = length * width;
   printf("Length: %d Width: %d and the area is %d\n", length, width, area);

   // Part 3
   double valueAverage = ((double)length + width) / 2;
   printf("Average is: %.1f\n", valueAverage);

   //Part 6
   double calculatedArea = calculateArea(length, width);
   printf("Calculated area is: %.1f\n", calculatedArea);


  // return; //!!!//

} // end function main 

double calculateArea(double dLength, double dWidth) {

	double dArea = (dLength * dWidth);
	printf("Double area is: %.1f\n", dArea);
	return dArea;
}


/**************************************************************************
 * (C) Copyright 1992-2021 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/
