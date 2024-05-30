/*  Name:  Charles Sirichoktanasup				  */
/*  Date:  10/29/2023     						  */
/*  Assignment:  APP_W10B_2_mod 				  */
/*  Seat:  00	  Instructor:  KMK   Time:  08:00 */

// Include imports for input/output and math
#include <stdio.h>
#include <math.h>
int main ( ) {
    // Print header
    printf ("************************************************\n");
	printf ("*  Name: Charles Sirichoktanasup Date: 10/29/23*\n");
	printf ("*  Seat:  00    File:  APP_W10B_2_mod.cpp      *\n");
	printf ("*  Instructor:  KMK 08:00                      *\n");
	printf ("************************************************\n\n");
    // Declare variables and initialize pointers to the references of these variables
    float a, b, c, avg;
    float *ptr_a = &a;
    float *ptr_b = &b;
    float *ptr_c = &c;
    float *ptr_avg = &avg;
    // Prompt user to enter 3 numbers
    printf("Enter 3 numbers: ");
    // Scan numbers to pointer variables
    scanf("%f%f%f", ptr_a, ptr_b, ptr_c);
    // Set the dereferenced pointer of average to the sum of the dereferenced pointers of the sum of
    // a, b, and c divided by 3
    *ptr_avg = (*ptr_a + *ptr_b + *ptr_c) / 3;
    // Print average value, absolute values of each item, and value/address of a using dereferenced 
    // pointers to terminal
    printf("Average: %.2f\n", *ptr_avg);
    printf("Absolute values: %.2f, %.2f, %.2f\n", fabs(*ptr_a), fabs(*ptr_b), fabs(*ptr_c));
    printf("Value of a: %.2f, address of a: %i\n\n", *ptr_a, ptr_a);
    // Ask user to enter 3 numbers...again.
    printf("Enter 3 numbers: ");
    // Scan 3 numbers to floats a, b, and c using referencing
    scanf("%f%f%f", &a, &b, &c);
    // Set average variable to the sum of a, b, and c divided by 3.
    avg = (a + b + c) / 3;
    // Print average value, absolute values of each item, and value/address of a using float variables
    // with referencing as needed to terminal
    printf("Average: %.2f\n", avg);
    printf("Absolute values: %.2f, %.2f, %.2f\n", fabs(a), fabs(b), fabs(c));
    printf("Value of a: %.2f, address of a: %i\n", a, &a);
}