#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{	
	//��ʾͼƬ
	//��ʾ����
	//��ⴥ��������Ҫһֱ���
	//����Ҫʵ�ֲ���ͬʱ���У�����Ҫ��������
	//��ʱ�Ҽ�⵽Ҫ��������
	char *music[3] = {"wqs.mp3","jn.mp3","by.mp3"};
	int pid = fork();
	if(pid == 0)			//�ӽ���Ҫִ�еĴ���
	{
		execlp("madplay","madplay",music[0],NULL);
		exit(0);
	}
	
	sleep(20);
	//������ⴥ��
	//�����ʱ��Ҫ�л�����һ��
	unsigned char cmd[32];
	sprintf(cmd,"kill -9 %d",pid);
	system(cmd);
	pid = fork();
	if(pid == 0)		//�ӽ���Ҫִ�еĴ���
	{
		execlp("madplay","madplay",music[1],NULL);
		exit(0);
	}
	
	sleep(20);
	//��ʱ��Ҫ�л�����һ��
	sprintf(cmd,"kill -9 %d",pid);
	system(cmd);
	pid = fork();
	if(pid == 0)		//�ӽ���Ҫִ�еĴ���
	{
		execlp("madplay","madplay",music[0],NULL);
		exit(0);
	}
	
	sleep(20);
	//��ʱ��Ҫ��ͣһ��
	sprintf(cmd,"kill -19 %d",pid);
	system(cmd);
	
	sleep(20);
	//��ʱ��Ҫ��������
	sprintf(cmd,"kill -18 %d",pid);
	system(cmd);
	
	while(1);	//���ǲ�Ҫ���������Ƴ�ȥ�������ӽ��̲������
	
	return 0;
	
	
	
	return 0;
}