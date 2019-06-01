#include<stdio.h>
void exchange(int *a,int *b)
{
	int tmp;
	tmp=*a;
	*a=*b;
	*b=tmp;
}

int main(void)
{
	int a=3;
	int b=4;
	printf("交换前：a:%d b:%d\n",a,b);
	exchange(&a,&b);
	printf("交换后：a:%d b:%d\n",a,b);
	return 0;
}
