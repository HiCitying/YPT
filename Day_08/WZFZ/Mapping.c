#include "Mapping.h"


int *Mapping(int fd,int pywidth,int pyhigh)
{

    int *p = mmap(NULL,pywidth*pyhigh*PX,PROT_READ | PROT_WRITE, MAP_SHARED,fd,0);
    if(p == MAP_FAILED)
    {
        perror("mmap erorr\n");
    }
    return p;
}

void DeMapping(int *py,int pywidth,int pyhigh)
{
    munmap(py,pywidth*pyhigh*PX);
}