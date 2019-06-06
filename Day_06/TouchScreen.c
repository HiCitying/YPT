#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>
#include <linux/input.h>

void main(void)
{

    int input_fd;
    int ret;
    struct input_event event;

    input_fd= open("/dev/input/event0",O_RDWR);


    while (1)
    {
        ret = read(input_fd,&event, sizeof(struct input_event));
        if(input_fd < 0)
        {
            printf("open input_fd erorr\n");
        }
        if(ret < sizeof(event))
        {
            perror("read input_fd erorr\n");
        }

        if(event.type==EV_ABS)
        {
            printf("Touch Event\n");
            printf("Touch The X And Y :%d\n",event.value);

        }
    }


    close(input_fd);




}