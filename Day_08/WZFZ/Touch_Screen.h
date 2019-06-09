#ifndef _TOUCH_SCREEN_H_
#define _TOUCH_SCREEN_H_

#include <fcntl.h>
#include <error.h>
#include <linux/input.h>
#include <stdio.h>

void Touch_Screen(int *py,int picture_fd);
#endif