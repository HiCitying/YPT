#include <stdio.h>
#include <errno.h>
#include <linux/input.h>
#include <signal.h>
#include "DrawPoint.h"
#include "ClearScreen.h"
#include "Play_Music.h"
//#include "Show_Bmp.h"
#include "Open_Led.h"
#include "Show_Num.h"
#include "Show_Word.h"
#include "LTPHH.h"

#include "myutils.h"

#include "C_playmusic.h"



unsigned char cmd1[2]={0,10};
//cmd1[0] = 0;  //cmd[0]存的是灯的状态1是亮 0是灭
//cmd1[1] = 10; //cmd[1]存的是灯的编号

unsigned char cmd2[2]={0,9};
//cmd2[0] = 0;  //cmd[0]存的是灯的状态1是亮 0是灭
//cmd2[1] = 9; //cmd[1]存的是灯的编号

int bt_flag1=-1,bt_flag2=-1,bt_flag3=-1;


//cxc
int *p=NULL;
char *music=NULL;

void main(void)
{



    ClearScreen(0,0,800,480,0x00ffffff);
    ClearScreen(0,195,5,480,0x00ff0000);
    ClearScreen(115,0,195,5,0x00ff0000);
    ClearScreen(235,0,195,5,0x00ff0000);
    ClearScreen(355,0,195,5,0x00ff0000);


    //int pid[3]={-1,-1,-1};

    int pid_1=-1;
    int pid_2=-1;
    int pid_3=-1;
    int pid_4=-1;

    int pid_5=-1;
    int function=-1;
    ///////////////////////////////////
    //char *music[2]={"TSLS.mp3","TSWD.mp3"};
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
    int lcd_fd = open("/dev/fb0",O_RDWR);
    if(lcd_fd < 0)
    {
        perror("open lcd_fd error\n");
    }

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
    p=(int *)Mapping(lcd_fd,800,480);



   // Open_Led(led_fd,0,10);
   // Show_Bmp(light_off_fd,p,144,240,650,0);
    ////////////////////////////////////////////////////

    struct input_event event;
//    struct LTPHH{
//        int L;
//        int T;
//        int P;
//        int H1;
//        int H2;
//    };
//
//    struct LTPHH event1={0};
//    int pip_fd[2];
//    int pip_ret;

//    if((pid_4=fork())==0)
//    {
//        while (1)
//        {
//            close(pip_fd[1]);
//            pip_ret = read(pip_fd[0],&event1,sizeof(event1));
//            if(pip_ret < sizeof(event))
//            {
//                continue;
//            }
//            ClearScreen(0,280,100,100,0x00ffffff);
//            Show_Num(event1.L,p,300,0,0x00FF0000);
//            Show_Num(event1.T,p,300,20,0x00FF0000);
//            Show_Num(event1.P,p,300,40,0x00FF0000);
//            Show_Num(event1.H1,p,300,60,0x00FF0000);
//            Show_Num(event1.H2,p,300,80,0x00FF0000);
//            printf("CCCCCCCCCCCCCCCCevent1 = %d , event1 = %d, ev.value = %d\n",event1.L,event1.T,event1.P);
//            sleep(1);
//        }
//    }

    int x,y;
//    int flag=0;
//    int led_flag=0;
    int touch_fd = open("/dev/input/event0",O_RDWR);
    if(touch_fd < 0)
    {
        perror("open touch_fd error\n");
    }
    int ret;
    int flag=0;
    int num_music=0;
    int led_flag=0;


//        int T=0;
//        int P=0;
//        int H1=0;
//        int H2=0;
        //int *py1=p;

        //Touch_Screen(p,picture_fd);

//        printf("3333333333333333333333333");
//        if((pid_5=fork())==0)
//        {

        //}

//        while (1)
//        {
//
//            write(pip_fd[1],&event2, sizeof(event2));
//            printf("YYYYYYYYYYYYYevent1 = %d , event1 = %d, ev.value = %d\n",event2.L,event2.T,event2.P);
//            sleep(1);
//        }

//    if((pid_3=fork())==0)
//    {
//
////        close(pip_fd[0]);
////
////        struct LTPHH event2={0};
//        int L=0;
//        LTPHH(p,&L,1);
//
//    } else
//    {
//        printf("pid 33333333333333 error\n");
//    }


//    int L=0;
//    LTPHH(p,&L,1);

    while(1)
    {

        //读取触摸屏事件
        ret = read(touch_fd,&event,sizeof(event));
        if(ret < sizeof(event))
        {
            continue;
        }
       //printf("ev.type = %d , ev.code = %d, ev.value = %d\n",event.type,event.code,event.value);

        //认为是一个X事件
        if(event.type == EV_ABS && event.code == ABS_X)
        {
            x = event.value;
            //printf("xxxxxxxxxxxxxx:   %d",x);
        }
            //认为是一个Y事件
        else if(event.type == EV_ABS && event.code == ABS_Y)
        {
            y = event.value;
            //printf("yyyyyyyyyyyyyy:   %d",y);
        }
            //认为按下去了
        else if(event.type == EV_KEY && event.code == BTN_TOUCH && event.value != 0 )
        {
            if(x>0&&x<200)
            {
                if(y>0&&y<120)
                {
                    printf("first\n");
                    function=1;
                } else if(y>120&&y<240)
                {
                    printf("second\n");
                    function=2;
                } else if(y>240&&y<360)
                {
                    printf("third\n");
                    function=3;

                } else
                {
                    printf("forth\n");
                    function=4;
                }



                switch (function)
                {
                    case 1:
                    {

                        //判断进程是否创建,没有创建进程并加载功能
//                        if(pid_3!=-1)
//                        {
//                            kill(pid_3,9);
//                        }

//                        if(pid_1==-1)
//                        {
//                            Show_Bmp(music_fd,p,240,240,200,0);
//                            Show_Bmp(start_fd,p,80,78,280,80);
//
//                        } else
//                        {
//
//                        }
                        C_playmusic(p);


                        break;
                    }
                    case 2:
                    {
                        control_led();
                        break;
                    }
                    case 3:
                    {
//                        if(pid_3!=0)
//                        {
//                            if((pid_3=fork())==0)
//                            {
//                                int L=0;
//                                LTPHH(p,&L,1);
//
//                            } else
//                            {
//                                printf("pid 33333333333333 error\n");
//                               // pid_3=-1;
//                            }
//
//                        } else
//                        {
//
//                        }
                        break;
                    }
                    case 4:
                    {
                        //
                    }
                    default:
                    {
                        break;
                    }
                }
            } else
            {
                switch (function)
                {
                    case 1:
                    {
//                        if(x>280&&x<360&&y>80&&y<160)
//                        {
//                            if(pid_1==-1)
//                            {
//                                if((pid_1=fork())==0)
//                                {
//                                    Show_Bmp(pause_fd,p,80,78,280,80);
//                                    Play_Music(music[num_music]);
//                                    flag=1;
//                                }
//                            } else
//                            {
//                                if(flag==0)
//                                {
//                                    Show_Bmp(pause_fd,p,80,78,280,80);
//                                    kill(pid_1,18);
//                                    flag=1;
//
//                                } else{
//                                    Show_Bmp(start_fd,p,80,78,280,80);
//                                    kill(pid_1,19);
//                                    flag=0;
//
//                                }
//                            }
//
//                        }else if(x>200&&x<280&&y>80&&y<160)
//                        {
//                            if(pid_1==-1)
//                            {
//                                if((pid_1=fork())==0)
//                                {
//                                    Show_Bmp(pause_fd,p,80,78,280,80);
//                                    Play_Music(music[num_music]);
//                                    flag=1;
//                                }
//                            } else
//                            {
//                                kill(pid_1,9);
//                                num_music=num_music-1;
//                                if(num_music<0)
//                                {
//                                    num_music=1;
//                                }
//                                num_music=num_music%2;
//                                if((pid_1=fork())==0)
//                                {
//
//                                    Show_Bmp(pause_fd,p,80,78,280,80);
//                                    Play_Music(music[num_music]);
//
//                                }
//
//                            }
//                        } else if(x>360&&x<440&&y>80&&y<160)
//                        {
//                            if(pid_1==-1)
//                            {
//                                if((pid_1=fork())==0)
//                                {
//                                    Show_Bmp(pause_fd,p,80,78,280,80);
//                                    Play_Music(music[num_music]);
//                                    flag=1;
//                                }
//                            } else
//                            {
//                                kill(pid_1,9);
//                                num_music=((++num_music)%2);
//                                if((pid_1=fork())==0)
//                                {
//                                    Show_Bmp(pause_fd,p,80,78,280,80);
//
//                                    Play_Music(music[num_music]);
//                                }
//
//                            }
//                        }


                        //判断区域
                        break;
                    }
                    case 2:
                    {
//                        if(x>200&&x<314&&y>0&&y<240)
//                        {
//                            if(led_flag==0)
//                            {
//                                Open_Led(led_fd,1,10);
//                                Show_Bmp(light_on_fd,p,144,240,650,0);
//                                led_flag=1;
//                            } else
//                            {
//                                Open_Led(led_fd,0,10);
//                                Show_Bmp(light_off_fd,p,144,240,650,0);
//                                led_flag=0;
//                            }
//                        }

                        if(x>220 && x < 380 && y > 360 && y <420)
                        {
                            if(cmd1[0]==0)
                            {
                                bt_flag1=-bt_flag1;
                                cmd1[0]=1;     //10亮
                                cmd1[1] = 10;
                                write(led_fd,cmd1,2);
                                if(cmd2[0]==0) //9号灯灭
                                {
                                    show_bmp("./you/on.bmp",600,480,200,0);
                                }else //9号灯亮
                                {
                                    show_bmp("./you/on_1.bmp",600,480,200,0);
                                }

                                if(bt_flag1==1)
                                {
                                    show_bmp("./you/bt_on.bmp",160,60,220,360); //第1个开关
                                }else{
                                    show_bmp("./you/bt_off.bmp",160,60,220,360); //第1个开关
                                }

                                if(bt_flag2==1)
                                {
                                    show_bmp("./you/bt2_off.bmp",160,61,420,360); //第二个开关
                                }else{
                                    show_bmp("./you/bt2_on.bmp",160,61,420,360); //第二个开关
                                }

                                if(bt_flag3==1){

                                    show_bmp("./you/bt_on.bmp",160,60,620,360); //第3个开关
                                }else{
                                    show_bmp("./you/bt_off.bmp",160,60,620,360); //第3个开关
                                }


                            }
                            else
                            {
                                bt_flag1=-bt_flag1;
                                cmd1[0]=0;  //10灭
                                cmd1[1] = 10;
                                write(led_fd,cmd1,2);
                                if(cmd2[0]==0) //9号灯灭
                                {
                                    show_bmp("./you/off.bmp",600,480,200,0);
                                }else //9号灯亮
                                {
                                    show_bmp("./you/on.bmp",600,480,200,0);
                                }

                                if(bt_flag1==1)
                                {
                                    show_bmp("./you/bt_on.bmp",160,60,220,360); //第1个开关
                                }else{

                                    show_bmp("./you/bt_off.bmp",160,60,220,360); //第1个开关
                                }

                                if(bt_flag2==1)
                                {
                                    show_bmp("./you/bt2_off.bmp",160,61,420,360); //第二个开关
                                }else{

                                    show_bmp("./you/bt2_on.bmp",160,61,420,360); //第二个开关
                                }

                                if(bt_flag3==1){

                                    show_bmp("./you/bt_on.bmp",160,60,620,360); //第3个开关
                                }else{

                                    show_bmp("./you/bt_off.bmp",160,60,620,360); //第3个开关
                                }
                            }
                        }

                        //第9盏灯
                        if(x>420 && x < 580 && y > 360 && y <420)
                        {
                            if(cmd2[0]==0)
                            {
                                bt_flag2=-bt_flag2;
                                cmd2[0]=1;  //9亮
                                cmd2[1] = 9;
                                write(led_fd,cmd2,2);

                                if(cmd1[0]==0) //10号灯灭
                                {
                                    show_bmp("./you/on.bmp",600,480,200,0);
                                }else //10号灯亮
                                {
                                    show_bmp("./you/on_1.bmp",600,480,200,0);
                                }

                                if(bt_flag1==1)
                                {
                                    show_bmp("./you/bt_on.bmp",160,60,220,360); //第1个开关
                                }else{

                                    show_bmp("./you/bt_off.bmp",160,60,220,360); //第1个开关
                                }

                                if(bt_flag2==1)
                                {
                                    show_bmp("./you/bt2_off.bmp",160,61,420,360); //第二个开关
                                }else{

                                    show_bmp("./you/bt2_on.bmp",160,61,420,360); //第二个开关
                                }

                                if(bt_flag3==1){

                                    show_bmp("./you/bt_on.bmp",160,60,620,360); //第3个开关
                                }else{

                                    show_bmp("./you/bt_off.bmp",160,60,620,360); //第3个开关
                                }

                            }
                            else
                            {
                                bt_flag2=-bt_flag2;
                                cmd2[0]=0;  //9灭
                                cmd2[1] = 9;
                                write(led_fd,cmd2,2);

                                if(cmd1[0]==0) //10号灯灭
                                {
                                    show_bmp("./you/off.bmp",600,480,200,0);
                                }else //10号灯亮
                                {
                                    show_bmp("./you/on.bmp",600,480,200,0);
                                }

                                if(bt_flag1==1)
                                {
                                    show_bmp("./you/bt_on.bmp",160,60,220,360); //第1个开关
                                }else{

                                    show_bmp("./you/bt_off.bmp",160,60,220,360); //第1个开关
                                }

                                if(bt_flag2==1)
                                {
                                    show_bmp("./you/bt2_off.bmp",160,61,420,360); //第二个开关
                                }else{

                                    show_bmp("./you/bt2_on.bmp",160,61,420,360); //第二个开关
                                }

                                if(bt_flag3==1){

                                    show_bmp("./you/bt_on.bmp",160,60,620,360); //第3个开关
                                }else{

                                    show_bmp("./you/bt_off.bmp",160,60,620,360); //第3个开关
                                }
                            }
                        }

                        //第10盏灯 第二个开关
                        if(x>620 && x < 780 && y > 360 && y <420)
                        {
                            if(cmd1[0]==0)
                            {
                                bt_flag3=-bt_flag3;
                                cmd1[0]=1;  //10亮
                                cmd1[1] = 10;
                                write(led_fd,cmd1,2);

                                if(cmd2[0]==0) //10号灯灭
                                {
                                    show_bmp("./you/on.bmp",600,480,200,0);
                                }else //10号灯亮
                                {
                                    show_bmp("./you/on_1.bmp",600,480,200,0);
                                }

                                if(bt_flag1==1)
                                {
                                    show_bmp("./you/bt_on.bmp",160,60,220,360); //第1个开关
                                }else{

                                    show_bmp("./you/bt_off.bmp",160,60,220,360); //第1个开关
                                }

                                if(bt_flag2==1)
                                {
                                    show_bmp("./you/bt2_off.bmp",160,61,420,360); //第二个开关
                                }else{

                                    show_bmp("./you/bt2_on.bmp",160,61,420,360); //第二个开关
                                }

                                if(bt_flag3==1){
                                    show_bmp("./you/bt_on.bmp",160,60,620,360); //第3个开关
                                }else{

                                    show_bmp("./you/bt_off.bmp",160,60,620,360); //第3个开关
                                }
                            }
                            else
                            {
                                bt_flag3=-bt_flag3;
                                cmd1[0]=0;  //10灭
                                cmd1[1] =10;
                                write(led_fd,cmd1,2);

                                if(cmd2[0]==0) //9号灯灭
                                {
                                    show_bmp("./you/off.bmp",600,480,200,0);
                                }else //9号灯亮
                                {
                                    show_bmp("./you/on.bmp",600,480,200,0);
                                }

                                if(bt_flag1==1)
                                {
                                    show_bmp("./you/bt_on.bmp",160,60,220,360); //第1个开关
                                }else{

                                    show_bmp("./you/bt_off.bmp",160,60,220,360); //第1个开关
                                }

                                if(bt_flag2==1)
                                {
                                    show_bmp("./you/bt2_off.bmp",160,61,420,360); //第二个开关
                                }else{

                                    show_bmp("./you/bt2_on.bmp",160,61,420,360); //第二个开关
                                }

                                if(bt_flag3==1){

                                    show_bmp("./you/bt_on.bmp",160,60,620,360); //第3个开关
                                }else{

                                    show_bmp("./you/bt_off.bmp",160,60,620,360); //第3个开关
                                }
                            }
                        }

                        break;
                    }
                    case 3:
                    {

                        break;
                    }
                    case 4:
                    {
                        break;
                    }
                    default:
                    {

                    }

                }
            }








            //Show_Bmp(pause_fd,p,80,78,80,80);
//            if(x>80&&x<160&&y>80&&y<160)
//            {
//                if(pid_1==-1)
//                {
//                    if((pid_1=fork())==0)
//                    {
//                        Show_Bmp(pause_fd,p,80,78,80,80);
//                        Play_Music(music[num_music]);
//                        flag=1;
//                    }
//                } else
//                {
//                    if(flag==0)
//                    {
//                        Show_Bmp(pause_fd,p,80,78,80,80);
//                        kill(pid_1,18);
//                        flag=1;
//
//                    } else{
//                        Show_Bmp(start_fd,p,80,78,80,80);
//                        kill(pid_1,19);
//                        flag=0;
//
//                    }
//                }
//
//            }else if(x>0&&x<80&&y>80&&y<160)
//            {
//                if(pid_1==-1)
//                {
//                    if((pid_1=fork())==0)
//                    {
//                        Show_Bmp(pause_fd,p,80,78,80,80);
//                        Play_Music(music[num_music]);
//                        flag=1;
//                    }
//                } else
//                {
//                    kill(pid_1,9);
//                    num_music=num_music-1;
//                    if(num_music<0)
//                    {
//                        num_music=1;
//                    }
//                    num_music=num_music%2;
//                    if((pid_1=fork())==0)
//                    {
//
//                        Show_Bmp(pause_fd,p,80,78,80,80);
//                        Play_Music(music[num_music]);
//
//                    }
//
//                }
//            } else if(x>160&&x<240&&y>80&&y<160)
//            {
//                if(pid_1==-1)
//                {
//                    if((pid_1=fork())==0)
//                    {
//                        Show_Bmp(pause_fd,p,80,78,80,80);
//                        Play_Music(music[num_music]);
//                        flag=1;
//                    }
//                } else
//                {
//                    kill(pid_1,9);
//                    num_music=((++num_music)%2);
//                    if((pid_1=fork())==0)
//                    {
//                        Show_Bmp(pause_fd,p,80,78,80,80);
//
//                        Play_Music(music[num_music]);
//                    }
//
//                }
//            } else if(x>650&&x<800&&y>0&&y<240)
//            {
//                if(led_flag==0)
//                {
//                    Open_Led(led_fd,1,10);
//                    Show_Bmp(light_on_fd,p,144,240,650,0);
//                    led_flag=1;
//                } else
//                {
//                    Open_Led(led_fd,0,10);
//                    Show_Bmp(light_off_fd,p,144,240,650,0);
//                    led_flag=0;
//                }
//            }

        }
            //认为此时弹起来了
        else if(event.type == EV_KEY && event.code == BTN_TOUCH && event.value == 0)
        {

        }

    }


}