#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void example_generator(int var[],int g,int h)
{
	int i;
	for(i=g;i<h;i++)
	{
		var[i] = i; 
		//printf("%d   ",var[i]);  
	}
	//printf("\n");
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
  int e=(N/np)*rank;
  int p=(N/np)*rank+(N/np);
  example_generator(var,e,p);
  int s=N/np;
  
  int offset;
  if (rank == 0) {
  	int i;
       for(i=0;i<s;i++)
       {
       	sum+=var[i];
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
       
        int i;
       for(i=e;i<p;i++)
       {
       	sum+=var[i];
       }
     	
         MPI_Send(&sum,1,MPI_INT,dest,2,MPI_COMM_WORLD);
         
     
     }
   	
  
   // printf("array sum is:%d\n",sum);
  
  MPI_Finalize();

  return 0;
}








