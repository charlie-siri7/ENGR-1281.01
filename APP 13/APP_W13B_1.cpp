/************************************************/
/*  Name: Charles Sirichoktanasup Date: 11/19/23*/
/*  Seat:  00    File:  APP_W13B_1.cpp          */
/*  Instructor:  KMK 08:00                      */
/************************************************/

// include imports for file stream, in/out stream, strings, and math
#include <fstream>
#include <iostream>
#include <string.h>
#include <math.h>
// use std so standard input/output requires less work
using namespace std;

int main( ) {
    // print program header
    cout << "************************************************\n" << endl;
    cout << "*  Name: Charles Sirichoktanasup Date: 11/19/23*\n" << endl;
    cout << "*  Seat:  00    File:  APP_W13B_1.cpp          *\n" << endl;
    cout << "*  Instructor:  KMK 08:00                      *\n" << endl;
    cout << "************************************************\n" << endl;

    // declare variables and arrays
    ifstream ifstream1;
    ofstream ofstream1;
    float triangleArray[5][2];
    int triangleNum;
    float base;
    float height;
    char mode[10];
    float height[ 3 ] = {5.6 6.4 5.9};
    float height[ ] = {5.6, 6.4, 5.9}; 
    float height[ 3 ]; 
    float height[ ];

    // set running string to "y" so the program runs at least once
    char running[10] = "y";

    // open a file for reading and a file for writing
    ifstream1.open("W13B_triangle.txt");
    ofstream1.open("APP_W13B_1_result.txt", fstream::app);

    // input the data from the input file into triangleArray using for loop
    for (int i = 0; i < 5; i++) {
        ifstream1 >> triangleArray[i][0] >> triangleArray[i][1];
    }

    // repeat the program until running string doesn't equal "y"
    while (strcmp(running, "y") == 0) {
        // get user input for triangle number
        cout << "Enter the number of the triangle to perform a computation on: ";
        cin >> triangleNum;

        // decrement triangleNum by 1 so the correct array index is used
        triangleNum--;

        // get base and height from array, calculate hypotenuse with given base and height
        base = triangleArray[triangleNum][0];
        height = triangleArray[triangleNum][1];
        float hypotenuse = pow(base, 2) + pow(height, 2);
        hypotenuse = pow(hypotenuse, 0.5);

        // get user input for which triangle value they want to calculate
        cout << endl << "Enter 'P' to get the perimeter, 'A' to get the area," << endl << 
        "or 'H' to get the hypotenuse (can be upper or lower case): ";
        cin >> mode;

        if (strcmp(mode, "P") == 0 || strcmp(mode, "p") == 0) {
            // if user wants perimeter, calculate perimeter and print base, height, and perimeter of
            // the triangle to the terminal and the output file
            float perimeter = base + height + hypotenuse;
            cout << endl << "Base of triangle: " << base << " m";
            cout << endl << "Height of triangle: " << height << " m";
            cout << endl << "Perimeter of triangle: " << perimeter << " m";
            ofstream1 << "Base of triangle: " << base << " m" << endl;
            ofstream1 << "Height of triangle: " << height << " m" << endl;
            ofstream1 << "Perimeter of triangle: " << perimeter << " m" << endl;
        } else if (strcmp(mode, "A") == 0 || strcmp(mode, "a") == 0) {
            // if user wants area, calculate area and print base, height, and area of
            // the triangle to the terminal and the output file
            float area = (base * height) / 2;
            cout << endl << "Base of triangle: " << base << " m";
            cout << endl << "Height of triangle: " << height << " m";
            cout << endl << "area of triangle: " << area << " m^2";
            ofstream1 << "Base of triangle: " << base << " m" << endl;
            ofstream1 << "Height of triangle: " << height << " m" << endl;
            ofstream1 << "Area of triangle: " << area << " m^2" << endl;
        } else if (strcmp(mode, "H") == 0 || strcmp(mode, "h") == 0) {
            // if user wants hypotenuse, get hypotenuse and print base, height, and hypotenuse of
            // the triangle to the terminal and the output file
            cout << endl << "Base of triangle: " << base << " m";
            cout << endl << "Height of triangle: " << height << " m";
            cout << endl << "Hypotenuse of triangle: " << hypotenuse << " m";
            ofstream1 << "Base of triangle: " << base << " m" << endl;
            ofstream1 << "Height of triangle: " << height << " m" << endl;
            ofstream1 << "Hypotenuse of triangle: " << hypotenuse << " m" << endl;
        } else {
            // if the user enters anything besides the accepted characters, tell them that their 
            // input is invalid
            cout << endl << "ERROR: CHARACTER IS NOT A VALID OPERATION.";
        }
        // get user input for if they want to rerun the program
        ofstream1 << endl;
        cout << endl << endl << "Enter 'y' if you want to run the program again: ";
        cin >> running;
        cout << endl;
    }
    // after program concludes, close input and output streams
    ifstream1.close();
    ofstream1.close();
}