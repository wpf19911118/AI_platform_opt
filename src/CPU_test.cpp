#include <stdio.h>
#include "CPU_test.h"
#include <unistd.h>
#include <stdlib.h>

#include <stdint.h>
//CPU序列号的获取
unsigned int veax;
unsigned int vebx;
unsigned int vedx;
unsigned int vecx;


//CPU使用情况获取及核数获取
float g_cpu_used;
int cpu_num;
//CPU频率和型号信息 平均使用频率
char cpu_version[MAXBUFSIZE];
float val_fre;
//CPU 序列号


void CPU_test()
{
   CPU_OCCUPY ocpu,ncpu;

//获取cpu核数
   cpu_num = sysconf(_SC_NPROCESSORS_ONLN);

   printf("cpu mum:%d \n",cpu_num);

//获取cpu使用率
   get_occupy(&ocpu);
   sleep(1);
   get_occupy(&ncpu);
   cal_occupy(&ocpu, &ncpu);
   printf("cpu used:%4.2f \n", g_cpu_used);
//获取CPU型号及最大频率和使用频率
   get_cpu_ver_fre();
   printf("cpu_version=%s \n",cpu_version);
   printf("cpu_MHz=%f \n",val_fre);
//获取CPU的序列号  
   char cpuid[MAXBUFSIZE];
   getcpuid(cpuid);
 
   printf("cpuid is %s \n",cpuid);
   
   char cpufactory[MAXBUFSIZE];
   getcpufactory(cpufactory);
   printf("cpufactory is %s \n",cpufactory);
//支持的指令集
   system("gcc -march=native -Q --help=target|grep march");

  
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
    float fre,sum_fre;sum_fre=0.0;
    //char type_cpu[MAXBUFSIZE];
    char buff[MAXBUFSIZE];
    if((fp=popen("cat /proc/cpuinfo | grep name | cut -f2 -d: | uniq -c","r"))!=NULL)
    {
        while (1)
        {
         //if(!(fgets(buff[MAXBUFSIZE],sizeof(buff),fp)))
         fgets(cpu_version,sizeof(cpu_version),fp);
         //sscanf(buff,"%d %s",&num,type_cpu);
         //printf("cpu_version=%s\n",buff);
         if(! (fgets(cpu_version,sizeof(cpu_version),fp))){break;}
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
            //printf("cpu_MHz=%s\n",buff);
            if(! (fgets(buff,sizeof(buff),fp))){break;}
        }
        val_fre=sum_fre/num;
       // printf("cpu_MHz=%f\n",val_fre);

        fclose(fp);
    }



}

void cpuid(unsigned int veax1)
{   
    asm("cpuid"
        :"=a"(veax),
        "=b"(vebx),
        "=c"(vecx),
        "=d"(vedx)
        :"a"(veax));
}
//做移位操作，把寄存器中的值以“%d”形式输出
void LM(int var,uint32_t *vx)
{
  int i;
  for(i=0;i<3;i++)
  {
      var=(var>>i);
      vx[i]=var;
  }
}
//做移位操作，把寄存器中的ASCII码，以字符形式输出
void LeftMove(int var,char *vx)
{
//printf("%c",var);
for(int i=0;i<3;i++)
{
var=(var>>i);
vx[i]=var;
//printf("%c",var);
}
}
static void getcpuid (char *id)
{
    uint32_t ax[3],cx[3],dx[3];
    cpuid(1);
    LM(veax,ax);
    cpuid(3);
    LM(vecx,cx);
    LM(vedx,dx);
    sprintf(id,"%u%u%u%u%u%u%u%u%u",ax[0],ax[1],ax[2],cx[0],cx[1],cx[2],dx[0],dx[1],dx[2]);
}

static void getcpufactory (char *id)
{
    char bx[3],cx[3],dx[3];
    cpuid(0);
    LeftMove(vebx,bx);
    LeftMove(vedx,dx);
    LeftMove(vecx,cx);
    //cpuid(3);
    //LM(vecx,cx);
    //LM(vedx,dx);
    sprintf(id,"%u%u%c%u%u%u%u%u%u",bx[0],bx[1],bx[2],dx[0],dx[1],dx[2],cx[0],cx[1],cx[2]);
}

