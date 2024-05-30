/************************************************/
/*  Name: Charles Sirichoktanasup Date: 11/12/23*/
/*  Seat:  00    File:  APP_W12B_1.cpp          */
/*  Instructor:  KMK 08:00                      */
/************************************************/

// Include import for input/output
#include <stdio.h>

// Struct of type student
struct Student {
    char Name[30];
    int ClassRank;
}; 

// Struct for BuckID account, which includes student information
struct BuckID_Account {
    long int ID;
    float Dollars;
    int MealBlocks;
    struct Student Personal;
}; 

// Protoype for fillstruct function
void fillstruct (struct BuckID_Account [], int );

int main ( ) {
    // Program header
    printf("************************************************\n");
    printf("*  Name: Charles Sirichoktanasup Date: 11/12/23*\n");
    printf("*  Seat:  00    File:  APP_W12B_1.cpp          *\n");
    printf("*  Instructor:  KMK 08:00                      *\n");
    printf("************************************************\n");

    // Initialize variables
    int k,n;
    struct BuckID_Account OSU[3];
    FILE *fptr;

    // Open a .txt file to write to
    fptr = fopen("APP_W12B_1.txt", "w");

    // Loop asking user to enter student data using the fillstruct function for each student in the 
    // struct array
    for ( n = 1 ; n <= 3 ; n++ ) {
        printf("\n\nEnter data for Student # %d\n", n);
        fillstruct (OSU, n - 1);
    }
    printf ("\n");

    // For each item in the array of BuckID account structs, print the input information to the terminal 
    // and to the .txt file
    for ( k = 0 ; k < 3 ; k++ ) {
        printf("%s, ID# %d,\n", OSU[k].Personal.Name, OSU[k].ID);
        printf("has a balance of $%6.2f,\n", OSU[k].Dollars); 
        printf("%d meal blocks,\n", OSU[k].MealBlocks);
        printf("and a class rank of %d\n\n", OSU[k].Personal.ClassRank);

        fprintf(fptr, "%s, ID# %d,\n", OSU[k].Personal.Name, OSU[k].ID);
        fprintf(fptr, "has a balance of $%6.2f,\n", OSU[k].Dollars); 
        fprintf(fptr, "%d meal blocks,\n", OSU[k].MealBlocks);
        fprintf(fptr, "and a class rank of %d\n\n", OSU[k].Personal.ClassRank);
    }
}

// fillstruct function, which takes an array of structs and an integer for index as parameters
void fillstruct (struct BuckID_Account a[], int j) {
    // Asks user to enter needed information and scans the information to the the specific variable 
    // in the struct
    printf ("Enter Student Name (no spaces): ");
    scanf ("%s", &a[j].Personal.Name);
    printf ("Enter BuckID Number: ");
    scanf ("%ld", &a[j].ID);
    printf ("Enter Account Balance (no '$' symbol): ");
    scanf ("%f", &a[j].Dollars);
    printf ("Enter Number of Meal Blocks: ");
    scanf ("%d", &a[j].MealBlocks);
    printf ("Enter Class Rank: ");
    scanf ("%d", &a[j].Personal.ClassRank);
}
