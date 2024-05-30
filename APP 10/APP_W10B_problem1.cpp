/*  Name:  Charles Sirichoktanasup				  */
/*  Date:  10/29/2023     						  */
/*  Assignment:  APP_W10B_problem1				  */
/*  Seat:  00	  Instructor:  KMK   Time:  08:00 */

// Include imports for input/output and math
#include <stdio.h>
#include <math.h>
int main ( ) {
    // Print header
    printf ("************************************************\n");
	printf ("*  Name: Charles Sirichoktanasup Date: 10/29/23*\n");
	printf ("*  Seat:  00    File:  APP_W10B_problem1.cpp   *\n");
	printf ("*  Instructor:  KMK 08:00                      *\n");
	printf ("************************************************\n\n");

    // Declare and initialize variables
    FILE *fptr_r;
    FILE *fptr_w;
    int base = 0;
    float height = 0;
    float area = 0;
    float baseTotal = 0;
    float heightTotal = 0;
    float areaTotal = 0;
    int items = 0;
    float baseAvg = 0;
    float heightAvg = 0;
    float areaAvg = 0;

    // Initlialize file pointers for reading .txt file and writing to separate .txt file
    fptr_r = fopen("W10B_triangle.txt", "r");
    fptr_w = fopen("APP_W10B_1_result.txt", "w");

    // Set base and height variables to values in .txt file until end of file is reached
    while (fscanf(fptr_r, "%i%f", &base, &height) != EOF) {
        // Set area variable using mathematical formula
        area = (base * height) / 2;

        // Increase total variables by the current values of their respective variables
        baseTotal += base;
        heightTotal += height;
        areaTotal += area;

        // Increment items by 1
        items++;

        // Write base, height, and area to terminal and .txt file
        printf("Base: %i mm, height: %.3f mm, area: %.3f mm\n", base, height, area);
        fprintf(fptr_w, "Base: %i mm, height: %.3f mm, area: %.3f mm\n", base, height, area);
    }
    
    // Set average variables to their respective totals divided by the number of items
    baseAvg = baseTotal / items;
    heightAvg = heightTotal / items;
    areaAvg = areaTotal / items;

    // Print averages for each value and total number of triangles to terminal and .txt file
    printf("Average base length: %.3f mm,  average height: %.3f mm, average area: %.3f mm\n", baseAvg, heightAvg, areaAvg);
    printf("Number of triangles: %i", items);
    fprintf(fptr_w, "Average base length: %.3f mm,  average height: %.3f mm, average area: %.3f mm\n", baseAvg, heightAvg, areaAvg);
    fprintf(fptr_w, "Number of triangles: %i", items);
    
    // Close both file pointers
    fclose(fptr_r);
    fclose(fptr_w);
}