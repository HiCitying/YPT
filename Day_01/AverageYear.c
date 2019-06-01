#include <stdio.h>
void main(void)
{
    int year;
    printf("Imput Yeat:");
    scanf("%d",&year);
    if(year%4==0&&year%100!=0||year%400==0)
    {
        printf("Yes\n");
    } else
    {
        printf("No\n");
    }
}