#include <stdio.h>
#include <string.h>
#include "OS_test.h"


//操作系统的版本号获取
void OS_test(char *str,char *os_env)
{
  //char os_env[MAXBUFSIZE];
  if(strcasecmp(str,"centos")==0)
  {
    //system("ls -l");
    //system("uname -a");
    FILE *fp;
    if((fp=fopen("/etc/system-release","r"))!=NULL)
    {
      //fscanf(fp,"%s",os_env);
      fgets(os_env,sizeof(os_env),fp);
      printf("%s\n",os_env);
      fclose(fp);
    }
  }
 
 if(strcasecmp(str,"ubuntu")==0)
 {

  FILE *fp;
  if((fp=fopen("/etc/issue","r"))!=NULL)
  {
   fgets(os_env,sizeof(os_env),fp);
   printf("%s\n",os_env);
   fclose(fp);
  }
  
 }
//return os_env;

}

