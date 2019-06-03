
#include "initial.h"
void initial(int (*p)[L],int color)
{
    int i,j;
    for (i=0;i<W;i++)
    {
        for (j=0;j<L;j++)
        {
            p[i][j]=color;
        }
    }
}