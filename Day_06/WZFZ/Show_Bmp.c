#include "Show_Bmp.h"
#include "DrawPoint.h"




void Show_Bmp(int fd,int *py,int wide, int high, int x, int y)
{


    lseek(fd,54,SEEK_SET);
    unsigned char dat[PWIDTH*PHIGH*3] = {0};



    int ret = read(fd,dat,PWIDTH*PHIGH*3);


    if(ret < PWIDTH*PHIGH*3)
    {
        perror("read picture_fd erorr\n");
    }


    unsigned char a,b,g,r;
    a = 0;
    int color,num = 0;
    int i,j;
    for (i = 0; i < high; i++)
    {
        for(j = 0; j < wide; j++)
        {
            b = dat[num +0];
            g = dat[num +1];
            r = dat[num +2];

            num = num +3;

            color =  a << 24 | r << 16 | g << 8 | b;

            DrawPoint(py,x + j,y + high-i -1,color);

        }

    }





}