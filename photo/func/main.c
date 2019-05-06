#include"lcd.h"
#include"bmp.h"
#include"linklist.h"

//需要一个函数进行触碰操作
int Input()
{
	int dev_fd=open("/dev/input/event0",O_RDONLY);
	if(dev_fd==-1)
	{
		perror("dev error:");
		return -1;
	}
	struct input_event event;
	int x_last,x_now;
	int div;
	int flag=0;
	while(1)
	{
		int r = read(dev_fd,&event,sizeof(struct input_event));
		if(r != sizeof(struct input_event))
		{
			continue;
		}
		//判断是否触碰，若触碰则记录该位置的值
		if(event.type == EV_ABS && event.code == ABS_X&&flag==0)
		{
			x_last = event.value;
		}
		//触碰到则flag置1
		if(event.type==0x01&&event.value==1)
		{
			flag++;
		}
		//手松开则记录离开位置
		if(event.type == EV_ABS && event.code == ABS_X&&flag==1)
		{
			x_now = event.value;
		}
		//手松开则退出即x_last与x_now被记录
		if(event.type==0x01&&event.value==0)
		{
			break;
		}
	}
	//返回手离开的点与手触碰的点的位置值得差值
	div=x_now-x_last;
	printf("x_now-x_last=%d-%d\n",x_now,x_last);
	return div;
	close(dev_fd);
}

int main(int argc,char *argv[])
{
	//初始化LCD
	Init_lcd();
	
	//创建链表
	struct List*list=Create_linklist();
	
	//读取目录
	list=search_dir(list,argv[1]);
	struct inode*p=list->first;
	int re;
	//触摸屏操作
	while(1)
	{
		if(strcmp(p->data+strlen(p->data)-4,".bmp")==0)
		{
			bmp_display(p->data);
			printf("%s\n",p->data);
		}
		if(strcmp(p->data+strlen(p->data)-4,".jpg")==0)
		{
			jpg_display(p->data);
			printf("%s\n",p->data);
		}
		//接收返回值
		re=Input();
		//若手指左滑则移到下一张
		if(re<-30)
		{
			p=p->next;
			if(p==NULL)
			{
				p=list->first;
			}
		}
		//若手指右滑则移到上一张
		if(re>30)
		{
			p=p->prev;
			if(p==NULL)
			{
				p=list->last;
			}
		}
		if(re==0)
		{
			continue;
		}
	}
	
	//关闭文件
	close_lcd();
}