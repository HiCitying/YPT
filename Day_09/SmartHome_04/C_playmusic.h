#ifndef _C_PLAYMUSIC_H_
#define _C_PLAYMUSIC_H_


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <linux/input.h>
#include <error.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>

//int *p1;
//char *music;
void C_show_screen(int *p,int x,int y,int wide,int high,int color);
void C_draw_point(int *p,int x, int y, int color);
void C_show_bmp(int *p,char *path,int wide, int high, int x, int y);
void play_music(char *music);
void read_touch();
void C_show_word(int *p,char *word, int x, int y,int wide,int wordsize,int color);

void C_playmusic(int *p);




#endif