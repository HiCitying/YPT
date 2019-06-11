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
int *p; //��Ļӳ��ָ��

//unsigned char num[10][16];

//int lcd_fd;

void draw_point(int x, int y, int color); //��һ���㣬ָ����ɫ

void show_bmp(char *path,int wide, int high, int x, int y); //���һ��ͼƬ ��ȣ��߶ȣ��ӣ�x,y�����꿪ʼ

void write_word(unsigned char *buff, int wide, int high, int x, int y,int color); //дһ���� �ֵĸ߶ȣ���ȣ�д�������λ�á���ɫ

void write_num(int num1,int x,int y,int color);

void brush_screen(int x1,int y1,int x2,int y2,int color);//ˢ��

void play_music(char *music);

int init_serial(const char *file, int baudrate); //��ʼ������
#endif