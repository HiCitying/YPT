#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

#define RedColor 0x00ff0000
#define BlackColor 0x002b2b2b
#define BlueColor 0x00436eee

#define W 800
#define H 480
void draw_color(int x,int y,int w,int h,int color)
{
    int i,j;
    int fd=open("/dev/fb0",O_RDWR);
    lseek(fd,0,SEEK_SET);
    int *p=mmap(NULL,480*800*4,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(fd<0)
    {
        printf("Open Error\n");
        return -1;
    }


    for (i=x;i<H;i++)
    {
        for (j=y;j<W;j++)
        {
            p=j+i*W+y;
            *p=color;
            if(j>w)
            {
                break;
            }
        }
        if(i>h)
        {
            break;
        }
    }
    munmap(p,480*800*4);
}

int  main(void)
{
//    int i,j;
//    int fd=open("/dev/fb0",O_RDWR);
//    lseek(fd,0,SEEK_SET);
//    int *p=mmap(NULL,480*800*4,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);




    draw_color(0,0,200,200,BlueColor);

//    for (i=0;i<480*800;i++)
//    {
//        *(p+i)=RedColor;
//    }



    close(fd);

    return 0;
}