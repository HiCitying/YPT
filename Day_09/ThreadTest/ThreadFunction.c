#include "ThreadFunction.h"


int i;
void *music_thread()
{
    //int i;
    for (i=0;i<100;i++)
    {
        printf("music thread %d\n",i);
        //*p=*p+1;
    }
}

void *light_thread()
{
    //int i;
    for (i=0;i<100;i++)
    {
        printf("light thread %d\n",i);
        //*p=*p+1;
    }

}