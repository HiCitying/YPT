#include <stdio.h>
int BNum(int n)
{
    int tmp=0;
    while (n)
    {
        if(n&1)
            tmp++;
        n>>=1;
    }
    return tmp;
}

void main(void)
{
    int x,y;
    printf("Input X:");
    scanf("%d",&x);
    y=BNum(x);
    printf("%d\n",y);
}