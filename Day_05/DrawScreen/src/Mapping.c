#include <stdio.h>

int *Mapping(int size,int fd,int *p_map)
{
    p_map=mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED,lcd_fd,0);
    if(p_map==MAP_FAILED)
    {
        perror("mmap error\n");
    }
    return p_map;
}

void DeMapping(int size,int *p_map)
{
    munmap(p_map,size);
}

