// Quinn Hackenberg
// Windows 11
// Renter Survey

#include <stdio.h>
#include <stdbool.h>

#define Surveys 5
#define Categories 3
void printCategories(const char* categories[], size_t totalCategories);
void getRatings(int rentalSurvey[][3], int renterIndex, const char* categories[], size_t totalCategories);
int getValidInt();
void printSurveyResults(int rentalSurvey[][3], size_t totalCategories);
void calculateCategoryAverages(int rentalSurvey[][3], double categoryAverages[], size_t totalCategories);
void printCategoryData(const char* categories[], double categoryAverages[], size_t totalCategories);

int main(void) {

	const char* surveyCategories[Categories] = { "Check-in Process", "Cleanliness", "Amenities" };
    int rentalSurvey[Surveys][Categories];
    double categoryAverages[Categories];
    int renterIndex = 0;

    printCategories(surveyCategories, Categories);

    for (int surveys = 0; surveys < Surveys; surveys++) {

        printf("\nRenter %d:\n", renterIndex + 1);
        getRatings(rentalSurvey, renterIndex, surveyCategories, Categories);
        renterIndex++;
    }
    printSurveyResults(rentalSurvey, Categories);

    calculateCategoryAverages(rentalSurvey, categoryAverages, Categories);
    printCategoryData(surveyCategories, categoryAverages, Categories);
}

void printCategories(const char* categories[], size_t totalCategories)
{
    //loop to display each category horizontally
    printf("%s", "Rating Categories:\t");
    for (size_t surveyCategory = 0; surveyCategory < totalCategories; ++surveyCategory){

        printf("\t%zu.%s\t", surveyCategory + 1, categories[surveyCategory]);
    }
    puts(""); // start new line of output
}

void getRatings(int rentalSurvey[][3], int renterIndex, const char* categories[], size_t totalCategories) {

    for (size_t i = 0; i < totalCategories; i++) {

        printf("Enter your rating for %s: ", categories[i]);
        rentalSurvey[renterIndex][i] = getValidInt();
    }
}

int getValidInt() {

    int userInput = 0;
    bool validInput = false;

    while (!validInput) {

        if (scanf("%d", &userInput) == true) {

            if ((userInput >= 1) && (userInput <= 5)) {

                return userInput;
                validInput = true;
            }

            else {

                printf("\nError: Input not in valid range.");
            }
        }

        else {

            puts("\nError: Input is not valid.\n");
            while ((getchar()) != '\n');
        }
    }
}

void printSurveyResults(int rentalSurvey[][3], size_t totalCategories) {
    for (int survey = 0; survey < Surveys; survey++) {

        printf("\nSurvey %d:", survey + 1);

        for (size_t surveyCategory = 0; surveyCategory < totalCategories; ++surveyCategory) {

            printf("\t%d", rentalSurvey[survey][surveyCategory]);
        }
    }
    
}

void calculateCategoryAverages(int rentalSurvey[][3], double categoryAverages[], size_t totalCategories) {

    
    for (size_t surveyCategory = 0; surveyCategory < totalCategories; ++surveyCategory) {

        int categoryTotal = 0;

        for (int survey = 0; survey < Surveys; survey++) {

            categoryTotal += rentalSurvey[survey][surveyCategory];
        }

        categoryAverages[surveyCategory] = (float)categoryTotal / Surveys;
    }
}

void printCategoryData(const char* categories[], double categoryAverages[], size_t totalCategories) {

    puts("\n");
    printCategories(categories, Categories);
    printf("Rating Averages:\t"); 

    for (size_t surveyCategory = 0; surveyCategory < totalCategories; ++surveyCategory) {

        printf("\t\t\t%.1f", categoryAverages[surveyCategory]);
    }
}