#include <stdio.h>
#include <termios.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//初始化串口
//file: 串口所对应的文件名
//baudrate：波特率
int init_serial(const char *file, int baudrate)
{ 
	int fd;
	
	fd = open(file, O_RDWR);
	if (fd == -1)
	{
		perror("open device error:");
		return -1;
	}

	struct termios myserial;
	//清空结构体
	memset(&myserial, 0, sizeof (myserial));
	//O_RDWR               
	myserial.c_cflag |= (CLOCAL | CREAD);
	//设置控制模式状态，本地连接，接受使能
	//设置 数据位
	myserial.c_cflag &= ~CSIZE;   //清空数据位
	myserial.c_cflag &= ~CRTSCTS; //无硬件流控制
	myserial.c_cflag |= CS8;      //数据位:8

	myserial.c_cflag &= ~CSTOPB;//   //1位停止位
	myserial.c_cflag &= ~PARENB;  //不要校验
	//myserial.c_iflag |= IGNPAR;   //不要校验
	//myserial.c_oflag = 0;  //输入模式
	//myserial.c_lflag = 0;  //不激活终端模式

	switch (baudrate)
	{
		case 9600:
			cfsetospeed(&myserial, B9600);  //设置波特率
			cfsetispeed(&myserial, B9600);
			break;
		case 115200:
			cfsetospeed(&myserial, B115200);  //设置波特率
			cfsetispeed(&myserial, B115200);
			break;
		case 19200:
			cfsetospeed(&myserial, B19200);  //设置波特率
			cfsetispeed(&myserial, B19200);
			break;
	}
	
	/* 刷新输出队列,清除正接受的数据 */
	tcflush(fd, TCIFLUSH);

	/* 改变配置 */
	tcsetattr(fd, TCSANOW, &myserial);

	return fd;
}
int main(void)
{
	int serial_fd = init_serial("/dev/ttySAC1",9600);
	
	while(1)
	{
		unsigned char cmd[3] = {0xA5,0x83,0x28};
		unsigned char buf[24] = {0};
		
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
		printf("lxu = %d\n",lxu);
		
		//温度
		int t = buf[13] << 8 | buf[14];
		t = t / 100;
		printf("t = %d\n",t);
		
		//气压
		int p = buf[15] << 24 | buf[16] << 16 | buf[17] << 8 | buf[18];
		p = p / 100;
		printf("p = %d\n",p);
		
		//湿度
		int hum = buf[19] << 8 | buf[20];
		hum = hum / 100;
		printf("hum = %d\n",hum);
		
		//海拔
		int h = buf[21] << 8 | buf[22];
		printf("h = %d\n",h);
		
		usleep(200000);
		
	}
	
	close(serial_fd); 
}









