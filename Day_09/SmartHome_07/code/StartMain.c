#include"PLH.h"
#include"Show_Bmp.h"

void StartMain(void)
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
	
	
	int plh_1_fd = open("./plh_1.bmp",O_RDWR);
	int plh_2_fd = open("./plh_2.bmp",O_RDWR);
	int plh_3_fd = open("./plh_3.bmp",O_RDWR);
	int plh_4_fd = open("./plh_4.bmp",O_RDWR);
	if(plh_1_fd < 0)
	{	
		perror("open plh_1_fd erorr\n");
		//printf("open picture_fd erorr\n");
	}
	
	if(plh_2_fd < 0)
	{	
		perror("open plh_3_fd erorr\n");
		//printf("open picture_fd erorr\n");
	}
	
	if(plh_3_fd < 0)
	{	
		perror("open plh_3_fd erorr\n");
		//printf("open picture_fd erorr\n");
	}
	
	if(plh_4_fd < 0)
	{	
		perror("open plh_4_fd erorr\n");
		//printf("open picture_fd erorr\n");
	}
	
	//3.打开图片文件以及读取数据和处理 显示
	//show_bmp("./plh_2.bmp",200,120,0,0);
	Show_Bmp(plh_1_fd,p,800,480,0,0);
	sleep(2);
	Show_Bmp(plh_2_fd,p,200,120,150,100);
	sleep(2);
	Show_Bmp(plh_3_fd,p,200,120,500,200);
	sleep(2);
	Show_Bmp(plh_4_fd,p,200,120,255,300);
	sleep(2);
	
	
	
	//4.收尾工作
	munmap(p,800*480*4);
	close(lcd_fd);
	
}