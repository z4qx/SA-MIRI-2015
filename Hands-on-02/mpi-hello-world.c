#include "mpi.h"
#include <stdio.h>
int main (int argc, char **argv)
{
MPI_Init (&argc, &argv);
MPI_Comm_rank ( );
MPI_Comm_size ( ); /* How many are we? */
printf ( "I am %d of %d\n", rank, size );
MPI_Finalize();
return 0;
}
