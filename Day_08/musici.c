#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{	
	//显示图片
	//显示数字
	//检测触屏，而且要一直检测
	//所以要实现并发同时进行，所以要创建进程
	//这时我检测到要播放音乐
	char *music[3] = {"wqs.mp3","jn.mp3","by.mp3"};
	int pid = fork();
	if(pid == 0)			//子进程要执行的代码
	{
		execlp("madplay","madplay",music[0],NULL);
		exit(0);
	}
	
	sleep(20);
	//继续检测触屏
	//如果这时我要切换到下一首
	unsigned char cmd[32];
	sprintf(cmd,"kill -9 %d",pid);
	system(cmd);
	pid = fork();
	if(pid == 0)		//子进程要执行的代码
	{
		execlp("madplay","madplay",music[1],NULL);
		exit(0);
	}
	
	sleep(20);
	//这时我要切换到上一首
	sprintf(cmd,"kill -9 %d",pid);
	system(cmd);
	pid = fork();
	if(pid == 0)		//子进程要执行的代码
	{
		execlp("madplay","madplay",music[0],NULL);
		exit(0);
	}
	
	sleep(20);
	//这时我要暂停一下
	sprintf(cmd,"kill -19 %d",pid);
	system(cmd);
	
	sleep(20);
	//这时我要继续播放
	sprintf(cmd,"kill -18 %d",pid);
	system(cmd);
	
	while(1);	//这是不要让主进程推出去，否则子进程不会继续
	
	return 0;
	
	
	
	return 0;
}