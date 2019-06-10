#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <sys/types.h>
#include <signal.h>
#include "Mapping.h"
#include "Show_Bmp.h"
#include "ClearScreen.h"
#include "Show_Word.h"
#include "Show_Num.h"
#include "Play_Music.h"
#include "Open_Led.h"
#include "Serial.h"
#include "LTPHH.h"
//#include "Touch_Screen.h"


void main(void)
{

    unsigned char mo[2][32] = {{0x20,0x00,0x3E,0x7C,0x48,0x44,0x08,0x44,0xFF,0x44,0x14,0x44,0x22,0x7C,0x40,0x00,
                                0x1F,0xF0,0x10,0x10,0x10,0x10,0x1F,0xF0,0x10,0x10,0x10,0x10,0x1F,0xF0,0x10,0x10},
                               {0x10,0x40,0x24,0x44,0x42,0x48,0xFF,0x70,0x01,0x40,0x00,0x42,0x7E,0x42,0x42,0x3E,
                                0x42,0x00,0x7E,0x44,0x42,0x48,0x42,0x70,0x7E,0x40,0x42,0x42,0x4A,0x42,0x44,0x3E}};

    int pid_1=-1;
    int pid_2=-1;
    int pid_3=-1;

    char *music[2]={"TSLS.mp3","TSWD.mp3"};
    int num_music=0;


    int x,y;

    //1.打开文件
    int lcd_fd = open("/dev/fb0",O_RDWR);
    if(lcd_fd < 0)
    {
        perror("open lcd_fd error\n");
    }
    // 打开触控板
    int touch_fd = open("/dev/input/event0",O_RDWR);
    if(touch_fd < 0)
    {
        perror("open touch_fd error\n");
    }


    //2.映射内存
    int *p=Mapping(lcd_fd,800,480);

    //3.打开图片
//    int picture_fd = open("./Hong.bmp",O_RDWR);
//    if(picture_fd < 0)
//    {
//        perror("open picture_fd erorr\n");
//    }
    int music_fd = open("./Music.bmp",O_RDWR);
    if(music_fd < 0)
    {
        perror("open Music_fd erorr\n");
    }
    int start_fd = open("./Start.bmp",O_RDWR);
    if(start_fd < 0)
    {
        perror("open start_fd erorr\n");
    }
    int pause_fd = open("./Pause.bmp",O_RDWR);
    if(pause_fd < 0)
    {
        perror("open pause_fd erorr\n");
    }
    //打开驱动
    int led_fd = open("/dev/led_drv",O_RDWR);
    if(led_fd < 0)
    {
        perror("open led_fd erorr\n");
    }


    int light_off_fd = open("./light_off.bmp",O_RDWR);
    if(light_off_fd < 0)
    {
        perror("open light_off_fd erorr\n");
    }
    int light_on_fd = open("./light_on.bmp",O_RDWR);
    if(light_on_fd < 0)
    {
        perror("open light_on_fd erorr\n");
    }

    //4.显示图片
    //Show_Bmp(music_fd,p,240,240,0,0);
    Show_Bmp(start_fd,p,80,78,80,80);

    Open_Led(led_fd,0,10);
    Show_Bmp(light_off_fd,p,144,240,650,0);

    //sleep(2);
    //ClearScreen(p,0x00ff0000);

//    if((pid_2=fork())==0)
//    {
//        int i=1;
//        while (i)
//        {
//            Show_Word(mo[0],p,i,0,16, sizeof(mo[0]),0x00ff0000);
//            sleep(0.3);
//            i++;
//            if(i>=800)
//            {
//                i=1;
//            }
//            ClearScreen(p,0x00ffffff);
//        }
//    }


//    Show_Num(1,p,200,0,0x00FF0000);

//    Show_Num(22222,p,200,20,0x00FF0000);
//    Show_Num(234,p,200,40,0x00FF0000);
//    Show_Num(2345,p,200,60,0x00FF0000);
//    Show_Num(23564,p,200,80,0x00FF0000);

    //char *path="TSLS.mp3";


    //sleep(20);
    //pid=fork();

    if((pid_2=fork())==0)
    {
        int L=0;
        int T=0;
        int P=0;
        int H1=0;
        int H2=0;
        //int *py1=p;

        //Touch_Screen(p,picture_fd);
        LTPHH(p,&L,&T,&P,&H1,&H2);
    }








//    if((pid_2=fork())==0)
//    {
//        Play_Music("TSLS.mp3");
//    }
    //sleep(10);
    //ClearScreen(p,0x00ffffff);

    ClearScreen(p,0,150,5,480,0x00ff0000);

    struct input_event ev;
    int flag=0;
    int led_flag=0;
    int ret;
    while(1)
    {

        //读取触摸屏事件
        ret = read(touch_fd,&ev,sizeof(ev));
        if(ret < sizeof(ev))
        {
            continue;
        }
        printf("ev.type = %d , ev.code = %d, ev.value = %d\n",ev.type,ev.code,ev.value);

        //认为是一个X事件
        if(ev.type == EV_ABS && ev.code == ABS_X)
        {
            x = ev.value;
        }
            //认为是一个Y事件
        else if(ev.type == EV_ABS && ev.code == ABS_Y)
        {
            y = ev.value;
        }
            //认为按下去了
        else if(ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value != 0 )
        {
            //Show_Bmp(pause_fd,p,80,78,80,80);
            if(x>80&&x<160&&y>80&&y<160)
            {
                if(pid_1==-1)
                {
                    if((pid_1=fork())==0)
                    {
                        Show_Bmp(pause_fd,p,80,78,80,80);
                        Play_Music(music[num_music]);
                        flag=1;
                    }
                } else
                {
                    if(flag==0)
                    {
                        Show_Bmp(pause_fd,p,80,78,80,80);
                        kill(pid_1,18);
                        flag=1;

                    } else{
                        Show_Bmp(start_fd,p,80,78,80,80);
                        kill(pid_1,19);
                        flag=0;

                    }
                }

            }else if(x>0&&x<80&&y>80&&y<160)
            {
                if(pid_1==-1)
                {
                    if((pid_1=fork())==0)
                    {
                        Show_Bmp(pause_fd,p,80,78,80,80);
                        Play_Music(music[num_music]);
                        flag=1;
                    }
                } else
                {
                    kill(pid_1,9);
                    num_music=num_music-1;
                    if(num_music<0)
                    {
                        num_music=1;
                    }
                    num_music=num_music%2;
                    if((pid_1=fork())==0)
                    {

                        Show_Bmp(pause_fd,p,80,78,80,80);
                        Play_Music(music[num_music]);

                    }

                }
            } else if(x>160&&x<240&&y>80&&y<160)
            {
                if(pid_1==-1)
                {
                    if((pid_1=fork())==0)
                    {
                        Show_Bmp(pause_fd,p,80,78,80,80);
                        Play_Music(music[num_music]);
                        flag=1;
                    }
                } else
                {
                    kill(pid_1,9);
                    num_music=((++num_music)%2);
                    if((pid_1=fork())==0)
                    {
                        Show_Bmp(pause_fd,p,80,78,80,80);

                        Play_Music(music[num_music]);
                    }

                }
            } else if(x>650&&x<800&&y>0&&y<240)
            {
                if(led_flag==0)
                {
                    Open_Led(led_fd,1,10);
                    Show_Bmp(light_on_fd,p,144,240,650,0);
                    led_flag=1;
                } else
                {
                    Open_Led(led_fd,0,10);
                    Show_Bmp(light_off_fd,p,144,240,650,0);
                    led_flag=0;
                }
            }

        }
            //认为此时弹起来了
        else if(ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)
        {


        }

    }

    //int status;
    wait(NULL);
    //5.收尾
    DeMapping(p,800,480);
    close(lcd_fd);
    close(music_fd);
    close(start_fd);
    close(pause_fd);


}