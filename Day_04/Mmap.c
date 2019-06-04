#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

#define RedColor 0x00ff0000
#define BlackColor 0x002b2b2b
#define BlueColor 0x00436eee


int  main(void)
{
    int i,j;
    int Red[480][800];
    int fd=open("/dev/fb0",O_RDWR);
    lseek(fd,0,SEEK_SET);
    int *p=mmap(NULL,480*800*4,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

    for (i=0;i<480;i++)
    {
        for (j=0;j<800;j++)
        {
            Red[i][j]=RedColor;
        }
    }

    if(fd<0)
    {
        printf("Open Error\n");
        return -1;
    }



    for (i=0;i<480*800;i++)
    {
        *(p+i)=RedColor;
    }

    munmap(p,480*800*4);

    close(fd);

    return 0;
}