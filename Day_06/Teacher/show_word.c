#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>
//智能2个字的模16x16
unsigned char mo[2][32] = {{0x20,0x00,0x3E,0x7C,0x48,0x44,0x08,0x44,0xFF,0x44,0x14,0x44,0x22,0x7C,0x40,0x00,
							0x1F,0xF0,0x10,0x10,0x10,0x10,0x1F,0xF0,0x10,0x10,0x10,0x10,0x1F,0xF0,0x10,0x10},
							{0x10,0x40,0x24,0x44,0x42,0x48,0xFF,0x70,0x01,0x40,0x00,0x42,0x7E,0x42,0x42,0x3E,
							0x42,0x00,0x7E,0x44,0x42,0x48,0x42,0x70,0x7E,0x40,0x42,0x42,0x4A,0x42,0x44,0x3E}};
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
							
int *p = NULL;
//画点
void draw_point(int x, int y, int color)
{
	if(x >= 0 && x < 800 && y >= 0 && y < 480)
	{
		*(p + 800* y + x) = color;
	}
}
//刷屏
void brush_screen(int color)
{
	int i,j;
	for(i = 0; i < 480; i++)
	{
		for(j = 0; j < 800; j++)
		{
			draw_point(j,i,color);
		}
	}
}


//显示字
void show_word(char *word, int x, int y,int wide,int wordsize,int color)
{
	int i,j;
	int x1; //横坐标
	int y1;	//纵坐标
	int by = wide/8;
	for(i = 0; i < wordsize; i++)	//遍历每个字节
	{
		for(j = 7; j >= 0; j--)		//遍历某个字节的每个位
		{
			if(word[i] & (1 << j))
			{
				x1 = x + 8 *(i % by)/*确定区域是在哪个字节*/+ 7 -j; /*确定是字节中的哪个位*/
				y1 = y + i / by;
				draw_point(x1,y1,color);//在对应位置的像素点上 上色
			}
		}
	}
}

void show_num(int num1,int x,int y,int color)
{
	if(num1/100)
	{
		//显示百位
		show_word(num[num1/100],x,y,8,sizeof(num[num1/100]),color);
		//显示十位
		show_word(num[num1%100/10],x+10,y,8,sizeof(num[num1%100/10]),color);
		//显示个位
		show_word(num[num1%10],x+20,y,8,sizeof(num[num1%10]),color);
	}
}

				
int main(void)
{
	//1.打开屏幕文件
	int lcd_fd = open("/dev/fb0",O_RDWR);
	if(lcd_fd < 0)
	{
		perror("open lcd_fd errno\n");
	}
	//2.映射文件
	p = mmap(NULL,800*480*4,PROT_READ | PROT_WRITE,MAP_SHARED,lcd_fd,0);
	if(p == MAP_FAILED)
	{
		perror("mmap errno\n");
	}
	//3.刷屏
	brush_screen(0x00FFFFFF);
	//4.显示汉字
	show_word(mo[0],0,0,16,sizeof(mo[0]),0x00000000);
	
	//5.显示数字
	show_word(num[1],200,140,8,sizeof(num[0]),0x00FF0000);
	//6.显示一个三位数 比如289；
	int indat = 0;
	scanf("%d",&indat);
	show_num(indat,400,240,0x00FF0000);
	//7.收尾工作
	munmap(p,800*480*4);
	close(lcd_fd);
}							
							
							
							
							
							