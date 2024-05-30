#include <stdio.h>
#include <math.h>
int main ( ) {
    float a, b, c, avg;
    float *ptr_a = &a;
    float *ptr_b = &b;
    float *ptr_c = &c;
    float *ptr_avg = &avg;
    printf("Enter 3 numbers: ");
    scanf("%f%f%f", ptr_a, ptr_b, ptr_c);
    *ptr_avg = (*ptr_a + *ptr_b + *ptr_c) / 3;
    printf("Average: %f\n", *ptr_avg);
    printf("Absolute values: %f, %f, %f\n", fabs(*ptr_a), fabs(*ptr_b), fabs(*ptr_c));
    printf("Value of a: %f, address of a: %i\n", *ptr_a, ptr_a);
}