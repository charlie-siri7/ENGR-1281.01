/*  Name:  Charles Sirichoktanasup				  */
/*  Date:  11/5/2023     						  */
/*  Assignment:  APP_W11B_1     				  */
/*  Seat:  00	  Instructor:  KMK   Time:  08:00 */

// Include imports for input/output, math, and strings
#include <stdio.h>
#include <math.h>
#include <string.h>

int main ( ) {
    // Print program header
    printf ("************************************************\n");
	printf ("*  Name: Charles Sirichoktanasup Date: 11/5/23 *\n");
	printf ("*  Seat:  00    File:  APP_W11B_1.cpp          *\n");
	printf ("*  Instructor:  KMK 08:00 AM                   *\n");
	printf ("************************************************\n\n");
    // Declare and initialize files for filepointer for reading and writing
    FILE *fptr_r;
    FILE *fptr_w;
    fptr_r = fopen("W11B_bloodtypes.txt", "r");
    fptr_w = fopen("APP_W11B_1_result.txt", "w");
    // Declare strings for name and bloodtype
    char name[40];
    char bloodtype[5];
    // declare 2D char array to store names of participants with AB+ bloodtype
    char ab_plus_array[40][40];
    // Declare and initialize all bloodtype counters to 0
    int a_plus_counter = 0;
    int o_plus_counter = 0;
    int b_plus_counter = 0;
    int ab_plus_counter = 0;
    int a_minus_counter = 0;
    int o_minus_counter = 0;
    int b_minus_counter = 0;
    int ab_minus_counter = 0;
    // Loop through each line of file until end is reached
    while (fscanf(fptr_r, "%s%s", name, bloodtype) != EOF) {
        // If a certain bloodtype is read, increment its respective counter by 1
        if (strcmp(bloodtype, "A+") == 0) {
            a_plus_counter++;
        }
        if (strcmp(bloodtype, "O+") == 0) {
            o_plus_counter++;
        }
        if (strcmp(bloodtype, "B+") == 0) {
            b_plus_counter++;
        }
        if (strcmp(bloodtype, "AB+") == 0) {
            // If AB+ bloodtype is read, copy the name of the participant into 2D char array
            strcpy(ab_plus_array[ab_plus_counter], name);
            ab_plus_counter++;
        }
        if (strcmp(bloodtype, "A-") == 0) {
            a_minus_counter++;
        }
        if (strcmp(bloodtype, "O-") == 0) {
            o_minus_counter++;
        }
        if (strcmp(bloodtype, "B-") == 0) {
            b_minus_counter++;
        }
        if (strcmp(bloodtype, "AB-") == 0) {
            ab_minus_counter++;
        }
    }
    // Print total count of participants of each bloodtype
    printf("# of participants with A+ bloodtype: %i\n", a_plus_counter);
    printf("# of participants with O+ bloodtype: %i\n", o_plus_counter);
    printf("# of participants with B+ bloodtype: %i\n", b_plus_counter);
    printf("# of participants with AB+ bloodtype: %i\n", ab_plus_counter);
    printf("# of participants with A- bloodtype: %i\n", a_minus_counter);
    printf("# of participants with O- bloodtype: %i\n", o_minus_counter);
    printf("# of participants with B- bloodtype: %i\n", b_minus_counter);
    printf("# of participants with AB- bloodtype: %i\n\n", ab_minus_counter);

    // Print label of participants with AB+ bloodtype to terminal and .txt file
    printf("Names of participants with AB+ bloodtype:\n");
    fprintf(fptr_w, "Names of participants with AB+ bloodtype:\n");
    // Prints each name in 2D array to terminal and .txt file
    for (int i = 0; i < ab_plus_counter; i++) {
        printf("%s\n", ab_plus_array[i]);
        fprintf(fptr_w, "%s\n", ab_plus_array[i]);
    }
    fclose(fptr_r);
    fclose(fptr_w);
}