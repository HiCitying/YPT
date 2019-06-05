#include "Head.h"
#include "TWord.h"

void TWord(unsigned int *pword, unsigned int (*sp)[Bwidth])
{
    unsigned int tmp;
    unsigned int mode[Bwidth*Bhigh]={0};
    int n=0;
    int Bit=8;
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
    n=0;
    for (i=0;i<Bhigh;i++)
    {
        for (j=0;j<Bwidth;j++)
        {
            sp[i][j]=mode[n];
            n++;
        }
    }

}