#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include "cudnn_env_test.h"

bool cudnn_env_test()
{
	if((access("/usr/local/cuda/include/cudnn.h",0))!=-1)
	{
		printf("cudnn version is: \n");

		system("cat /usr/local/cuda/include/cudnn.h | grep CUDNN_MAJOR");
		
		system("ls /usr/local/cuda/lib64/*cudnn.so.*");

		return true;
	}	

        //else if((system("sudo find / -name cudnn.h "))!=0 && (access("/usr/local/cuda/include/cudnn.h",0))==-1)
	//{
	//	printf("cudnn is not installed");
	//	return false;
	//}

	else
	{
		printf("cudnn is not installed\n");
		return false;
	}
}
