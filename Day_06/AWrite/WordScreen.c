#include "Head.h"
#include "WordScreen.h"
// ph 像素点高度
// pw 像素点宽度
// status 状态数组

void WordScreen(int fd,int x0,int y0,int ph,int pw,int color, unsigned int (*status)[W])
{
    int x,y;
    int sx,sy;
    lseek(fd,0,SEEK_SET);
    int *p=mmap(NULL,W*H*4,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
    for(x=x0,sx=0;x<x0+ph;x++,sx++)
    {
        for(y=y0,sy=0;y<y0+pw;y++,sy++)
        {
            if(status[sx][sy]==1)
            {
                *(p+x*W+y)=color;
            }

        }
    }

    munmap(p,W*H*4);
}