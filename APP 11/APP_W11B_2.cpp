/*  Name:  Charles Sirichoktanasup				  */
/*  Date:  11/5/2023     						  */
/*  Assignment:  APP_W11B_2     				  */
/*  Seat:  00	  Instructor:  KMK   Time:  08:00 */

// Include imports for input/output, math, and strings
#include <stdio.h>
#include <math.h>
#include <string.h>
// Prototypes for functions used
float mydot(float input_vector1[], float input_vector2[]);
void mycross(float input_vector1[], float input_vector2[], float output_vector[]);

int main ( ) {
    // Print program header
    printf ("************************************************\n");
	printf ("*  Name: Charles Sirichoktanasup Date: 11/5/23 *\n");
	printf ("*  Seat:  00    File:  APP_W11B_2.cpp          *\n");
	printf ("*  Instructor:  KMK 08:00 AM                   *\n");
	printf ("************************************************\n");
    // Declare variables, initialize running variable to "y" so program runs at least once
    int item_count;
    char mode[] = "";
    float vector1[3];
    float vector2[3];
    float vector3[3];
    char running[] = "y";
    FILE *fptr;
    // Set file pointer to .txt file to write to
    fptr = fopen("APP_W11B_2_result.txt", "w");
    // Repeats program while running = "y"
    while (strcmp(running, "y") == 0) {
        // Gets 3 floats as items for the first vector
        for (int i = 0; i < 3; i++) {
            printf("\nEnter an int for item %i of vector 1: ", i + 1);
            scanf("%f", &vector1[i]);
        }
        // Gets 3 floats as items for the second vector
        for (int j = 0; j < 3; j++) {
            printf("\nEnter an int for item %i of vector 2: ", j + 1);
            scanf("%f", &vector2[j]);
        }
        // Asks user what product they want and store response in mode variable
        printf("\nEnter 'D'/'d' to get the dot product or 'C'/'c' to get the cross product of the 2 arrays: ");
        scanf("%s", &mode);
        if (strcmp(mode, "D") == 0 || strcmp(mode, "d") == 0) {
            // If user wants to get dot product, call dot product function on the 2 vectors
            float dot_product = mydot(vector1, vector2);
            // Print 2 vectors and resulting dot product to terminal and .txt file
            printf("\nVector 1: %.2f, %.2f, %.2f\n", vector1[0], vector1[1], vector1[2]);
            printf("Vector 2: %.2f, %.2f, %.2f\n", vector2[0], vector2[1], vector2[2]);
            printf("Dot product: %.2f\n\n", dot_product);
            fprintf(fptr, "Vector 1: %.2f, %.2f, %.2f\n", vector1[0], vector1[1], vector1[2]);
            fprintf(fptr, "Vector 2: %.2f, %.2f, %.2f\n", vector2[0], vector2[1], vector2[2]);
            fprintf(fptr, "Dot product: %.2f\n\n", dot_product);
        } else if (strcmp(mode, "C") == 0 || strcmp(mode, "c") == 0) {
            // If user wants to get cross product, 
            mycross(vector1, vector2, vector3);
            // Print original 2 vectors and cross product vector to terminal and .txt file
            printf("\nVector 1: %.2f, %.2f, %.2f\n", vector1[0], vector1[1], vector1[2]);
            printf("Vector 2: %.2f, %.2f, %.2f\n", vector2[0], vector2[1], vector2[2]);
            printf("Cross product: %.2f, %.2f, %.2f\n\n", vector3[0], vector3[1], vector3[2]);
            fprintf(fptr, "Vector 1: %.2f, %.2f, %.2f\n", vector1[0], vector1[1], vector1[2]);
            fprintf(fptr, "Vector 2: %.2f, %.2f, %.2f\n", vector2[0], vector2[1], vector2[2]);
            fprintf(fptr, "Cross product: %.2f, %.2f, %.2f\n\n", vector3[0], vector3[1], vector3[2]);
        }
        // Asks user if they want to run program again and scan response to mode variable
        printf("Enter 'y' to run the program again: ");
        scanf("%s", &running);
        printf("\n");
    }
    fclose(fptr);
}

// Function that returns the dot product of the two vectors inputted
float mydot(float input_vector1[], float input_vector2[]) {
    // Initialize output to 0
    float output = 0;
    // Adds the product of items of same index of the 2 vectors to output
    for (int k = 0; k < 3; k++) {
        output += (input_vector1[k] * input_vector2[k]);
    }
    // Return output, equal to dot product of the 2 vectors
    return output;
}

// Function that sets output vector the the cross product of the 2 input vectors
void mycross(float input_vector1[], float input_vector2[], float output_vector[]) {
    // Calculations are done for each element of the output vector using elements of input vectors
    output_vector[0] = input_vector1[1] * input_vector2[2] - input_vector1[2] * input_vector2[1];
    output_vector[1] = input_vector1[2] * input_vector2[0] - input_vector1[0] * input_vector2[2];
    output_vector[2] = input_vector1[0] * input_vector2[1] - input_vector1[1] * input_vector2[0];
}
