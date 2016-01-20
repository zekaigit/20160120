#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <gtk/gtk.h>
#include <glade/glade.h>
#include <stdlib.h>

#include "sqlite3.h"
#include "uart_init.h"
#include "server.h"
//获取时间
int get_sys_time(char *time_data)
{
	time_t now;
	char *snow = NULL;

	
	now = time(NULL);
	snow = ctime(&now);
	//时间字符串中会有\n，复制时去掉\n
	strncpy(time_data, snow, strlen(snow)-1);
	
	return OK;
}

//gtk线程初始化
void gtk_thread_init(void)
{
	if(FALSE == g_thread_supported())
	{ 
		g_thread_init(NULL); 
	}
	gdk_threads_init();

	pthread_mutex_init(&g_mutex_rfid, NULL);

}

int main(int argc, char *argv[])
{
	//变量定义区域
	pthread_t tid_rfid;
	pthread_t tid_cgi;

	//线程初始化
	gtk_thread_init();
	//gtk初始化
	gtk_init(&argc, &argv);
	//gtk图形界面初始化
	ui_init(&g_window);


	//数据库初始化
	db_init(DB_NAME);

	//创建读卡线程
	pthread_create(&tid_rfid, NULL, thread_rfid, NULL);
	//创建处理cgi程序线程
	pthread_create(&tid_rfid, NULL, thread_cgi, NULL);

	//显示主窗口	
	gtk_widget_show_all(g_window.window);

	//gtk主事件循环
	gtk_main();


	//线程及锁回收资源
	pthread_join(tid_rfid, NULL);
	pthread_join(tid_cgi, NULL);
	pthread_mutex_destroy(&g_mutex_rfid);

	return 0;
}


