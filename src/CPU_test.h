#define MAXBUFSIZE 1024
#include <stdint.h>

typedef  struct occupy
   {
        char name[20];
        unsigned int user;
        unsigned int nice;
        unsigned int system;
        unsigned int idle;
   } CPU_OCCUPY ;



void CPU_test();
void cal_occupy(CPU_OCCUPY *, CPU_OCCUPY *);
void get_occupy(CPU_OCCUPY *);
void get_cpu_ver_fre();

void cpuid(unsigned int veax1);
void LM(int var,uint32_t *vx);
void LeftMove(int var,char *vx);

static void getcpuid (char *id);
static void getcpufactory (char *id);

