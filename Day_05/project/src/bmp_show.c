#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>


int *p=NULL;

void draw_point(int x,int y,int color)
{
    if(x>=0&&x<800&&y>=0&&y<480)
    {
        *(p+800*y+x)=color;
    }
}
void show_bmp(char *path,int wide,int high,int x,int y)
{
    int picture_fd=open(path,O_RDWR);
    if(picture_fd<0)
    {
        printf("open picture errror\n");
    }
    lseek(picture_fd,54,SEEK_SET);
    unsigned char data[800*480*3]={0};

    int res=read(picture_fd,data,800*480*3);
    if(res<800*480*3)
    {
        printf("read picture error\n");
    }

    unsigned char a,b,g,r;
    a=0;
    int color,number=0;
    int i,j;
    for (i=0;i<high;i++)
    {
        for (j=0;j<wide;j++)
        {
            b=data[number+0];
            g=data[number+1];
            r=data[number+2];
            number=number+3;
            color=a<<24|r<<16|g<<8|b;

            draw_point(x+j,y+high-i-1,color);
        }
    }
    close(picture_fd);

}
int main(void)
{
    //1.打开文件
    int lcd_fd=open("/dev/fb0",O_RDWR);
    if(lcd_fd<0)
    {
        printf("open lcd error\n");
    }
    //2.映射文件
    p=mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,lcd_fd,0);

    if(p==MAP_FAILED)
    {
        printf("mmap error\n");
    }
    //3.打开文件以及数据处理和显示

    show_bmp("./Hong.bmp",800,480,0,0);
    //4.收尾
    munmap(p,800*480*4);
    close(lcd_fd);

    return 0;

}