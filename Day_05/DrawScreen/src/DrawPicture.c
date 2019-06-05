void DrawPicture(int fd,int *bcolor)
{
    lseek(fd,0,SEEK_SET);
    int *p=mmap(NULL,480*800*4,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);


    int i,j;
    for (i=0;i<H;i++)
    {
        for (j=0;j<W;j++)
        {
            *(p+i*W+j)=bcolor[i*W+j];
        }
    }
}