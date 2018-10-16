#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

#define MAXBUFSIZE 1024

typedef  struct occupy
   {
        char name[20];
        unsigned int user;
        unsigned int nice;
        unsigned int system;
        unsigned int idle;
   } CPU_OCCUPY ;
 float g_cpu_used;
 int cpu_num;
//CPU使用率计算的结构体及全局变量


void OS_test(char *str);
void CPU_test();
void cal_occupy(CPU_OCCUPY *, CPU_OCCUPY *);
void get_occupy(CPU_OCCUPY *);
void get_cpu_ver_fre();




void GPU_test();
void MEM_test();
void HardDisk_test();
void Pcie_test();

void GPU_software_test();
void version_consistency();

void Auto_install();

void Bench_mark_test();

void deeplearning_framework();


void Auto_adjusting();
void demo_check(); 


int main(int argc,char **argv)
{
int i,j;
char temp_str[100];


for (i=0;i<=5;i++)
  {
   for(j=0;j<=5;j++)
      {
        printf(" * ");
      }
   printf("\n");
  }

printf("please input the OS environment, currently support is 'centos' or 'ubuntu' \n");
printf("centos must >7.0 ubuntu must >14.04\n");
/*
scanf("%s",temp_str);
//printf("Hello\n");
//printf("%s\n",temp_str);

if(strcasecmp(temp_str,"centos")==0)
{
  printf("centos\n");
}

if(strcasecmp(temp_str,"ubuntu")==0)
{
  printf("ubuntu\n");
}

if(strcasecmp(temp_str,"ubuntu")!=0&&strcasecmp(temp_str,"centos")!=0)
{
  
while (1)
  {
    printf("please input the OS env 'centos' or 'ubuntu' \n");
    scanf("%s",temp_str);
    if(strcasecmp(temp_str,"ubuntu")==0||strcasecmp(temp_str,"centos")==0)
      {
        printf("%s\n",temp_str);
        break;
      }
  }
}
*/
//system("uname -a");
OS_test("centos");
CPU_test();

return 0;
}

//操作系统的版本号获取
void OS_test(char *str)
{
  char os_env[MAXBUFSIZE];
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
}

//CPU使用情况获取及核数获取
void CPU_test()
{
   CPU_OCCUPY ocpu,ncpu;
   
//获取cpu核数
   cpu_num = sysconf(_SC_NPROCESSORS_ONLN);

   printf("cpu mum:%d\n",cpu_num);

//获取cpu使用率
   get_occupy(&ocpu);
   sleep(1);
   get_occupy(&ncpu);
   cal_occupy(&ocpu, &ncpu);
   printf("cpu used:%4.2f \n", g_cpu_used);
//获取CPU型号及最大频率和使用频率
   get_cpu_ver_fre();

}


void  cal_occupy (CPU_OCCUPY *o, CPU_OCCUPY *n)
{
    double od, nd;
    double id, sd;
    double scale;
    od = (double) (o->user + o->nice + o->system +o->idle);//第一次(用户+优先级+系统+空闲)的时间再赋给od  
    nd = (double) (n->user + n->nice + n->system +n->idle);//第二次(用户+优先级+系统+空闲)的时间再赋给od  
    scale = 100.0 / (float)(nd-od);       //100除强制转换(nd-od)之差为float类型再赋给scale这个变量  
    id = (double) (n->user - o->user);    //用户第一次和第二次的时间之差再赋给id  
    sd = (double) (n->system - o->system);//系统第一次和第二次的时间之差再赋给sd  
    g_cpu_used = ((sd+id)*100.0)/(nd-od); //((用户+系统)乖100)除(第一次和第二次的时间差)再赋给g_cpu_used  
}
void  get_occupy (CPU_OCCUPY *o)
{
     FILE *fd;
     int n;
     char buff[MAXBUFSIZE];
     fd = fopen ("/proc/stat", "r"); //这里只读取stat文件的第一行及cpu总信息，如需获取每核cpu的使用情况，请分析stat文件的接下来几行。
     fgets (buff, sizeof(buff), fd);
     sscanf (buff, "%s %u %u %u %u", o->name, &o->user, &o->nice,&o->system, &o->idle);
     fclose(fd);
}
void get_cpu_ver_fre()
{
    FILE *fp;
    int num,temp;num=0;
    float fre,sum_fre,val_fre;sum_fre=0.0;
    char type_cpu[MAXBUFSIZE];
    char buff[MAXBUFSIZE];
    if((fp=popen("cat /proc/cpuinfo | grep name | cut -f2 -d: | uniq -c","r"))!=NULL)
    {      
        while (1)
        {
         //if(!(fgets(buff[MAXBUFSIZE],sizeof(buff),fp)))
         fgets(buff,sizeof(buff),fp);
         //sscanf(buff,"%d %s",&num,type_cpu);
         printf("cpu_version=%s\n",buff);
         if(! (fgets(buff,sizeof(buff),fp))){break;}         
        }
      
      fclose(fp);
    }
   
    if((fp=popen("cat /proc/cpuinfo | grep MHz | cut -f2 -d: | uniq -c","r"))!=NULL)
    {
        while (1)
        {
            //if(!(fgets(buff[MAXBUFSIZE],sizeof(buff),fp)))
            fgets(buff,sizeof(buff),fp);
            sscanf(buff,"%d %f",&temp,&fre);
            sum_fre+=fre*temp;
            num+=temp;
            printf("cpu_MHz=%s\n",buff);
            if(! (fgets(buff,sizeof(buff),fp))){break;}
        }
        val_fre=sum_fre/num;
        printf("cpu_MHz=%f\n",val_fre);

        fclose(fp);
    }
         
      

}


