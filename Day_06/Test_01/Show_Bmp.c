#include "Show_Bmp.h"

void show_bmp(char *path,int wide, int high, int x, int y)
{
    int picture_fd = open(path,O_RDWR);
    if(picture_fd < 0)
    {
        perror("open picture_fd erorr\n");
    }

    lseek(picture_fd,54,SEEK_SET);



    unsigned char dat[800*480*3] = {0};



    int ret = read(picture_fd,dat,800*480*3);


    if(ret < 800*480*3)
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

            draw_point(x + j,y + high-i -1,color);
        }

    }

    close(picture_fd);




}