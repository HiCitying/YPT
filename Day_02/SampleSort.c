#include <stdio.h>




void Sort(int *p,int n)
{
    int i,j,tmp;
    for (i=0;i<n;i++)
        for(j=i+1;j<n;j++)
        {
            if(p[i]>p[j])
            {
                tmp=p[i];
                p[i]=p[j];
                p[j]=tmp;
            }
        }
}


void main(void)
{
    int a[5]={1,2,3,-1,8};
    Sort(a,5);
    for (int i=0;i<5;i++)
    {
        printf("%d ",a[i]);
    }
}