#ifndef _MAPPING_H_
#define _MAPPING_H_

#include <stdio.h>
#include <errno.h>
#include <sys/mman.h>


#define PX 4
int *Mapping(int fd,int pywidth,int pyhigh);
// pywidth 映射屏幕宽度
// pyhigh  映射屏幕高度
// PX      单个屏幕像点字节数
void DeMapping(int *py,int pywidth,int pyhigh);


#endif