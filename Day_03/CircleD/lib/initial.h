#ifndef _INITIAL_H_
#define _INITIAL_H_



#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define RedColor 0x00ff0000
#define BlackColor 0x002b2b2b
#define BlueColor 0x00436eee
#define YelloColor 0x00adff2f
#define PurpleColor 0x00912cee
#define PinkColor 0x00ff6eb4
#define GreenColor 0x004eee94



#define W 480
#define L 800


void writecolor(int fd,int (*color)[L],int n);

void initial(int (*p)[L],int color);

#endif