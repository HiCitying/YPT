#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

#define RedColor 0x00ff0000
#define BlackColor 0x002b2b2b
#define BlueColor 0x00436eee
#define YelloColor 0x00adff2f
#define PurpleColor 0x00912cee
#define PinkColor 0x00ff6eb4
#define GreenColor 0x004eee94


int  main(void)
{
    int i;


    int fd=open("/dev/fb0",O_RDWR);
    lseek(fd,0,SEEK_SET);
    int *p=mmap(NULL,480*800*4,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);



    if(fd<0)
    {
        printf("Open Error\n");
        return -1;
    }


    while (1)
    {
        lseek(fd,0,SEEK_SET);
        p=mmap(NULL,480*800*4,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
        for (i=0;i<480*800;i++)
        {
            *(p+i)=RedColor;
        }
        sleep(1);
        lseek(fd,0,SEEK_SET);
        p=mmap(NULL,480*800*4,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
        for (i=0;i<480*800;i++)
        {
            *(p+i)=BlackColor;
        }
        sleep(1);
        lseek(fd,0,SEEK_SET);
        p=mmap(NULL,480*800*4,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
        for (i=0;i<480*800;i++)
        {
            *(p+i)=BlueColor;
        }
        sleep(1);
        lseek(fd,0,SEEK_SET);
        p=mmap(NULL,480*800*4,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
        for (i=0;i<480*800;i++)
        {
            *(p+i)=YelloColor;
        }
        sleep(1);
        lseek(fd,0,SEEK_SET);
        p=mmap(NULL,480*800*4,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
        for (i=0;i<480*800;i++)
        {
            *(p+i)=PurpleColor;
        }
        sleep(1);
        lseek(fd,0,SEEK_SET);
        p=mmap(NULL,480*800*4,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
        for (i=0;i<480*800;i++)
        {
            *(p+i)=PinkColor;
        }
        sleep(1);
        lseek(fd,0,SEEK_SET);
        p=mmap(NULL,480*800*4,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
        for (i=0;i<480*800;i++)
        {
            *(p+i)=GreenColor;
        }
        sleep(1);
    }
    munmap(p,480*800*4);
    close(fd);

    return 0;
}