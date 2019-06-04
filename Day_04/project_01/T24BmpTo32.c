#include "Head.h"

void T24BmpTo32(int fd_p, uint *bcolor)
{
    int i,j;
    uint b_1;
    uint b_2;
    uint b_3;

    uchar buf_p[W*H*3];
    int x=0;
    int rt;


    lseek(fd_p,BmpOff,SEEK_SET);
    rt=read(fd_p,buf_p,H*W*3);

    if(rt<0)
    {
        printf("Read Error\n");
    }

    for(i=H-1;i>=0;i--)
    {
        for (j=0;j<W;j++)
        {
            b_1=(uint)buf_p[2+x];
            b_2=(uint)buf_p[1+x];
            b_3=(uint)buf_p[x];
            bcolor[i*W+j]=(b_1<<16|b_2<<8|b_3);
            x+=3;
        }
    }
}