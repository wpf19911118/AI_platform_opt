#include<stdio.h>
#include<stdlib.h>
#include<sys/sysinfo.h>
#include "MEM_test.h"

void MEM_test()
{

struct sysinfo si;
sysinfo(&si);
float totalRAM,freeRAM;
totalRAM=float(si.totalram)/(1024.0*1024*1024);
freeRAM=float(si.freeram)/(1024.0*1024*1024);

//system("ls -alF");
system("free -h >>tmp.txt ");
system("tail -3 tmp.txt ");
system("rm -rf ./tmp.txt");

//内存条数量
printf("total number of the memory is: \n");

system("sudo dmidecode -t memory| grep 'Memory Device'|wc -l" );
printf("memory type is: \n");
system("sudo dmidecode -t memory | grep Manufacturer |sort |uniq");
printf("size & speed & Type: \n");
system("sudo dmidecode -t memory | grep -E 'Size:|Type:|Speed:'|sort|uniq");
printf("Maximum Capacity is: \n");
system("sudo dmidecode -t memory | grep 'Maximum Capacity'|uniq");


printf("Totalram:       %f\n", totalRAM);
printf("Available:      %f\n", freeRAM);


}
