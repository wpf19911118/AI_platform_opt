#include <stdio.h>
#include <string.h>

#define MAXBUFSIZE 1024


//操作系统的版本号获取
void OS_test(char *str)
{
  char os_env[MAXBUFSIZE];
  if(strcasecmp(str,"centos")==0)
  {
    //system("ls -l");
    //system("uname -a");
    printf("Hello World\n");
    FILE *fp;
    if((fp=fopen("/etc/system-release","r"))!=NULL)
    {
      //fscanf(fp,"%s",os_env);
      fgets(os_env,sizeof(os_env),fp);
      printf("%s\n",os_env);
      fclose(fp);
    }
  }
 

}




int main(int argc ,char **argv)
{

char str[50]="ubuntu";
OS_test(str);


return 0;
}
