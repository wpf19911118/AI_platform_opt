#include <stdio.h>
#include <stdlib.h>


void reinstall()
{


	if (1)
	{
		system("sudo sh cuda_9.2.88_396.26_linux.run --silent --toolkit --samples --driver");

	}
	else
	{
		printf("cuda & driver is installed!\n");
	}
	if(1)
	{
		system("tar -xvf cudnn-9.0-linux-x64-v7.1.tar");
		system("sudo cp cuda/include/cudnn.h  /usr/local/cuda/include");
		system("sudo cp cuda/lib64/libcudnn*  /usr/local/cuda/lib64;cd /usr/local/cuda/lib64; rm libcudnn.so libcudnn.so.7;sudo ln -s libcudnn.so.7.0.5 libcudnn.so.7;sudo ln -s libcudnn.so.7 libcudnn.so ");

	}
	else
	{
		printf("cudnn 7 is installed!\n");
	}
	if(1)
	{
		system("sudo yum install -y epel-release; yum install -y numpy swig python-devel python-wheel python-pip patch enum34 mock protobuf");
	
	}
	else
	{
		printf("python & pip is installed!\n");
	}

	if(1)
	{
		system("wget -O /etc/yum.repos.d/CentOS-Base.repo http://mirrors.aliyun.com/repo/Centos-7.repo");
		system("sudo su");
		system("sudo cp ../lib/Bazel.repo  /etc/yum.repos.d/");
	        system("yum install -y bazel");

	}
	else
	{
		printf("yum and bazel is installed!\n");
	}
}
