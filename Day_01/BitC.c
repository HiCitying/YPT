#include <stdio.h>
void main(void)
{
    int x=1056;
    int n;
    unsigned char a=32;
    unsigned char b=4;
    unsigned char c=0;
    unsigned char d=0;
    n=(a|b<<8|c<<16|d<<24);
    //printf("%d\n",n);
    if(n==x)
    {
        printf("Yes\n");
    }
    printf("%d",n);
}