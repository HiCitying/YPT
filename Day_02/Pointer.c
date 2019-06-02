#include <stdio.h>

void Exchange(int *x,int *y)
{
    *x^=*y;
    *y=*x^*y;
    *x^=*y;
}

void Exchange_1(int *x,int *y)
{
    *x+=*y;
    *y=*x-*y;
    *x=*x-*y;
}

void Exchange_2(int *x,int *y)
{
    (*x)*=*y;
    *y=*x/(*y);
    (*x)/=*y;
}

void main(void)
{
    int a=1;
    int b=2;
    Exchange_2(&a,&b);
    printf("a:%d b:%d\n",a,b);
}