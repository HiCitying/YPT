#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{	
	int led_fd = open("/dev/led_drv",O_RDWR);
	if(led_fd < 0)
	{
		perror("open led_fd erorr\n");
	}
	
	unsigned char cmd[2];
	cmd[0] = 1;  //cmd[0]存的是灯的状态1是亮 0是灭
	cmd[1] = 10; //cmd[1]存的是灯的编号
	
	write(led_fd,cmd,2);
	
	close(led_fd);
	
	return 0;
}