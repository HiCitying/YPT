#include <stdio.h>

void MaxArray(int (*p)[3],int *x,int *y,int *tmp)
{
    int i,j;
    *tmp=p[0][0];
    for (i=0;i<3;i++)
        for (j=0;j<3;j++)
        {
            if(p[i][j]<*tmp)
            {
                *tmp=p[i][j];
                *x=i;
                *y=j;
            }

        }
}

void main(void)
{
    int i,j;
    int tmp;
    int a[3][3]={0,1,2,1,-1,-3,2,3,-1};
    MaxArray(a,&i,&j,&tmp);
    printf("The Min is a[%d][%d]  %d\n",i,j,tmp);

}
