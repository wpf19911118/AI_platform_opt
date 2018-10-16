#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cudnn_env_test.h"
#include "python_pip_env_test.h"
#include "cuda_env_test.h"
#include "gpudriver_env_test.h"
void re_test()
{
	if(cudnn_env_test())
	{
		printf("cudnn is installed/n");
	}
	else
	{
		printf("Please Checkout the cudnn env or cudnn packages!/n");
	}
        


	python_pip_env_test();
	cuda_env_test();
	gpudriver_env_test();



}
