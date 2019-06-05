#ifndef _WORDSCREEN_H_
#define _WORDSCREEN_H_

#define WSwidth 16
#define WSHigh  16

void WordScreen(int fd,int x0,int y0,int ph,int pw,int color, unsigned int (*status)[16]);
#endif