#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>


int *p = NULL;

void draw_point(int x, int y, int color)
{
    if(x >= 0 && x < 800 && y >= 0 && y < 480)
    {
        *(p + 800* y + x) = color;
    }
}


void show_bmp(char *path,int wide, int high, int x, int y)
{
    int picture_fd = open(path,O_RDWR);
    if(picture_fd < 0)
    {
        perror("open picture_fd erorr\n");
        //printf("open picture_fd erorr\n");
    }

    lseek(picture_fd,54,SEEK_SET);

    unsigned char dat[800*480*3] = {0};

    int ret = read(picture_fd,dat,wide*high*3);
    if(ret < wide*high*3)
    {
        perror("read picture_fd erorr\n");
        //printf("read picture_fd erorr\n");
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



int main(void)
{
    //1.打开文件init_lcd()
    int lcd_fd = open("/dev/fb0",O_RDWR);
    if(lcd_fd < 0)
    {
        perror("open lcd_fd error\n");
        //printf("open lcd_fd error\n");
    }

    //2.映射文件
    p  = mmap(NULL,800*480*4,PROT_READ | PROT_WRITE, MAP_SHARED,lcd_fd,0);
    if(p == MAP_FAILED)
    {
        perror("mmap erorr\n");
        //printf("mmap erorr\n");
    }

    //3.打开图片文件以及读取数据和处理 显示
    show_bmp("./plh_2.bmp",200,120,0,0);
    
    //4.收尾工作
    munmap(p,800*480*4);
    close(lcd_fd);
}
