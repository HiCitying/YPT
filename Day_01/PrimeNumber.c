#include <stdio.h>
int  Prime(int n)
{
    int i;
    for (i=2;i<n/2;i++)
    {
        if(n%i==0)
        {
            return -1;
        }
    }
    return 1;
}

void main(void)
{
    int i;
    for(i=2;i<100;i++)
    {
        if(Prime(i)==1)
        {
            printf("%d ",i);
        }
    }

}
