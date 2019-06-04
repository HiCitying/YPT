#include "Head.h"



void main(void)
{
    int fd=open(FB0PATH,O_RDWR);
    if(fd<0)
    {
        printf("Open Error\n");
    }
    draw_image(fd,0,0,50,100,0xf0f0f0);

}