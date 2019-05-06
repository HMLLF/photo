#ifndef _LINKLIST_H_
#define _LINKLIST_H_

#include<stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<jpeglib.h>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
struct inode
{
	char data[128];
	struct inode*next;
	struct inode*prev;
};

struct List
{
	struct inode*first;
	struct inode*last;
};
struct List*search_dir(struct List*list,char*pathname);
struct List*add_a_node(struct List*h,char *buf);
struct List*Create_linklist();
int jpg_display(char*s);


#endif