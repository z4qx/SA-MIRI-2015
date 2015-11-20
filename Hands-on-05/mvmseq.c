// mvmseq.c
#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>
#include <time.h>

void Read_matrix(char prompt[], double A[], int m, int n);
void Read_vector(char prompt [], double x[], int n);
void Mat_vect_mult(double A[], double x[], double y[], int m, int n);

struct timeval start_time, end_time;

int main(int argc, char *argv[]) {
   double* A = NULL;
   double* x = NULL;
   double* y = NULL;
   long long int size;
   int m, n;

   n= atoi(argv[1]);
   m= n;

   size=m*n*sizeof(double);
   A = malloc(size);
   x = malloc(n*sizeof(double));
   y = malloc(m*sizeof(double));
   
   Read_matrix("A", A, m, n);
   Read_vector("x", x, n);

   gettimeofday(&start_time, NULL);

   Mat_vect_mult(A, x, y, m, n);

   gettimeofday(&end_time, NULL);
   print_times();

   free(A);
   free(x);
   free(y);
   return 0;
}  /* main */

void Read_matrix(char    prompt[], double  A[], int m, int n) {
   int i, j;
for (i = 0; i < m; i++)
      for (j = 0; j < n; j++)
              A[i*n+j]=rand();
}  

void Read_vector( char    prompt[], double x[], int n) {
   int i;
for (i = 0; i < n; i++)
     x[i]=rand();
} 

void Mat_vect_mult(double  A[], double  x[], double  y[], int m, int n) {
   int i, j, jj;
   
   for (jj = 0; jj < 1000; jj++) {

     for (i = 0; i < m; i++) {
        y[i] = 0.0;
        for (j = 0; j < n; j++)
           y[i] += A[i*n+j]*x[j];
     }
   }
} 

print_times()
{
   int total_usecs;
   float total_time, total_flops;
   total_usecs = (end_time.tv_sec-start_time.tv_sec) * 1000000 +
         (end_time.tv_usec-start_time.tv_usec);
   printf(" %.2f mSec \n", ((float) total_usecs) / 1000.0);
   total_time = ((float) total_usecs) / 1000000.0;
}


