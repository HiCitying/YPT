#include "ClearScreen.h"

//ph 高度
//pw 宽度
//color 颜色

void ClearScreen(int *py,int color)
{
    int x,y;
    for(x=0;x<SHIGH;x++)
    {
        for(y=0;y<SWIDTH;y++)
        {
            *(py+x*SWIDTH+y)=color;
        }
    }


}
