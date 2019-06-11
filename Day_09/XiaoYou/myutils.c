#include "myutils.h"


//����
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
	//1.���ļ�
	int lcd_fd = open("/dev/fb0",O_RDWR);
	if(lcd_fd < 0)
	{
		perror("open lcd_fd error\n");
	}
	
	//2.ӳ���ļ�
	p  = mmap(NULL,800*480*4,PROT_READ | PROT_WRITE, MAP_SHARED,lcd_fd,0);
	if(p == MAP_FAILED)
	{
		perror("mmap erorr\n");
	}*/
	//����Ƭ�ļ�
	int picture_fd = open(path,O_RDWR);
	if(picture_fd < 0)
	{
		perror("open picture_fd erorr\n");
	}
	
	//��궨λ��������Ƭͷ��Ϣ
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
	
	//��ӳ��
	//munmap(p,800*480*4);
	//close(lcd_fd);
}

//дһ���� �ֵĸ߶ȣ���ȣ�д�������λ��
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
				//temp[wide/8*j+i]>>=1;  ���ԭʼ����ȫ����Ϊ0
			}
		}
	}	
	
}

//ˢ��
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

//����0-9��ģ8x16

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
		//��ʾ��λ
		write_word(num[num1/10000],8,sizeof(num[num1/10000]),x,y,color);
		//��ʾǧλ
		write_word(num[num1%10000/1000],8,sizeof(num[num1%10000/1000]),x+10,y,color);
		//��ʾ��λ
		write_word(num[num1%1000/100],8,sizeof(num[num1%1000/100]),x+20,y,color);
		//��ʾʮλ
		write_word(num[num1%100/10],8,sizeof(num[num1%100/10]),x+30,y,color);
		//��ʾ��λ
		write_word(num[num1%10],8,sizeof(num[num1%10]),x+40,y,color);
	}
	else if(num1>=1000)
	{
		//��ʾǧλ
		write_word(num[num1/1000],8,sizeof(num[num1/1000]),x,y,color);
		//��ʾ��λ
		write_word(num[num1%1000/100],8,sizeof(num[num1%1000/100]),x+10,y,color);
		//��ʾʮλ
		write_word(num[num1%100/10],8,sizeof(num[num1%100/10]),x+20,y,color);
		//��ʾ��λ
		write_word(num[num1%10],8,sizeof(num[num1%10]),x+30,y,color);
	}
	
	else if(num1>=100)
	{
		//��ʾ��λ
		write_word(num[num1%1000/100],8,sizeof(num[num1%1000/100]),x,y,color);
		//��ʾʮλ
		write_word(num[num1%100/10],8,sizeof(num[num1%100/10]),x+10,y,color);
		//��ʾ��λ
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

//��ʼ������
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
	//��սṹ��
	memset(&myserial, 0, sizeof (myserial));
	//O_RDWR               
	myserial.c_cflag |= (CLOCAL | CREAD);
	//���ÿ���ģʽ״̬���������ӣ�����ʹ��
	//���� ����λ
	myserial.c_cflag &= ~CSIZE;   //�������λ
	myserial.c_cflag &= ~CRTSCTS; //��Ӳ��������
	myserial.c_cflag |= CS8;      //����λ:8

	myserial.c_cflag &= ~CSTOPB;//   //1λֹͣλ
	myserial.c_cflag &= ~PARENB;  //��ҪУ��
	//myserial.c_iflag |= IGNPAR;   //��ҪУ��
	//myserial.c_oflag = 0;  //����ģʽ
	//myserial.c_lflag = 0;  //�������ն�ģʽ

	switch (baudrate)
	{
		case 9600:
			cfsetospeed(&myserial, B9600);  //���ò�����
			cfsetispeed(&myserial, B9600);
			break;
		case 115200:
			cfsetospeed(&myserial, B115200);  //���ò�����
			cfsetispeed(&myserial, B115200);
			break;
		case 19200:
			cfsetospeed(&myserial, B19200);  //���ò�����
			cfsetispeed(&myserial, B19200);
			break;
	}
	
	/* ˢ���������,��������ܵ����� */
	tcflush(fd, TCIFLUSH);

	/* �ı����� */
	tcsetattr(fd, TCSANOW, &myserial);

	return fd;
}
