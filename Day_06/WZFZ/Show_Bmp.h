#ifndef _SHOW_BMP_H_
#define _SHOW_BMP_H_

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#define PWIDTH 800  //屏幕宽度
#define PHIGH  480  //屏幕高度




void Show_Bmp(int fd,int *py,int wide, int high, int x, int y);

// wide 宽度
// high 高度
// x    初始横坐标
// y    初始纵坐标
// fd   文件描述符
//py    映射操作指针



#endif