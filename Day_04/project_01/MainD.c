#include "Head.h"

void main(void)
{
    uint buf_r[H*W*4];

    int fd=open(FBOPATH,O_RDWR);
    if(fd<0)
    {
        printf("Open fb0 Error\n");
    }

    int fd_p=open(BMPPATH,O_RDWR);
    if(fd_p<0)
    {
        printf("Open Bmp Error\n");
    }

    T24BmpTo32(fd_p,buf_r);
    DrawSA(fd,buf_r);
}
