#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <error.h>
#include <linux/input.h>

int main(void)
{
	//1.�򿪴������ļ�
	int touch_fd = open("/dev/input/event0",O_RDWR);
	if(touch_fd < 0)
	{
		perror("open touch_fd error\n");
	}
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
		printf("ev.type = %d , ev.code = %d, ev.value = %d\n",ev.type,ev.code,ev.value);
		
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
			
		}
		
	}
}