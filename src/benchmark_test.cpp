#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void benchmark_test()
{


	system("cd /usr/local/cuda/samples/1_Utilities/p2pBandwidthLatencyTest;sudo make; sudo ./p2pBandwidthLatencyTest");
	system("cd /usr/local/cuda/samples/1_Utilities/bandwidthTest;sudo make; sudo ./bandwidthTest");
	system("nvidia-smi topo -m");
	system("gcc -O3 -DSTREAM_ARRAY_SIZE=100000 stream.c -o stream;sudo ./stream");


}
