#include "initial.h"

int main(void)
{
    int fd;

    int Red[W][L];
    int Black[W][L];
    int Blue[W][L];
    int Yello[W][L];
    int Purple[W][L];
    int Pink[W][L];
    int Green[W][L];

    initial(Red,RedColor);
    initial(Black,BlackColor);
    initial(Blue,BlueColor);
    initial(Yello,YelloColor);
    initial(Purple,PurpleColor);
    initial(Pink,PinkColor);
    initial(Green,GreenColor);

    fd=open("/dev/fb0",O_RDWR);

    if(fd<0)
    {
        printf("Open Error\n");
        return -1;
    }

    while (1)
    {
        writecolor(fd,Red,L*W*4);
        writecolor(fd,Black,L*W*4);
        writecolor(fd,Blue,L*W*4);
        writecolor(fd,Yello,L*W*4);
        writecolor(fd,Purple,L*W*4);
        writecolor(fd,Pink,L*W*4);
        writecolor(fd,Green,L*W*4);
    }

    close(fd);

    return 0;


}