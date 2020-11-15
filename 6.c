#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


void example_generator(int var[],int N)
{
	int i;
	for(i=0;i<N;i++)
	{
		var[i] = rand()%10;
	       // printf("%d  ",var[i]);
	}
	//printf("\n");
}

int main(int argc, char **argv) {
  int N; 
  N=atoi(argv[1]);
  int var[N];
  int i;
  int x = 0;
  example_generator(var,N);

  { 
#pragma omp for             
    for (i = 0; i < N; i++) {
        x+=var[i];
    }
  }

    printf("%d\n", x);
  
  return 0;
}

