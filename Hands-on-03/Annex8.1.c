void Mat_vect_mult(double  A[], double  x[], double  y[], int m, int n) {
   int i, j;
   

     for (i = 0; i < m; i++) {
        y[i] = 0.0;
        for (j = 0; j < n; j++)
           y[i] += A[i*n+j]*x[j];
     }
   

