#include"PLH.h"
#include"Show_Bmp.h"

void EndMian(void)
{
	//1.打开文件init_lcd()
	int lcd_fd = open("/dev/fb0",O_RDWR);
	if(lcd_fd < 0)
	{	
		perror("open lcd_fd error\n");
		//printf("open lcd_fd error\n");
	}
	
	//2.映射文件
	int *p  = mmap(NULL,800*480*4,PROT_READ | PROT_WRITE, MAP_SHARED,lcd_fd,0);
	if(p == MAP_FAILED)
	{	
		perror("mmap erorr\n");
		//printf("mmap erorr\n");
	}
	
	
	int plh_9_fd = open("./plh_9.bmp",O_RDWR);
	if(plh_9_fd < 0)
	{	
		perror("open plh_9_fd erorr\n");
		//printf("open picture_fd erorr\n");
	}
	
	Show_Bmp(plh_9_fd,p,800,480,0,0);
	
	munmap(p,800*480*4);
	close(lcd_fd);
}