#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>

#include "ThreadFunction.h"
void main(void)
{

    int x=0;
    //int i=0;

    pthread_t tid1;
    pthread_t tid2;

    int rtid1;
    int rtid2;

    memset(&tid1, 0, sizeof(tid1));
    memset(&tid2, 0, sizeof(tid2));

    rtid1=pthread_create(&tid1,NULL,(void*)music_thread,NULL);
    if(rtid1==0)
    {
        printf("music thread creat success\n");
    } else
    {
        printf("music thread creat fail\n");
    }
    rtid1=pthread_create(&tid2, NULL,(void *)light_thread,NULL);
    if(rtid2==0)
    {
        printf("light thread creat success\n");
    } else
    {
        printf("light thread creat fail\n");
    }
//    while (1)
//    {
//        printf("zzzzzzzzzzzzzzzzz%d\n",x);
//        x+=1;
//    }


}