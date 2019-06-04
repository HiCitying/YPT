#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

#define RedColor 0x00ff0000
#define BlackColor 0x002b2b2b
#define BlueColor 0x00436eee


int  main(void)
{
    int i,j;
    //int color[480*800];
    unsigned char buf_p[480*800*3];
    unsigned char buf_r[480*800*4];

    int fd=open("/dev/fb0",O_RDWR);
    int fd_p=open("/home/HIMA/RedC.bmp",O_RDWR);

    lseek(fd,0,SEEK_SET);
    int *p=mmap(NULL,480*800*4,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);


    lseek(fd_p,54,SEEK_SET);
    read(fd_p,buf_p,480*800*3);

    //int *pf=color;
    int b_1;
    int b_2;
    int b_3;
    int tmp=0;

//    for(i=0;i<480*800*3;i+=3){
//        b_1=(int)buf_p[2+i];
//        b_2=(int)buf_p[1+i];
//        b_3=(int)buf_p[i];
//        *(p+tmp)=(b_1<<16|b_2<<8|b_3);
//        tmp=tmp+1;
//    }

    for(i=479;i>=0;i--){
        for (j=0;j<800;j++)
        {
            b_1=(int)buf_p[2+tmp];
            b_2=(int)buf_p[1+tmp];
            b_3=(int)buf_p[tmp];
            *(p+i*800+j)=(b_1<<16|b_2<<8|b_3);
            tmp=tmp+3;
        }


    }







    if(fd<0)
    {
        printf("Open Error\n");
        return -1;
    }



//    for (i=0;i<480*800;i++)
//    {
//        *(p+i)=pf[i];
//    }

    munmap(p,480*800*4);

    close(fd);

    return 0;
}