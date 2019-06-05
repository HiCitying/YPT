#include "Head.h"



void main(void)
{
    int fd=open(FB0PATH,O_RDWR);
    if(fd<0)
    {
        printf("Open Error\n");
    }
    draw_image(fd,0,0,480,800,0xf0f0f0);


    int i,j,n;
    unsigned int word[32]={0x10,0x00,0x10,0x00,0x21,0xFC,0x24,0x20,0x44,0x20,0xF8,0x20,0x10,0x20,0x20,0x20,
                           0x40,0x20,0xFC,0x20,0x40,0x20,0x00,0x20,0x1C,0x20,0xE0,0x20,0x43,0xFE,0x00,0x00};
    unsigned int mode[16*16]={0};

    unsigned tmp;
    int pd=8;
    for (i=0,n=0;i<32;i++)
    {
        for (j=0;j<8;j++)
        {
            tmp=word[i];
            tmp=tmp>>(pd-j-1);
            if(tmp&1)
            {
                mode[n]=1;

            }

            n++;
        }
    }

//    for (i=0;i<16*16;i++)
//    {
//        if(mode[i]==1)
//        {
//            draw_image(fd,0,0,16,16,0x00000000);
//        }
//    }

    lseek(fd,0,SEEK_SET);
    int x,y;
    int *p=mmap(NULL,480*800*4,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
    for(x=100,n=0;x<116;x++)
        for(y=200;y<216;y++)
        {
            if(mode[n]==1)
            {
                *(p+x*800+y)=0x00000000;

            }
            n++;

        }




    munmap(p,W*H*4);

}