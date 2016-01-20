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
//��ȡʱ��
int get_sys_time(char *time_data)
{
	time_t now;
	char *snow = NULL;

	
	now = time(NULL);
	snow = ctime(&now);
	//ʱ���ַ����л���\n������ʱȥ��\n
	strncpy(time_data, snow, strlen(snow)-1);
	
	return OK;
}

//gtk�̳߳�ʼ��
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
	//������������
	pthread_t tid_rfid;
	pthread_t tid_cgi;

	//�̳߳�ʼ��
	gtk_thread_init();
	//gtk��ʼ��
	gtk_init(&argc, &argv);
	//gtkͼ�ν����ʼ��
	ui_init(&g_window);


	//���ݿ��ʼ��
	db_init(DB_NAME);

	//���������߳�
	pthread_create(&tid_rfid, NULL, thread_rfid, NULL);
	//��������cgi�����߳�
	pthread_create(&tid_rfid, NULL, thread_cgi, NULL);

	//��ʾ������	
	gtk_widget_show_all(g_window.window);

	//gtk���¼�ѭ��
	gtk_main();


	//�̼߳���������Դ
	pthread_join(tid_rfid, NULL);
	pthread_join(tid_cgi, NULL);
	pthread_mutex_destroy(&g_mutex_rfid);

	return 0;
}


