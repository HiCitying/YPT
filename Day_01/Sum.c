#include <stdio.h>
int Sum(int n)
{
    int i=1,sum=0;
    while (i<=n)
    {
        sum=sum+i;
        i++;
    }
    return sum;
}

void main(void)
{
    int x,s;
    printf("Import x:");
    scanf("%d",&x);
    s=Sum(x);
    printf("\nAnswer:%d\n",s);
}