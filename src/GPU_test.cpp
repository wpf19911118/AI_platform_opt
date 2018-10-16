
#include<stdio.h>
#include<stdlib.h>
#include "GPU_test.h"


// 
void GPU_test()
{

	printf("GPUs number is: \n");

	system("lspci | grep NVIDIA| wc -l");

	printf("GPU type is: \n");

	system("lspci | grep NVIDIA |awk '{print $(NF-5) $(NF-4) $(NF-3) $(NF-2)}'|sort|uniq");
        
	printf("GPU link pcie bandwidth is :\n");

	system("sudo lspci | grep NVIDIA |awk '{print $1}'|xargs -n 1 sudo lspci  -vvvxxx -s |grep LnkSta|sort|uniq");


}	

