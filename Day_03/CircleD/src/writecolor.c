#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "initial.h"

void writecolor(int fd,int (*color)[L],int n)
{
    int fp;
    lseek(fd,0,SEEK_SET);
    fp=write(fd,color,L*W*4);
    if(fp>0)
    {
        printf("Write Success\n");
    } else
    {
        printf("Write Fail\n");
    }
    sleep(1);
}