#include "Head.h"
#include "TWord.h"


// bwidth 位宽度
// bhigh  位高度
// Abyte  总字节数
// sp     数组存放位状态
//ALByte  总字节数

void TWord(unsigned int *pword,int ALByte,int bwidth,int bhigh ,unsigned int (*sp)[800])
{
    unsigned int tmp;
    //int size=bhigh*bhigh;
    unsigned int mode[H*W]={0};
    int n=0;
    //int Bit=8;
    int i,j;
    for (i=0;i<ALByte;i++)
    {
        for (j=0;j<Bit;j++)
        {
            tmp=pword[i];
            tmp=tmp>>(Bit-j-1);
            if(tmp&1)
            {
                mode[n]=1;

            }
            n++;


        }
    }

    for (i=0,n=0;i<bhigh;i++)
    {
        for (j=0;j<bwidth;j++)
        {
            sp[i][j]=mode[n];
            n++;
        }
    }

}