#include "head.h"
#define W 800
#define H 480
void draw_color(int x,int y,int w,int h,int color)
{
    int fd=open("/dev/fb0",O_RDWR);
    lseek(fd,0,SEEK_SET);
    int *p=mmap(NULL,480*800*4,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    int i,j;
    for (i=0;i<H;i++)
    {
        for (j=0;j<W;j++)
        {
            p=j+i*W;
            *p=color;
        }
    }
}