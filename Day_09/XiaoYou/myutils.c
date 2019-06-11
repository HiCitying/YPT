#include "myutils.h"


//画点
void draw_point(int x,int y,int color)
{
	if(x >= 0 && x < 800 && y >= 0 && y < 480)
	{
		*(p + 800*y + x) = color;
	}
}

void show_bmp(char *path,int wide, int high, int x, int y)
{
	/*
	//1.打开文件
	int lcd_fd = open("/dev/fb0",O_RDWR);
	if(lcd_fd < 0)
	{
		perror("open lcd_fd error\n");
	}
	
	//2.映射文件
	p  = mmap(NULL,800*480*4,PROT_READ | PROT_WRITE, MAP_SHARED,lcd_fd,0);
	if(p == MAP_FAILED)
	{
		perror("mmap erorr\n");
	}*/
	//打开照片文件
	int picture_fd = open(path,O_RDWR);
	if(picture_fd < 0)
	{
		perror("open picture_fd erorr\n");
	}
	
	//光标定位，跳过照片头信息
	lseek(picture_fd,54,SEEK_SET);
	
	unsigned char dat[800*480*3] = {0};
	
	int ret = read(picture_fd,dat,wide*high*3);
	if(ret < wide*high*3)
	{
		perror("read picture_fd erorr\n");
	}
	
	unsigned char a,b,g,r;
	a = 0;
	int color,num = 0;
	int i,j;
	for (i = 0; i < high; i++)
	{
		for(j = 0; j < wide; j++)
		{
			b = dat[num +0]; 
			g = dat[num +1]; 
			r = dat[num +2];
			
			num = num +3;
			
			color =  a << 24 | r << 16 | g << 8 | b;
			
			draw_point(x + j,y + high-i -1,color);
		}
	}
	close(picture_fd);
	
	//解映射
	//munmap(p,800*480*4);
	//close(lcd_fd);
}

//写一个字 字的高度，宽度，写入的坐标位置
void write_word(unsigned char *buff, int wide, int high, int x, int y,int color)
{
	int i,j,k;	
	for(j=0;j<high;j++)
	{   
		for (i=0;i<wide/8;i++)
		{		
			for(k=7;k>=0;k--)
			{
				if(buff[wide/8*j+i]&(1<<(7-k)))
				{
					draw_point(8*i+k+x,j+y,color);
				}
				//temp[wide/8*j+i]>>=1;  会把原始数组全部改为0
			}
		}
	}	
	
}

//刷屏
void brush_screen(int x1,int y1,int x2,int y2,int color)
{
	int i,j;
	for(i=y1;i<y2;i++)
	{
		for(j=x1;j<x2;j++)
		{
			draw_point(j,i,color);
		}
	}
		
}

//数字0-9的模8x16

unsigned char num[10][16] = {{0x00,0x00,0x00,0x18,0x24,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00,0x00},
							{0x00,0x00,0x00,0x08,0x38,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00},
							{0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x02,0x04,0x08,0x10,0x20,0x42,0x7E,0x00,0x00},
							{0x00,0x00,0x00,0x3C,0x42,0x42,0x02,0x04,0x18,0x04,0x02,0x42,0x42,0x3C,0x00,0x00},
							{0x00,0x00,0x00,0x04,0x0C,0x0C,0x14,0x24,0x24,0x44,0x7F,0x04,0x04,0x1F,0x00,0x00},
							{0x00,0x00,0x00,0x7E,0x40,0x40,0x40,0x78,0x44,0x02,0x02,0x42,0x44,0x38,0x00,0x00},
							{0x00,0x00,0x00,0x18,0x24,0x40,0x40,0x5C,0x62,0x42,0x42,0x42,0x22,0x1C,0x00,0x00},
							{0x00,0x00,0x00,0x7E,0x42,0x04,0x04,0x08,0x08,0x10,0x10,0x10,0x10,0x10,0x00,0x00},
							{0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x24,0x18,0x24,0x42,0x42,0x42,0x3C,0x00,0x00},
							{0x00,0x00,0x00,0x38,0x44,0x42,0x42,0x42,0x46,0x3A,0x02,0x02,0x24,0x18,0x00,0x00}};
	
void write_num(int num1,int x,int y,int color)
{
	if(num1>=10000)
	{
		//显示万位
		write_word(num[num1/10000],8,sizeof(num[num1/10000]),x,y,color);
		//显示千位
		write_word(num[num1%10000/1000],8,sizeof(num[num1%10000/1000]),x+10,y,color);
		//显示百位
		write_word(num[num1%1000/100],8,sizeof(num[num1%1000/100]),x+20,y,color);
		//显示十位
		write_word(num[num1%100/10],8,sizeof(num[num1%100/10]),x+30,y,color);
		//显示个位
		write_word(num[num1%10],8,sizeof(num[num1%10]),x+40,y,color);
	}
	else if(num1>=1000)
	{
		//显示千位
		write_word(num[num1/1000],8,sizeof(num[num1/1000]),x,y,color);
		//显示百位
		write_word(num[num1%1000/100],8,sizeof(num[num1%1000/100]),x+10,y,color);
		//显示十位
		write_word(num[num1%100/10],8,sizeof(num[num1%100/10]),x+20,y,color);
		//显示个位
		write_word(num[num1%10],8,sizeof(num[num1%10]),x+30,y,color);
	}
	
	else if(num1>=100)
	{
		//显示百位
		write_word(num[num1%1000/100],8,sizeof(num[num1%1000/100]),x,y,color);
		//显示十位
		write_word(num[num1%100/10],8,sizeof(num[num1%100/10]),x+10,y,color);
		//显示个位
		write_word(num[num1%10],8,sizeof(num[num1%10]),x+20,y,color);
	}
	
	else if(num1>=10)
	{
		write_word(num[num1/10],8,sizeof(num[num1/10]),x,y,color);
		
		write_word(num[num1%10],8,sizeof(num[num1%10]),x+10,y,color);
	}
	
	else if(num1>=0)
	{	
		write_word(num[num1],8,sizeof(num[num1]),x,y,color);
	}	
}


void play_music (char *music)
{
	execlp("madplay","madplay","TSLS.mp3",NULL);
}

//初始化串口
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
