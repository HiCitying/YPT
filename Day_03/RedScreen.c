#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define RedColor 0x00ff0000
#define BlackColor 0x002b2b2b
#define BlueColor 0x00436eee


int  main(void)
{
    int i,j;
    int Red[480][800];
    int fd=open("/dev/fb0",O_RDWR);


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

    lseek(fd,0,SEEK_SET);
    int fp=write(fd,Red,480*800*4);
    if(fp>0)
    {
        printf("Write Success\n");
    } else
    {
        printf("Write Fail\n");
    }



    close(fd);

    return 0;
}