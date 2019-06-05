#ifndef _HEAD_H_
#define _HEAD_H_

#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>


#define W 800
#define H 480

#define FB0PATH "/dev/fb0"

void draw_image(int fd,int x0,int y0,int ph,int pw,int color);

#endif