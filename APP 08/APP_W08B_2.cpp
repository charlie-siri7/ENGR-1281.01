/*  Name:  Charles Sirichoktanasup				  */
/*  Date:  10/14/2023     						  */
/*  Assignment:  APP W08B-2						  */
/*  Seat:  00	  Instructor:  KMK   Time:  08:00 */

#include  <stdio.h>
#include  <math.h>
int main () 
{
    // Declare float variables for height and base as constants
    float h = 3;
    float b = 2 * h;
    // Set value of float I using inertia formula
    float I = (b * pow(h, 3)) / 12;
    // Print base and height of rectangle to screen with units
    printf("A rectangle with b = %6.2f in and h = %6.2f in\n", b, h);
    // Print inertia of rectangle to screen with units
    printf("has an area moment of inertia of I = %6.2f in^4\n", I);
}