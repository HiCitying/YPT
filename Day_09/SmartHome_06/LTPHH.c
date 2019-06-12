#include "LTPHH.h"
#include "Serial.h"
#include "Show_Num.h"
#include "ClearScreen.h"
#include "Open_Led.h"
#include <sys/stat.h>


//void LTPHH(int *py,int *L,int *T,int *P,int *H1,int *H2,int flag)
void LTPHH(int *py,int flag)
{
    int serial_fd = init_serial("/dev/ttySAC1",9600);


//        int fifo_fd;
//        int fifo_buf[5];
//
//        //printf("I am %d process.\n", getpid()); // 说明进程ID
//
//        if((fifo_fd = open("fifo1", O_WRONLY)) < 0) // 以写打开一个FIFO
//        {
//            perror("Open FIFO Failed");
//            //exit(1);
//        }

        //////////////////////////////////////

    while(1)
    {
        unsigned char cmd[3] = {0xA5,0x83,0x28};
        unsigned char buf[24] = {0};


        int tbg_fd = open("./t_bg.bmp",O_RDWR);
        if(tbg_fd < 0)
        {
            perror("open tbg_fd erorr\n");
        }

        //Show_Bmp(tbg_fd,py,600,480,200,0);

        int led_fd = open("/dev/led_drv",O_RDWR);
        if(led_fd < 0)
        {
            perror("open led_fd erorr\n");
        }

        int ret = write(serial_fd,cmd,3);//下指令
        if(ret < 3)
        {
            perror("write serial_fd error\n");
        }
        ret = read(serial_fd,buf,24);//读数据
        if(ret < 24 || buf[0] != 0x5A || buf[1] != 0x5A)
        {
            usleep(200000);
            continue;
        }

        //处理数据

        //光照强度
        int lxu = buf[4] << 24 | buf[5] << 16 | buf[6] << 8 | buf[7];
        lxu = lxu / 100;
        //*L=lxu;
        printf("lxu = %d\n",lxu);

        //温度
        int t = buf[13] << 8 | buf[14];
        t = t / 100;
        //*T=t;
        printf("t = %d\n",t);

        //气压
        int p = buf[15] << 24 | buf[16] << 16 | buf[17] << 8 | buf[18];
        p = p / 100;
        //*P=p;
        printf("p = %d\n",p);

        //湿度
        int hum = buf[19] << 8 | buf[20];
        hum = hum / 100;
        //*H1=hum;
        printf("hum = %d\n",hum);

        //海拔
        int h = buf[21] << 8 | buf[22];
        //*H2=h;
        printf("h = %d\n",h);

        //usleep(200000);
        if(flag==1)
        {
//            ClearScreen(0,280,100,100,0x00ffffff);
//            Show_Num(lxu,py,300,0,0x00FF0000);
//            Show_Num(t,py,300,20,0x00FF0000);
//            Show_Num(p,py,300,40,0x00FF0000);
//            Show_Num(hum,py,300,60,0x00FF0000);
//            Show_Num(h,py,300,80,0x00FF0000);
            Show_Bmp(tbg_fd,py,600,480,200,0);
            Show_Num(lxu,py,381,376,0x00FF0000); //lxu
            Show_Num(t,py,390,50,0x00FF0000);   //t
            Show_Num(h,py,521,208,0x00FF0000); //h
            Show_Num(p,py,620,105,0x00FF0000);//p
            Show_Num(hum,py,707,362,0x00FF0000);//hum
            sleep(1);
        }
//        fifo_buf[0]=lxu;
//        fifo_buf[1]=t;
//        fifo_buf[2]=p;
//        fifo_buf[3]=hum;
//        fifo_buf[4]=h;

//        if(write(fifo_fd,fifo_buf,5) < 0)  // 写入到FIFO中
//        {
//            perror("Write FIFO Failed");
//            //close(fd);
//            //exit(1);
//        }
//
//        printf("LLLLLLLLLLLLLLLLTTTTTTL:%d T:%d P:%d H1:%d H2:%d \n", fifo_buf[0],fifo_buf[1],fifo_buf[2],fifo_buf[3],fifo_buf[4]);



        sleep(1);  // 休眠1秒

        if(lxu<18)
        {
            Open_Led(led_fd,1,8);
        } else
        {
            Open_Led(led_fd,0,8);

        }

    }

    close(serial_fd);
}