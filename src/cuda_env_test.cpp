#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "cuda_env_test.h"

void cuda_env_test(){
	
	printf("CUDA Version is: \n");
	system("cat /usr/local/cuda/version.txt");
	
}
