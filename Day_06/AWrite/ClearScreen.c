#include "Head.h"

//ph 高度
//pw 宽度
//color 颜色

void ClearScreen(int fd,int x0,int y0,int ph,int pw,int color)
{
    int x,y;
    lseek(fd,0,SEEK_SET);
    int *p=mmap(NULL,W*H*4,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
    for(x=x0;x<x0+ph;x++)
        for(y=y0;y<y0+pw;y++)
        {
            *(p+x*W+y)=color;
        }
    munmap(p,W*H*4);
}
