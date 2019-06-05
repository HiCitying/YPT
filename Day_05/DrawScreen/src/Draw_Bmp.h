#ifndef _DRAW_BMP_H_H
#define _DRAW_BMP_H_H

#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

typedef unsigned char uchar;
typedef unsigned char uint;

void draw_point(int x,int y,int color)
void show_bmp(char *path,int wide,int high,int x,int y)

#endif