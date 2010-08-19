#include <stdio.h> 
#include <stdlib.h> 
#include <X11/Xlib.h> 

#define WINDOW_SIZE 200 

int main (int argc, char *argv[]) 
{ 
	Display *dpy; 
	XSetWindowAttributes attributes; 
	Window win; 
	GC gc; 
	XKeyEvent event; 
	int i; 

	// 连接到 X Server，创建到 X Server 的套接字连接
	dpy = XOpenDisplay(NULL); 

	// 创建 200X200 的白色背景窗口
	attributes.background_pixel = XWhitePixel(dpy, 0);  
	win = XCreateWindow(dpy, 
						XRootWindow(dpy, 0), 
						0, 
						0, 
						WINDOW_SIZE, 
						WINDOW_SIZE, 
						0, 
						DefaultDepth(dpy, 0), 
						InputOutput, 
						DefaultVisual(dpy, 0), 
						CWBackPixel,&attributes); 
	// 选择输入事件。
	XSelectInput(dpy, win, ExposureMask | KeyPressMask ); 
	// 创建绘图上下文
	gc = XCreateGC(dpy, win, 0, NULL); 
	//Map 窗口
	XMapWindow(dpy, win); 
	// 事件主循环。主要处理 Expose 事件和 KeyPress 事件
	while(1) 
	{ 
		XNextEvent(dpy,(XEvent *)&event); 
		switch(event.type) 
		{ 
			// 处理 Expose 事件
			case Expose: 
				{ 
					// 绘制 100 个点
					for (i=0;i<WINDOW_SIZE/2;i++) 
						XDrawPoint(dpy, win, gc, WINDOW_SIZE/4+i, WINDOW_SIZE/2); 
				}
				break; 
						// 处理按键事件
			case KeyPress: 
				{ 
					XFreeGC(dpy, gc); 
					XCloseDisplay(dpy); 
					exit(0); 
				}
				break; 
			default: 
				break; 
		} 
	} 

	return(0); 
} 
