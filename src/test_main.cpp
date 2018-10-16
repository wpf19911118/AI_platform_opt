#include <stdio.h>
#include <string.h>
#include "OS_test.h"
#include "CPU_test.h"
#include "MEM_test.h"
#include "GPU_test.h"
#include "cudnn_env_test.h"
#include "python_pip_env_test.h"
#include "benchmark_test.h"
#include "reinstall.h"
#include "re_test.h"
#include "gpudriver_env_test.h"
#include "cuda_env_test.h"
#include "DISK_test.h"
#include "MAINBOARD_test.h"
#define MAXBUFSIZE 1024

struct test_result{
	char OS[1024];
	char OS_version[1024];
	unsigned int cpu_nums;
	CPU_OCCUPY *cpu_user;
	float cpu_max_fz;
	float cpu_use_fz;

};
struct test_result test_result_ubuntu;

int main(int argc ,char **argv)
{

strcpy(test_result_ubuntu.OS,"ubuntu");
OS_test(test_result_ubuntu.OS,test_result_ubuntu.OS_version);
printf("main fun OS test is %s\n",test_result_ubuntu.OS_version);

CPU_test();
printf("Hello world!\n");
MEM_test();
GPU_test();
printf("%d\n",cudnn_env_test());
python_pip_env_test();
benchmark_test();
re_test();

gpudriver_env_test();
DISK_test();
MAINBOARD_test();
cuda_env_test();
	
	
	
	return 0;
}



