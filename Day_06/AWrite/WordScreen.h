#ifndef _WORDSCREEN_H_
#define _WORDSCREEN_H_

#define W 800
#define H 480

void WordScreen(int fd,int x0,int y0,int ph,int pw,int color, unsigned int (*status)[W]);


#endif