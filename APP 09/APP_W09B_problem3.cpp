/*  Name:  Charles Sirichoktanasup				  */
/*  Date:  10/22/2023     						  */
/*  Assignment:  APP_W09B					      */
/*  Seat:  00	  Instructor:  KMK   Time:  08:00 */
#include <stdio.h>
#include <math.h>
int main ( ) {
    printf ("************************************************\n");
	printf ("*  Name: Charles Sirichoktanasup Date: 10/22/23*\n");
	printf ("*  Seat:  00    File:  APP_W09B.cpp            *\n");
	printf ("*  Instructor:  KMK 08:00                      *\n");
	printf ("************************************************\n\n");
    // initialize arrays and variables to 0
    float swimTimes[6];
    float bikeTimes[6];
    float runTimes[6];
    float avgTimes[6];
    float average = 0;
    float swimTotal = 0;
    float bikeTotal = 0;
    float runTotal = 0;
    float avgTotal = 0;
    float swimMax = 0;
    float bikeMax = 0;
    float runMax = 0;
    float avgMax = 0;
    int swimMaxYear = 0;
    int bikeMaxYear = 0;
    int runMaxYear = 0;
    int avgMaxYear = 0;
    // for loop that runs for each year
    for (int i = 0; i < 6; i++) {
        // set year to the counter + 2007
        int year = i + 2007;
        // get user input for swimming, biking, running, and average speeds and store in respective arrays
        printf("\nEnter the speeds for swimming, biking, running, and the average speed for the %i Iron Man (in mph): ", year);
        scanf("%f%f%f%f", &swimTimes[i], &bikeTimes[i], &runTimes[i], &avgTimes[i]);
        // add inputted/calculated values of each metric to a variable for the total of each
        swimTotal = swimTotal + swimTimes[i];
        bikeTotal = bikeTotal + bikeTimes[i];
        runTotal = runTotal + runTimes[i];
        avgTotal = avgTotal + avgTimes[i];
        // For each list, check if current item in list is greater than the max variable for metric
        // If so, set max variable for the metric to the value of the current list item
        if (swimTimes[i] > swimMax) {
            swimMax = swimTimes[i];
            swimMaxYear = year;
        }
        if (bikeTimes[i] > bikeMax) {
            bikeMax = bikeTimes[i];
            bikeMaxYear = year;
        }
        if (runTimes[i] > runMax) {
            runMax = runTimes[i];
            runMaxYear = year;
        }
        if (avgTimes[i] > avgMax) {
            avgMax = avgTimes[i];
            avgMaxYear = year;
        }
    }
    // Calculate average value of each metric over all the years
    float swimAvg = swimTotal/6;
    float bikeAvg = bikeTotal/6;
    float runAvg = runTotal/6;
    float avgAvg = avgTotal/6;
    // Print average values and fastest values of each metric to screen
    printf("\nSwim average speed: %.2f mph", swimAvg);
    printf("\nBike average speed: %.2f mph", bikeAvg);
    printf("\nRun average speed: %.2f mph", runAvg);
    printf("\nAverage average speed: %.2f mph", avgAvg);
    printf("\nFastest year for swimming: %i (%.2f mph)", swimMaxYear, swimMax);
    printf("\nFastest year for biking: %i (%.2f mph)", bikeMaxYear, bikeMax);
    printf("\nFastest year for running: %i (%.2f mph)", runMaxYear, runMax);
    printf("\nFastest year for average speed: %i (%.2f mph)", avgMaxYear, avgMax);
    // Declare filepointer and open .txt file for writing
    FILE *fptr;
    fptr = fopen("W09B_3_result.txt ", "w");
    // Write average values and fastest values of each metric to .txt file
    fprintf(fptr, "\nSwim average: %.2f", swimAvg);
    fprintf(fptr, "\nBike average: %.2f", bikeAvg);
    fprintf(fptr, "\nRun average: %.2f", runAvg);
    fprintf(fptr, "\nAverage average: %.2f", avgAvg);
    fprintf(fptr, "\nFastest year for swimming: %i (%.2f mph)", swimMaxYear, swimMax);
    fprintf(fptr, "\nFastest year for biking: %i (%.2f mph)", bikeMaxYear, bikeMax);
    fprintf(fptr, "\nFastest year for running: %i (%.2f mph)", runMaxYear, runMax);
    fprintf(fptr, "\nFastest year for average speed: %i (%.2f mph)", avgMaxYear, avgMax);
    // close filepointer
    fclose(fptr);
}