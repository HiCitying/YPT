#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "Mapping.h"
#include "Show_Bmp.h"
#include "ClearScreen.h"


void main(void)
{
    //1.打开文件
    int lcd_fd = open("/dev/fb0",O_RDWR);
    if(lcd_fd < 0)
    {
        perror("open lcd_fd error\n");
    }

    //2.映射内存
    int *p=Mapping(lcd_fd,800,480);

    //3.打开图片
    int picture_fd = open("./Hong.bmp",O_RDWR);
    if(picture_fd < 0)
    {
        perror("open picture_fd erorr\n");
    }

    //4.显示图片
    Show_Bmp(picture_fd,p,800,480,0,0);
    sleep(2);
    ClearScreen(p,0x00ff0000);


    //5.收尾
    DeMapping(p,800,480);
    close(lcd_fd);
    close(picture_fd);


}