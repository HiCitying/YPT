#include "myutils.h"

int main()
{
	int lcd_fd = open("/dev/fb0",O_RDWR);
	if(lcd_fd < 0)
	{
		perror("open lcd_fd error\n");
	}	
	//ӳ���ļ�
	
	p  = mmap(NULL,800*480*4,PROT_READ | PROT_WRITE, MAP_SHARED,lcd_fd,0);
	if(p == MAP_FAILED)
	{
		perror("mmap erorr\n");
	}
	
	//1.�򿪴������ļ�
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
	
	unsigned char cmd1[2];
	cmd1[0] = 0;  //cmd[0]����ǵƵ�״̬1���� 0����
	cmd1[1] = 10; //cmd[1]����ǵƵı��
	
	unsigned char cmd2[2];
	cmd2[0] = 0;  //cmd[0]����ǵƵ�״̬1���� 0����
	cmd2[1] = 9; //cmd[1]����ǵƵı��
	
	int flag1=-1,flag2=-1,flag3=-1; //-1����ر�״̬ ��1 �����״̬
	int x,y;
	while(1)
	{
		struct input_event ev;
		//��ȡ�������¼�
		int ret = read(touch_fd,&ev,sizeof(ev));
		if(ret < sizeof(ev))
		{
			continue;
		}
		
		//��Ϊ��һ��X�¼�
		if(ev.type == EV_ABS && ev.code == ABS_X)
		{
			x = ev.value;
		}
		//��Ϊ��һ��Y�¼�
		else if(ev.type == EV_ABS && ev.code == ABS_Y)
		{
			y = ev.value;
		}
		//��Ϊ����ȥ��
		else if(ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value != 0 )
		{
			
		}
		//��Ϊ��ʱ��������
		else if(ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)
		{
			//��ʮյ��  ��һ������
			if(x>220 && x < 380 && y > 360 && y <420)
			{
				if(cmd1[0]==0)
				{
					flag1=-flag1;
					cmd1[0]=1;     //10��
					cmd1[1] = 10;
					write(led_fd,cmd1,2);
					if(cmd2[0]==0) //9�ŵ���
					{
						show_bmp("./you/on.bmp",600,480,200,0);
					}else //9�ŵ���
					{
						show_bmp("./you/on_1.bmp",600,480,200,0);
					}
					
					if(flag1==1)
					{	
						show_bmp("./you/bt_on.bmp",160,60,220,360); //��1������
					}else{
						show_bmp("./you/bt_off.bmp",160,60,220,360); //��1������
					}
					
					if(flag2==1)
					{	
						show_bmp("./you/bt2_off.bmp",160,61,420,360); //�ڶ�������
					}else{
						show_bmp("./you/bt2_on.bmp",160,61,420,360); //�ڶ�������
					}
					
					if(flag3==1){
						
						show_bmp("./you/bt_on.bmp",160,60,620,360); //��3������
					}else{
						show_bmp("./you/bt_off.bmp",160,60,620,360); //��3������
					}
					
					
				}
				else  
				{
					flag1=-flag1;
					cmd1[0]=0;  //10��
					cmd1[1] = 10;
					write(led_fd,cmd1,2);
					if(cmd2[0]==0) //9�ŵ���
					{
						show_bmp("./you/off.bmp",600,480,200,0);
					}else //9�ŵ���
					{
						show_bmp("./you/on.bmp",600,480,200,0);
					}
					
					if(flag1==1)
					{	
						show_bmp("./you/bt_on.bmp",160,60,220,360); //��1������
					}else{
					
						show_bmp("./you/bt_off.bmp",160,60,220,360); //��1������
					}
					
					if(flag2==1)
					{
						show_bmp("./you/bt2_off.bmp",160,61,420,360); //�ڶ�������
					}else{
						
						show_bmp("./you/bt2_on.bmp",160,61,420,360); //�ڶ�������
					}
					
					if(flag3==1){
						
						show_bmp("./you/bt_on.bmp",160,60,620,360); //��3������
					}else{
						
						show_bmp("./you/bt_off.bmp",160,60,620,360); //��3������
					}
				}
			}
			
			//��9յ��
			if(x>420 && x < 580 && y > 360 && y <420)
			{
				if(cmd2[0]==0)
				{
					flag2=-flag2;
					cmd2[0]=1;  //9��
					cmd2[1] = 9;
					write(led_fd,cmd2,2);
					
					if(cmd1[0]==0) //10�ŵ���
					{
						show_bmp("./you/on.bmp",600,480,200,0);
					}else //10�ŵ���
					{
						show_bmp("./you/on_1.bmp",600,480,200,0);
					}

					if(flag1==1)
					{	
						show_bmp("./you/bt_on.bmp",160,60,220,360); //��1������
					}else{
					
						show_bmp("./you/bt_off.bmp",160,60,220,360); //��1������
					}
					
					if(flag2==1)
					{	
						show_bmp("./you/bt2_off.bmp",160,61,420,360); //�ڶ�������
					}else{
						
						show_bmp("./you/bt2_on.bmp",160,61,420,360); //�ڶ�������
					}
					
					if(flag3==1){
						
						show_bmp("./you/bt_on.bmp",160,60,620,360); //��3������
					}else{
						
						show_bmp("./you/bt_off.bmp",160,60,620,360); //��3������
					}
					
				}
				else
				{
					flag2=-flag2;
					cmd2[0]=0;  //9��
					cmd2[1] = 9;
					write(led_fd,cmd2,2);
					
					if(cmd1[0]==0) //10�ŵ���
					{
						show_bmp("./you/off.bmp",600,480,200,0);
					}else //10�ŵ���
					{
						show_bmp("./you/on.bmp",600,480,200,0);
					}

					if(flag1==1)
					{	
						show_bmp("./you/bt_on.bmp",160,60,220,360); //��1������
					}else{
						
						show_bmp("./you/bt_off.bmp",160,60,220,360); //��1������
					}
					
					if(flag2==1)
					{	
						show_bmp("./you/bt2_off.bmp",160,61,420,360); //�ڶ�������
					}else{
						
						show_bmp("./you/bt2_on.bmp",160,61,420,360); //�ڶ�������
					}
					
					if(flag3==1){
						
						show_bmp("./you/bt_on.bmp",160,60,620,360); //��3������
					}else{
						
						show_bmp("./you/bt_off.bmp",160,60,620,360); //��3������
					}
				}
			}
			
			//��10յ�� �ڶ�������
			if(x>620 && x < 780 && y > 360 && y <420)
			{
				if(cmd1[0]==0)
				{
					flag3=-flag3;
					cmd1[0]=1;  //10��
					cmd1[1] = 10;
					write(led_fd,cmd1,2);
					
					if(cmd2[0]==0) //10�ŵ���
					{
						show_bmp("./you/on.bmp",600,480,200,0);
					}else //10�ŵ���
					{
						show_bmp("./you/on_1.bmp",600,480,200,0);
					}

					if(flag1==1)
					{	
						show_bmp("./you/bt_on.bmp",160,60,220,360); //��1������
					}else{
					
						show_bmp("./you/bt_off.bmp",160,60,220,360); //��1������
					}
					
					if(flag2==1)
					{	
						show_bmp("./you/bt2_off.bmp",160,61,420,360); //�ڶ�������
					}else{
						
						show_bmp("./you/bt2_on.bmp",160,61,420,360); //�ڶ�������
					}
					
					if(flag3==1){
						show_bmp("./you/bt_on.bmp",160,60,620,360); //��3������
					}else{
						
						show_bmp("./you/bt_off.bmp",160,60,620,360); //��3������
					}
				}
				else
				{
					flag3=-flag3;
					cmd1[0]=0;  //10��
					cmd1[1] =10;
					write(led_fd,cmd1,2);
					
					if(cmd2[0]==0) //9�ŵ���
					{
						show_bmp("./you/off.bmp",600,480,200,0);
					}else //9�ŵ���
					{
						show_bmp("./you/on.bmp",600,480,200,0);
					}

					if(flag1==1)
					{	
						show_bmp("./you/bt_on.bmp",160,60,220,360); //��1������
					}else{
						
						show_bmp("./you/bt_off.bmp",160,60,220,360); //��1������
					}
					
					if(flag2==1)
					{	
						show_bmp("./you/bt2_off.bmp",160,61,420,360); //�ڶ�������
					}else{
						
						show_bmp("./you/bt2_on.bmp",160,61,420,360); //�ڶ�������
					}
					
					if(flag3==1){
						
						show_bmp("./you/bt_on.bmp",160,60,620,360); //��3������
					}else{
						
						show_bmp("./you/bt_off.bmp",160,60,620,360); //��3������
					}
				}
			}
			
			
		}
		
	}
	
	
	return 0;
}