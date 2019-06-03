#include "exchange.h"

void exchange(int *p,int *q)
{
    int tmp;
    tmp=*p;
    *p=*q;
    *q=tmp;
}