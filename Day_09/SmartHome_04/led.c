#include "myutils.h"

void control_led(void)
{
	int lcd_fd = open("/dev/fb0",O_RDWR);
	if(lcd_fd < 0)
	{
		perror("open lcd_fd error\n");
	}	
	//映射文件
	
	p  = mmap(NULL,800*480*4,PROT_READ | PROT_WRITE, MAP_SHARED,lcd_fd,0);
	if(p == MAP_FAILED)
	{
		perror("mmap erorr\n");
	}
	
	//1.打开触摸屏文件
	int touch_fd = open("/dev/input/event0",O_RDWR);
	if(touch_fd < 0)
	{
		perror("open touch_fd error\n");
	}
	
	int led_fd = open("/dev/led_drv",O_RDWR);
	if(led_fd < 0)
	{
		perror("open led_fd erorr\n");
	}

	show_bmp("./you/off.bmp",600,480,200,0);
	show_bmp("./you/bt_off.bmp",160,60,220,360);
	show_bmp("./you/bt2_on.bmp",160,61,420,360);
	show_bmp("./you/bt_off.bmp",160,60,620,360);
	
//	unsigned char cmd1[2];
//	cmd1[0] = 0;  //cmd[0]存的是灯的状态1是亮 0是灭
//	cmd1[1] = 10; //cmd[1]存的是灯的编号
//
//	unsigned char cmd2[2];
//	cmd2[0] = 0;  //cmd[0]存的是灯的状态1是亮 0是灭
//	cmd2[1] = 9; //cmd[1]存的是灯的编号
//
//	int flag1=-1,flag2=-1,flag3=-1; //-1代表关闭状态 ，1 代表打开状态
	int x,y;



//	while(1)
//	{
//		struct input_event ev;
//		//读取触摸屏事件
//		int ret = read(touch_fd,&ev,sizeof(ev));
//		if(ret < sizeof(ev))
//		{
//			continue;
//		}
//
//		//认为是一个X事件
//		if(ev.type == EV_ABS && ev.code == ABS_X)
//		{
//			x = ev.value;
//		}
//		//认为是一个Y事件
//		else if(ev.type == EV_ABS && ev.code == ABS_Y)
//		{
//			y = ev.value;
//		}
//		//认为按下去了
//		else if(ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value != 0 )
//		{
//
//		}
//		//认为此时弹起来了
//		else if(ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)
//		{
//			//第十盏灯  第一个开关
//			if(x>220 && x < 380 && y > 360 && y <420)
//			{
//				if(cmd1[0]==0)
//				{
//					flag1=-flag1;
//					cmd1[0]=1;     //10亮
//					cmd1[1] = 10;
//					write(led_fd,cmd1,2);
//					if(cmd2[0]==0) //9号灯灭
//					{
//						show_bmp("./you/on.bmp",600,480,200,0);
//					}else //9号灯亮
//					{
//						show_bmp("./you/on_1.bmp",600,480,200,0);
//					}
//
//					if(flag1==1)
//					{
//						show_bmp("./you/bt_on.bmp",160,60,220,360); //第1个开关
//					}else{
//						show_bmp("./you/bt_off.bmp",160,60,220,360); //第1个开关
//					}
//
//					if(flag2==1)
//					{
//						show_bmp("./you/bt2_off.bmp",160,61,420,360); //第二个开关
//					}else{
//						show_bmp("./you/bt2_on.bmp",160,61,420,360); //第二个开关
//					}
//
//					if(flag3==1){
//
//						show_bmp("./you/bt_on.bmp",160,60,620,360); //第3个开关
//					}else{
//						show_bmp("./you/bt_off.bmp",160,60,620,360); //第3个开关
//					}
//
//
//				}
//				else
//				{
//					flag1=-flag1;
//					cmd1[0]=0;  //10灭
//					cmd1[1] = 10;
//					write(led_fd,cmd1,2);
//					if(cmd2[0]==0) //9号灯灭
//					{
//						show_bmp("./you/off.bmp",600,480,200,0);
//					}else //9号灯亮
//					{
//						show_bmp("./you/on.bmp",600,480,200,0);
//					}
//
//					if(flag1==1)
//					{
//						show_bmp("./you/bt_on.bmp",160,60,220,360); //第1个开关
//					}else{
//
//						show_bmp("./you/bt_off.bmp",160,60,220,360); //第1个开关
//					}
//
//					if(flag2==1)
//					{
//						show_bmp("./you/bt2_off.bmp",160,61,420,360); //第二个开关
//					}else{
//
//						show_bmp("./you/bt2_on.bmp",160,61,420,360); //第二个开关
//					}
//
//					if(flag3==1){
//
//						show_bmp("./you/bt_on.bmp",160,60,620,360); //第3个开关
//					}else{
//
//						show_bmp("./you/bt_off.bmp",160,60,620,360); //第3个开关
//					}
//				}
//			}
//
//			//第9盏灯
//			if(x>420 && x < 580 && y > 360 && y <420)
//			{
//				if(cmd2[0]==0)
//				{
//					flag2=-flag2;
//					cmd2[0]=1;  //9亮
//					cmd2[1] = 9;
//					write(led_fd,cmd2,2);
//
//					if(cmd1[0]==0) //10号灯灭
//					{
//						show_bmp("./you/on.bmp",600,480,200,0);
//					}else //10号灯亮
//					{
//						show_bmp("./you/on_1.bmp",600,480,200,0);
//					}
//
//					if(flag1==1)
//					{
//						show_bmp("./you/bt_on.bmp",160,60,220,360); //第1个开关
//					}else{
//
//						show_bmp("./you/bt_off.bmp",160,60,220,360); //第1个开关
//					}
//
//					if(flag2==1)
//					{
//						show_bmp("./you/bt2_off.bmp",160,61,420,360); //第二个开关
//					}else{
//
//						show_bmp("./you/bt2_on.bmp",160,61,420,360); //第二个开关
//					}
//
//					if(flag3==1){
//
//						show_bmp("./you/bt_on.bmp",160,60,620,360); //第3个开关
//					}else{
//
//						show_bmp("./you/bt_off.bmp",160,60,620,360); //第3个开关
//					}
//
//				}
//				else
//				{
//					flag2=-flag2;
//					cmd2[0]=0;  //9灭
//					cmd2[1] = 9;
//					write(led_fd,cmd2,2);
//
//					if(cmd1[0]==0) //10号灯灭
//					{
//						show_bmp("./you/off.bmp",600,480,200,0);
//					}else //10号灯亮
//					{
//						show_bmp("./you/on.bmp",600,480,200,0);
//					}
//
//					if(flag1==1)
//					{
//						show_bmp("./you/bt_on.bmp",160,60,220,360); //第1个开关
//					}else{
//
//						show_bmp("./you/bt_off.bmp",160,60,220,360); //第1个开关
//					}
//
//					if(flag2==1)
//					{
//						show_bmp("./you/bt2_off.bmp",160,61,420,360); //第二个开关
//					}else{
//
//						show_bmp("./you/bt2_on.bmp",160,61,420,360); //第二个开关
//					}
//
//					if(flag3==1){
//
//						show_bmp("./you/bt_on.bmp",160,60,620,360); //第3个开关
//					}else{
//
//						show_bmp("./you/bt_off.bmp",160,60,620,360); //第3个开关
//					}
//				}
//			}
//
//			//第10盏灯 第二个开关
//			if(x>620 && x < 780 && y > 360 && y <420)
//			{
//				if(cmd1[0]==0)
//				{
//					flag3=-flag3;
//					cmd1[0]=1;  //10亮
//					cmd1[1] = 10;
//					write(led_fd,cmd1,2);
//
//					if(cmd2[0]==0) //10号灯灭
//					{
//						show_bmp("./you/on.bmp",600,480,200,0);
//					}else //10号灯亮
//					{
//						show_bmp("./you/on_1.bmp",600,480,200,0);
//					}
//
//					if(flag1==1)
//					{
//						show_bmp("./you/bt_on.bmp",160,60,220,360); //第1个开关
//					}else{
//
//						show_bmp("./you/bt_off.bmp",160,60,220,360); //第1个开关
//					}
//
//					if(flag2==1)
//					{
//						show_bmp("./you/bt2_off.bmp",160,61,420,360); //第二个开关
//					}else{
//
//						show_bmp("./you/bt2_on.bmp",160,61,420,360); //第二个开关
//					}
//
//					if(flag3==1){
//						show_bmp("./you/bt_on.bmp",160,60,620,360); //第3个开关
//					}else{
//
//						show_bmp("./you/bt_off.bmp",160,60,620,360); //第3个开关
//					}
//				}
//				else
//				{
//					flag3=-flag3;
//					cmd1[0]=0;  //10灭
//					cmd1[1] =10;
//					write(led_fd,cmd1,2);
//
//					if(cmd2[0]==0) //9号灯灭
//					{
//						show_bmp("./you/off.bmp",600,480,200,0);
//					}else //9号灯亮
//					{
//						show_bmp("./you/on.bmp",600,480,200,0);
//					}
//
//					if(flag1==1)
//					{
//						show_bmp("./you/bt_on.bmp",160,60,220,360); //第1个开关
//					}else{
//
//						show_bmp("./you/bt_off.bmp",160,60,220,360); //第1个开关
//					}
//
//					if(flag2==1)
//					{
//						show_bmp("./you/bt2_off.bmp",160,61,420,360); //第二个开关
//					}else{
//
//						show_bmp("./you/bt2_on.bmp",160,61,420,360); //第二个开关
//					}
//
//					if(flag3==1){
//
//						show_bmp("./you/bt_on.bmp",160,60,620,360); //第3个开关
//					}else{
//
//						show_bmp("./you/bt_off.bmp",160,60,620,360); //第3个开关
//					}
//				}
//			}
//
//
//		}
//
//	}
	
	
	//return 0;
}