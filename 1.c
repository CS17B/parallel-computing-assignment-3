#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void example_generator(int var[],int N)
{
	int i;
	for(i=0;i<N;i++)
	{
		var[i] = rand()%10; 
		//printf("%d   ",var[i]);  
	}
	
}

int main(int argc, char **argv)
{
  int rank;
  int np;
  int N;
  int t;
  int sum=0;
  int source,dest;
  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  N = atoi(argv[1]);
  int var[N];
  example_generator(var,N);
  int s=N/np;
  
  int offset;
  if (rank == 0) {
  	int i;
       for(i=0;i<s;i++)
       {
       	sum+=var[i];
       }
       offset=offset+s;
     
     for(dest=1;dest<np;dest++)
     {
     	
         MPI_Send(&offset,1,MPI_INT,dest,1,MPI_COMM_WORLD);
         MPI_Send(&var[offset],s,MPI_INT,dest,1,MPI_COMM_WORLD);
         offset=offset+s;
     }
     
  
     for(i=1;i<np;i++)
     {
         
        
         source =i;
         MPI_Recv(&t,1,MPI_INT,source,2,MPI_COMM_WORLD,&status);
         
         sum = sum+t;
         
     }
     printf("array sum is: %d\n",sum);
    }
     
     if(rank > 0)
     {
        source=0;
     	MPI_Recv(&offset,1,MPI_INT,source,1,MPI_COMM_WORLD,&status);
        MPI_Recv(&var[offset],s,MPI_INT,source,1,MPI_COMM_WORLD,&status);
        
        int i;
       for(i=offset;i<offset+s;i++)
       {
       	sum+=var[i];
       }
     	
         MPI_Send(&sum,1,MPI_INT,dest,2,MPI_COMM_WORLD);
         
     
     }
   	
  
   // printf("array sum is:%d\n",sum);
  
  MPI_Finalize();

  return 0;
}








