#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char **argv)
{





	struct stu{
	  	char *name; //姓名
	    	int num; //学号
	      	int age; //年龄
	        char group; //所在学习小组
		float score; //成绩
		};

	struct stu stu1;
	stu1.name="aaaa";
	stu1.num=5;
	stu1.age=12;
	stu1.group='B';
	stu1.score=99;

	printf("%s : num %d, age %d,group %c,score %f\n ",stu1.name,stu1.num,stu1.age,stu1.group,stu1.score);

        int a=system("cat num.txt"); 
	printf("return num=%d\a",a);



	return 0;
}
