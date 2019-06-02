#include <stdio.h>
void Sort(int *p)
{
    int i,j;
    for(i=0;i<5;i++)
        for(j=0;j<5-i-1;j++)
        {
            if(p[j]>p[j+1])
            {
                p[j]^=p[j+1];
                p[j+1]=p[j]^p[j+1];
                p[j]^=p[j+1];

            }
        }

}

void InsertSortArray ( int *p, int n)
{
    int i;
    for (i = 1; i < n; i++)// 循环从第二个数组元素开始
    {
        int temp = p[i];//temp标记为未排序的第一个元素
        while (i >= 0 && p[i - 1] > temp) //将temp与已排序元素从大到小比较，寻找temp应插入的元素
        {
            p[i] = p[i - 1];
            i--;
        }
        p[i] = temp;
    }

}

void main(void)
{
    int a[5],i;
    printf("Input Five Number:");
    for(i=0;i<5;i++)
        scanf("%d",&a[i]);
    //Sort(a);
    InsertSortArray(a,5);
    printf("\nAfter Sort:");
    for (i=0;i<5;i++)
        printf("%d ",a[i]);
}