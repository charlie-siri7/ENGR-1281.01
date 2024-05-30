/*  Name:  Charles Sirichoktanasup				  */
/*  Date:  10/22/2023     						  */
/*  Assignment:  APP_W09B					      */
/*  Seat:  00	  Instructor:  KMK   Time:  08:00 */
#include  <stdio.h>
#include  <math.h>
int main ( ) {
    printf ("************************************************\n");
	printf ("*  Name: Charles Sirichoktanasup Date: 10/22/23*\n");
	printf ("*  Seat:  00    File:  APP_W09B.cpp            *\n");
	printf ("*  Instructor:  KMK 08:00                      *\n");
	printf ("************************************************\n\n");
    // declare variable to store fl. oz.
    float ounces;
    // ask user for volume and store in fl. oz. variable
    printf("Enter a volume in fluid ounces: ");
    scanf("%f", &ounces);
    // declare variables of different units with volumes from the conversion of fl. oz.
    float cups = ounces * (1.0/8);
    float tbsp = ounces * 2;
    float tsp = ounces * 6;
    float quarts = cups * (1.0/4);
    float pints = cups * (1.0/2);
    float gallons = quarts * (1.0/4);
    // print the input volume and output volumes of different units
    printf("Input volume: %.2f fl. oz.\n", ounces);
    printf("Output volume: %.2f cups\n", cups);
    printf("Output volume: %.2f gallons\n", gallons);
    printf("Output volume: %.2f quarts\n", quarts);
    printf("Output volume: %.2f pints\n", pints);
    printf("Output volume: %.2f tablespoons\n", tbsp);
    printf("Output volume: %.2f teaspoons\n", tsp);
    // declare file pointer and open .txt file for writing
    FILE *filepointer;
    filepointer = fopen("W09B_2_result.txt", "w");
    // print input/output volumes with different units to .txt file
    fprintf(filepointer, "Input volume: %.2f fl. oz.\n", ounces);
    fprintf(filepointer, "Output volume: %.2f cups\n", cups);
    fprintf(filepointer, "Output volume: %.2f gallons\n", gallons);
    fprintf(filepointer, "Output volume: %.2f quarts\n", quarts);
    fprintf(filepointer, "Output volume: %.2f pints\n", pints);
    fprintf(filepointer, "Output volume: %.2f tablespoons\n", tbsp);
    fprintf(filepointer, "Output volume: %.2f teaspoons\n", tsp);
    // close file pointer
    fclose(filepointer);
}