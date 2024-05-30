/*  Name:  Charles Sirichoktanasup				  */
/*  Date:  10/29/2023     						  */
/*  Assignment:  EWA_06						  */
/*  Seat:  00	  Instructor:  KMK   Time:  08:00 */

// Include standard input/output and math imports
#include <stdio.h>
#include <math.h>

int main ( ) {
    // Print header
    printf ("************************************************\n");
	printf ("*  Name: Charles Sirichoktanasup Date: 10/29/23*\n");
	printf ("*  Seat:  00    File:  EWA_06.cpp              *\n");
	printf ("*  Instructor:  KMK 08:00                      *\n");
	printf ("************************************************\n\n");

    // Create variables and initialize constants / counters
    float v_out;
    float first_v_out;
    float max_v_out;
    float min_v_out;
    float time_elapsed = 0;
    float strain_max;
    float strain_min;
    float input_voltage = 5.0;
    float amplification = 500;
    float gage_factor = 2.085;
    FILE *fptr_r;
    FILE *fptr_w;

    // Initialize file pointers for reading .txt file and writing to a separate .txt file
    fptr_r = fopen("W10B_bike.txt", "r");
    fptr_w = fopen("APP_W10B_3_result.txt", "w");

    // Scan the first item of W10B_bike.txt to variable first_v_out
    fscanf(fptr_r, "%f", &first_v_out);

    // Set min and max voltage change variables to first_v_out
    max_v_out = first_v_out;
    min_v_out = first_v_out;

    // Set voltage change variable to current index in file until end of file is reached
    while (fscanf(fptr_r, "%f", &v_out) != EOF) {
        // Increase time elapsed by 0.005 seconds
        time_elapsed += 0.005;

        // Set voltage change to the difference between the current voltage change and first voltage
        v_out = v_out - first_v_out;

        // If current voltage is greater than max voltage, set max voltage to the current voltage
        if (v_out > max_v_out) {
            max_v_out = v_out;
        }

        // If current voltage is less than min voltage, set min voltage to the current voltage
        if (v_out < min_v_out) {
            min_v_out = v_out;
        }
    }

    // Close file pointer for reading .txt file
    fclose(fptr_r);

    // Calculate strains for min and max voltages
    strain_max = max_v_out / (input_voltage * amplification * gage_factor);
    strain_min = min_v_out / (input_voltage * amplification * gage_factor);

    // Print min and max output voltages, time elapsed, and min and max strain to terminal
    printf("Min. change in voltage: %.3f volts\n", min_v_out);
    printf("Max. change in voltage: %.3f volts\n", max_v_out);
    printf("Time elapsed: %.3f seconds\n", time_elapsed);
    printf("Min strain: %f\n", strain_min);
    printf("Max strain: %f\n", strain_max);

    // Write min and max output voltages, time elapsed, and min and max strain to .txt file
    fprintf(fptr_w, "Min. change in voltage: %.3f volts\n", min_v_out);
    fprintf(fptr_w, "Max. change in voltage: %.3f volts\n", max_v_out);
    fprintf(fptr_w, "Time elapsed: %.3f seconds\n", time_elapsed);
    fprintf(fptr_w, "Min strain: %f\n", strain_min);
    fprintf(fptr_w, "Max strain: %f\n", strain_max);

    // Close file pointer for writing
    fclose(fptr_w);
}