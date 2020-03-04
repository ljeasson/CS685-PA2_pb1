//#include <fstream.h>
//#include <iostream.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <math.h>

extern "C" void solve_system(int, int, float**, float*, float*); 

int main(int argc, char* argv[])
{
 int i;
 int m, n;
 float **a, *x, *b;

 // Set m to the number of equations 
 // Set n to the number of unknowns
 
 a = new float* [m+1];
 for(i=0; i<m+1; i++)
   a[i] = new float [n+1];

 x = new float [n+1];

 b = new float [m+1];

 // Fill matrix a and vector b with the desired values
 // The values should be placed at indices 1..m, 1..n

 solve_system(m,n,a,x,b);

 // The solution is now in vector x, at indices 1..n 
}