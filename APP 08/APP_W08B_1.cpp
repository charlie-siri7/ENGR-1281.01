/*  Name:  Charles Sirichoktanasup				  */
/*  Date:  10/14/2023     						  */
/*  Assignment:  APP W08B-1						  */
/*  Seat:  00	  Instructor:  KMK   Time:  08:00 */

#include  <stdio.h>
#include  <math.h>
int main ( )
{
	printf ("************************************************\n");
	printf ("*  Name: Charles Sirichoktanasup Date: 10/16/23*\n");
	printf ("*  Seat:  00    File:  APP_W08B_2.cpp          *\n");
	printf ("*  Instructor:  KMK 08:00                      *\n");
	printf ("************************************************\n\n");
	// declare ints and floats
	int a, b, c ;
	float w, x, y = 2, z ;
	// assign values to ints and floats
	int e = 8, f = 0.50, g = 1, h = 10.999 ;
	float q = 6, r = .75, s = 7, t = 9/4 ;
	// Expressions to change variables, guess for the result, 
	// and printing the result
	w = g / e - 110 * f;	   	 	/* w = _____0.125_____*/
    printf("%f\n",w);
	w += h;					/* w = _____10.125_____*/
    printf("%f\n",w);
	a = t + pow (g, q);			/* a = _____3_____*/
    printf("%d\n",a);
	b = --w + t;					/* b = _____11_____*/
    printf("%d\n",b);
	x = h % e++;					/* x = _____2_____*/
    printf("%f\n",x);
	y = (e + w) * y;				/* y = _____36.25_____*/
    printf("%f\n",y);
	c = (++s);					/* c = _____8_____*/
    printf("%d\n",c);
	z = r * s + h / e + q;			/* z = _____12.5_____*/
    printf("%f\n",z);
    h = pow (c,2);                    /* h = _____64_____*/
    printf("%d\n",h);
}
