/*  Name:  Charles Sirichoktanasup				  */
/*  Date:  11/5/2023     						  */
/*  Assignment:  APP_W11B_3     				  */
/*  Seat:  00	  Instructor:  KMK   Time:  08:00 */

// Include imports for intput/output, math, time and Windows
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

int main ( ) {
    // Print program header
    printf ("************************************************\n");
	printf ("*  Name: Charles Sirichoktanasup Date: 11/5/23 *\n");
	printf ("*  Seat:  00    File:  APP_W11B_3.cpp          *\n");
	printf ("*  Instructor:  KMK 08:00 AM                   *\n");
	printf ("************************************************\n\n");
    // declare variables for total time, time cycles, and light strings
    int total_time;
    int green_cycle;
    int yellow_cycle;
    char NS_light[7];
    char EW_light[7];

    // Get user input for total time, green light cycle, and yellow light cycle
    printf("Enter the minimum time you want to run the program (s): ");
    scanf("%i", &total_time);
    printf("Enter the time for the green cycle (s): ");
    scanf("%i", &green_cycle);
    printf("Enter the time for the yellow cycle (s): ");
    scanf("%i", &yellow_cycle);

    // Start timer
    int start = time(NULL);

    // Loop runs for at least the specified amount of total time
    while ((time(NULL) - start) < total_time) {
        // Changes NS light to green and waits for green_cycle seconds
        strcpy(NS_light, "green");
        strcpy(EW_light, "red");
        printf("North-South light: %s, East-West light: %s\n", NS_light, EW_light);
        Sleep(green_cycle * 1000);

        // Changes NS light to yellow and waits for yellow_cycle seconds
        strcpy(NS_light, "yellow");
        printf("North-South light: %s, East-West light: %s\n", NS_light, EW_light);
        Sleep(yellow_cycle * 1000);

        // Changes NS light to red and waits for green_cycle seconds
        strcpy(NS_light, "red");
        strcpy(EW_light, "green");
        printf("North-South light: %s, East-West light: %s\n", NS_light, EW_light);
        Sleep(green_cycle * 1000);

        // Changes EW light to yellow and waits for yellow_cycle seconds
        strcpy(EW_light, "yellow");
        printf("North-South light: %s, East-West light: %s\n", NS_light, EW_light);
        Sleep(yellow_cycle * 1000);
    }
}