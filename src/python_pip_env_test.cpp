#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "python_pip_env_test.h"

void python_pip_env_test()
{

	int i=0;
        char **buf=(char **)malloc(sizeof(char*)*2);
        for(i=0;i<2;i++)
	{
		buf[i]=(char *)malloc(sizeof(char)*1024);
	}
	
	//system("rm -rf tmp.txt");

	system("python -V 2>&1 | tee  tmp.txt");

	system("python3 -V 2>&1 | tee -a tmp.txt");

	system("pip -V 2>&1| tee -a tmp.txt");

	system("pip3 -V 2>&1| tee -a tmp.txt");
	

	FILE *fp;

	if ((fp=fopen("tmp.txt","r+"))!=NULL);
	{
		
		for(i=0;i<2;i++)
		{

			fgets(buf[i],1024,fp);
		//	if(!(fgets(buf[i],1024,fp))){break;}
		}	
		

		fclose(fp);
	}
          
	system("rm -rf tmp.txt");
	if(buf[0]||buf[1])
	{
		printf("pyton env is installed");
       		printf("pytho2: %s\n  python3: %s\n",buf[0],buf[1]);
	}
	else
	{
		printf("Please check out the python environment!");


	}

}

/*
int  main(int argc,char** argv)
{


	char **buf=(char **)malloc(sizeof(char*)*2);
	for(int i=0;i<2;i++)
	{
		buf[i]=(char *)malloc(sizeof(char)*1024);
	}

	python_pip_env_test();

	for(int i=0 ;i<2;i++)
	{
		free(buf[i]);
	}
	free(buf);

	return 0;
}
*/
