#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void example_generator(int var[],int N)
{
	int i;
	for(i=0;i<N;i++)
	{
		var[i] = rand()%10;
	       
	}
	
}



int main(int argc, char **argv)
{

  int rank;
  int np;
  int N;
  
  
 
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  N = atoi(argv[1]);
  int var[N];
  example_generator(var,N);
  

  if (rank == 0) {
   	MPI_Send(var,1,MPI_INT,((rank+1) % np), 0 ,MPI_COMM_WORLD);
   	MPI_Recv(var,1,MPI_INT,np-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
  }
  else
  {
  	MPI_Recv(var,1,MPI_INT,(rank-1) , 0 , MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  	//var[0] += rank; 
  	MPI_Send(var,1,MPI_INT,((rank+1) % np) , 0 ,MPI_COMM_WORLD);
  
  }
  
  
  int i;
  for(i=0;i<N;i++)
  {
  printf("the value of var[%d]:%d and rank :%d\n",i,var[i],rank);
 }
  
  MPI_Finalize();

  return 0;
}










