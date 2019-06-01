#include <stdio.h>
void main(void)
{
    int x;
    int a,b,c;
    int i;
    for (i=100;i<1000;i++)
    {
        a=i%10;
        b=(i%100)/10;
        c=i/100;
        if(i==(a*a*a+b*b*b+c*c*c))
        {
            printf("%d ",i);
        }
    }
}