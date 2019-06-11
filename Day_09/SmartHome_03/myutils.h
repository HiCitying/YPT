#ifndef __PRINT_H__
#define __PRINT_H__


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<stdio.h>
#include <sys/mman.h>
#include <errno.h>
#include <linux/input.h>
#include <termios.h>
#include <string.h>

//int lcd_fd;
int *p; //屏幕映射指针

//unsigned char num[10][16];

//int lcd_fd;

void draw_point(int x, int y, int color); //画一个点，指定颜色

void show_bmp(char *path,int wide, int high, int x, int y); //输出一张图片 宽度，高度，从（x,y）坐标开始

//void write_word(unsigned char *buff, int wide, int high, int x, int y,int color); //写一个字 字的高度，宽度，写入的坐标位置、颜色
//
//void write_num(int num1,int x,int y,int color);
//
//void brush_screen(int x1,int y1,int x2,int y2,int color);//刷屏
//
//void play_music(char *music);

//int init_serial(const char *file, int baudrate); //初始化串口

void control_led();
#endif