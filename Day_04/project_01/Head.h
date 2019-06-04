#ifndef _HEAD_H_
#define _HEAD_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

#define W 800
#define H 480

#define BmpOff 54

#define FBOPATH "/dev/fb0"
#define BMPPATH "/home/HIMA/RedC.bmp"


typedef unsigned char uchar;
typedef unsigned int uint;

void T24BmpTo32(int fd_p,uint *bcolor);
void DrawSA(int fd,int *bcolor);


#endif