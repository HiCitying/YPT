#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define RedColor 0x00ff0000
#define BlackColor 0x002b2b2b
#define BlueColor 0x00436eee
#define YelloColor 0x00adff2f
#define PurpleColor 0x00912cee
#define PinkColor 0x00ff6eb4
#define GreenColor 0x004eee94


int  main(void)
{
    int i,j,k;
    int Red[480][800];
    int Black[480][800];
    int Blue[480][800];
    int Yello[480][800];
    int Purple[480][800];
    int Pink[480][800];
    int Green[480][800];

    int fd=open("/dev/fb0",O_RDWR);


    for (i=0;i<480;i++)
    {
        for (j=0;j<800;j++)
        {
            Red[i][j]=RedColor;
            Black[i][j]=BlackColor;
            Blue[i][j]=BlueColor;
            Yello[i][j]=YelloColor;
            Purple[i][j]=PurpleColor;
            Pink[i][j]=PinkColor;
            Green[i][j]=GreenColor;

        }
    }

    if(fd<0)
    {
        printf("Open Error\n");
        return -1;
    }

    int fp;

    while (1)
    {
        switch (k%7){
            case 0:
            {
                lseek(fd,0,SEEK_SET);
                fp=write(fd,Red,480*800*4);
                k++;
                if(fp>0)
                {
                    printf("Write Success\n");
                } else
                {
                    printf("Write Fail\n");
                }
                sleep(1);
                break;
            }
            case 1:
            {
                lseek(fd,0,SEEK_SET);
                fp=write(fd,Black,480*800*4);
                k++;
                if(fp>0)
                {
                    printf("Write Success\n");
                } else
                {
                    printf("Write Fail\n");
                }
                sleep(1);
                break;
            }
            case 2:
            {
                lseek(fd,0,SEEK_SET);
                fp=write(fd,Blue,480*800*4);
                k++;
                if(fp>0)
                {
                    printf("Write Success\n");
                } else
                {
                    printf("Write Fail\n");
                }
                sleep(1);
                break;
            }
            case 3:
            {
                lseek(fd,0,SEEK_SET);
                fp=write(fd,Yello,480*800*4);
                k++;
                if(fp>0)
                {
                    printf("Write Success\n");
                } else
                {
                    printf("Write Fail\n");
                }
                sleep(1);
                break;
            }
            case 4:
            {
                lseek(fd,0,SEEK_SET);
                fp=write(fd,Purple,480*800*4);
                k++;
                if(fp>0)
                {
                    printf("Write Success\n");
                } else
                {
                    printf("Write Fail\n");
                }
                sleep(1);
                break;
            }
            case 5:
            {
                lseek(fd,0,SEEK_SET);
                fp=write(fd,Pink,480*800*4);
                k++;
                if(fp>0)
                {
                    printf("Write Success\n");
                } else
                {
                    printf("Write Fail\n");
                }
                sleep(1);
                break;
            }
            case 6:
            {
                lseek(fd,0,SEEK_SET);
                fp=write(fd,Green,480*800*4);
                k++;
                if(fp>0)
                {
                    printf("Write Success\n");
                } else
                {
                    printf("Write Fail\n");
                }
                sleep(1);
                break;
            }
            default:
            {
                break;
            }
        }
    }

    close(fd);

    return 0;
}