#ifndef _WORDSCREEN_H_
#define _WORDSCREEN_H_

#define WSwidth 24
#define WSHigh  20

void WordScreen(int fd,int x0,int y0,int ph,int pw,int color, unsigned int (*status)[WSwidth]);
#endif