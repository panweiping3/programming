/*********************************************************************
 *                
 * Filename:      pfile.c
 * Version:       1.0
 * Description:   Demo for Linux LIST utility
 * Compilation:   gcc –D__KERNEL__ -I/usr/src/linux/include pfile.c
 * Status:        Stable
 * Author:        Yang Shazhou<pubb@163.net>
 * Created at:    Thu Jul 15 13:50:33 2004
 * Modified at:   Thu Jul 15 14:39:03 2004
 * Modified by:   Yang Shazhou<pubb@163.net>
 * 
 *     Copyright (c) 2004 Yang Shazhou, All Rights Reserved.
 *     
 *     This program is free software; you can redistribute it and/or 
 *     modify it under the terms of the GNU General Public License as 
 *     published by the Free Software Foundation; either version 2 of 
 *     the License, or (at your option) any later version.
 * 
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *     GNU General Public License for more details.
 * 
 *     You should have received a copy of the GNU General Public License 
 *     along with this program; if not, write to the Free Software 
 *     Foundation, Inc., 59 Temple Place, Suite 330, Boston, 
 *     MA 02111-1307 USA
 *     
 ********************************************************************/
#include <linux/list.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char *argv[])
{
	LIST_HEAD(list);		//定义存放文件内容的链表
	FILE *fp;

	struct file_store {
		char c;
		struct list_head node;
	} *pstore;

	if(argc<2){
		printf("usage: pfile <filename> <[r]>\n");
		return -1;
	}
	if(!(fp=fopen(argv[1],"rb"))){
		printf("fopen(%s) error\n",argv[1]);
	        return -1;
	}

	/* 读文件到链表 */
	while(1){
		if(!(pstore=(struct file_store *)malloc(sizeof(struct file_store))))
			break;
		pstore->c=fgetc(fp);
		if(feof(fp)){
			free(pstore);
			break;
		}
		list_add_tail(&pstore->node,&list); 		//将本字符插入链表中
	}
	fclose(fp);

	/* 遍历链表，输出链表中的节点个数，即文件字符数 */
	int count=0;
	struct list_head *p;
	list_for_each(p,&list){
		count++;
	}
	printf("%s has altogether %d character(s)\n",argv[1],count);

	/* 根据命令行参数正向/反向遍历链表，输出链表中存放的字符，同时释放各节点 */
	if(argc>2 && !strcasecmp(argv[2],"r")){
		struct list_head *p;
		list_for_each_entry_reverse(pstore,&list,node){		//反向遍历，没有保护
			p=pstore->node.next;
			list_del(&pstore->node);
			putchar(pstore->c);
			free(pstore);
			/* 如果没有这一句，将报segmentation fault */
pstore=list_entry(p,struct file_store,node);	//取数据项
		}
	}else{
		struct file_store *p;
		list_for_each_entry_safe(pstore,p,&list,node){		//正向遍历，有保护
			list_del(&pstore->node);
			putchar(pstore->c);
			free(pstore);
		}
	}

	return 0;
}
