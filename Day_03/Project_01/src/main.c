#include "exchange.h"
#include <stdio.h>

void main(void)
{
    int a=2;
    int b=3;
    exchange(&a,&b);
    printf("%d %d\n",a,b);
}