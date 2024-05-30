/************************************************/
/*  Name: Charles Sirichoktanasup Date: 11/19/23*/
/*  Seat:  00    File:  APP_W13B_2.cpp          */
/*  Instructor:  KMK 08:00                      */
/************************************************/

// include imports for file and input/output stream
#include <fstream>
#include <iostream>
// include namespace std so standard input/output requires less work
using namespace std;

// declare class year with public constructor and methods, as well as private variables
class Year {
    public:
        Year(int y);
        void GetData();
        void FindMax();
        void Average();
        void DisplayValues();
    private:
        int y;
        int current_year, max_index;
        float year_avg, monthly_avg[12];
        char months[12][50] = {"January", "February", "March", "April", "May", "June", "July", 
        "August", "September", "October", "November", "December"};
};

int main ( ) {
    // print program header
    cout << "************************************************" << endl;
    cout << "*  Name: Charles Sirichoktanasup Date: 11/19/23*" << endl;
    cout << "*  Seat:  00    File:  APP_W13B_1.cpp          *" << endl;
    cout << "*  Instructor:  KMK 08:00                      *" << endl;
    cout << "************************************************" << endl;

    // array of size 3 and for loop to get 3 values for the current year
    int year_count[3];
    for (int i = 0; i < 3; i++) {
        // get user input for year and set Year class to the input
        cout << endl << "Enter any year between 1980 and 2007: ";  
        cin >> year_count[i];
        Year y1(year_count[i]);

        // call instance methods on class y1
        y1.GetData();
        y1.FindMax();
        y1.Average();
        y1.DisplayValues();
    }
}

Year::Year(int y) {
    // sets max_index, year_avg, and all elements of monthly_avg to 0, 
    // and sets current year to the user input
    max_index = 0;
    year_avg = 0;
    for (int i = 0; i < (sizeof(monthly_avg) / 4); i++) {
        monthly_avg[i] = 0;
    }
    current_year = y;
}

void Year::GetData() {
    // input stream declared to open .txt file to get data from
    ifstream ifstream1;
    ifstream1.open("W13B_co2data.txt");

    // get difference between current_year and 1980 (year at the beginning of file)
    int year_difference = current_year - 1980;
    int i = 0;
    // loop through file until values for right year are found, setting monthly_avg[0] to each 
    // wrong year
    while (i < year_difference * 12) {
        ifstream1 >> monthly_avg[0];
        i++;
    }
    // loop through the 12 files for the right year, declaring the values for each month to
    // the monthly_avg array
    for (int j = 0; j < 12; j++) {
        ifstream1 >> monthly_avg[j];
    }
    // close input file stream
    ifstream1.close();
}

void Year::FindMax() {
    // set float called max to the first element of monthly_avg
    float max = monthly_avg[0];

    for (int i = 0; i < (sizeof(monthly_avg) / 4); i++) {
        // loop through each item in monthly_avg and set max_index to any value higher than it
        if (monthly_avg[i] > max) {
            max = monthly_avg[i];
            max_index = i;
        }
    }
}

void Year::Average() {
    // loop through each item of monthly_avg and add to year_avg to get initial total
    year_avg = 0;
    for (int i = 0; i < (sizeof(monthly_avg) / 4); i++) {
        year_avg += monthly_avg[i];
    }
    // divide year_avg by the number of items
    year_avg /= (sizeof(monthly_avg) / 4);
}

void Year::DisplayValues() {
    // Print calculated values with context
    cout << "In " << current_year << ", the average CO2 concentration at Mauna Loa was " << year_avg 
    << " ppm." << "\nThe maximum CO2 reading was " << monthly_avg[max_index] << " in " 
    << months[max_index] << " " << current_year << endl;
}