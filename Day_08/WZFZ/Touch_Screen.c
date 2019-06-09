//#include <stdio.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <fcntl.h>
//#include <error.h>
//#include <linux/input.h>
#include "Touch_Screen.h"
#include "Show_Bmp.h"

void Touch_Screen(int *py,int picture_fd)
{
    //1.打开触摸屏文件
    int touch_fd = open("/dev/input/event0",O_RDWR);
    if(touch_fd < 0)
    {
        perror("open touch_fd error\n");
    }
    int x,y;
    while(1) {
        struct input_event ev;
        //读取触摸屏事件
        int ret = read(touch_fd, &ev, sizeof(ev));
        if (ret < sizeof(ev)) {
            continue;
        }
        printf("ev.type = %d , ev.code = %d, ev.value = %d\n", ev.type, ev.code, ev.value);

        //认为是一个X事件
        if (ev.type == EV_ABS && ev.code == ABS_X) {
            x = ev.value;
        }
            //认为是一个Y事件
        else if (ev.type == EV_ABS && ev.code == ABS_Y) {
            y = ev.value;
        }
            //认为按下去了
        else if (ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value != 0) {
            //ClearScreen(py,0x00ffffff);
        }
            //认为此时弹起来了
        else if (ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0) {

            //Show_Bmp(picture_fd,py,800,480,0,0);
        }
    }

}

//int main(void)
//{
//    //1.打开触摸屏文件
//    int touch_fd = open("/dev/input/event0",O_RDWR);
//    if(touch_fd < 0)
//    {
//        perror("open touch_fd error\n");
//    }
//    int x,y;
//    while(1)
//    {
//        struct input_event ev;
//        //读取触摸屏事件
//        int ret = read(touch_fd,&ev,sizeof(ev));
//        if(ret < sizeof(ev))
//        {
//            continue;
//        }
//        printf("ev.type = %d , ev.code = %d, ev.value = %d\n",ev.type,ev.code,ev.value);
//
//        //认为是一个X事件
//        if(ev.type == EV_ABS && ev.code == ABS_X)
//        {
//            x = ev.value;
//        }
//        //认为是一个Y事件
//        else if(ev.type == EV_ABS && ev.code == ABS_Y)
//        {
//            y = ev.value;
//        }
//            //认为按下去了
//        else if(ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value != 0 )
//        {
//
//        }
//            //认为此时弹起来了
//        else if(ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)
//        {
//
//        }
//
//    }
//}