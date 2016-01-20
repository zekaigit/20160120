#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


#include "./uart_debug/uart_debug.h"
#include "./server/server.h"

/*
	��������get_html_data
	������	��ȡ�����(html)������������
	������	���ڴ洢�����(html)�����������ݵ��ڴ��ַ
	����ֵ�������(html)�����������ݳ���
	��ע��	��
*/
int get_html_data(char *buff)
{
	//���ж����������ͨ��ʲô�����������ݸ�cgi�ģ�ͨ��REQUEST_METHOD�����������Ի�ȡ��
	char *method = getenv("REQUEST_METHOD");
	if(NULL != method)
	{
		if(0 == strcmp("GET", method))
		{
			//�����GET�������͵ģ�����ͨ��QUERY_STRING����������ȡ��
			char *data = getenv("QUERY_STRING");
			if(NULL != data)
			{
				strncpy(buff, data, strlen(data));
				return strlen(buff);
			}
			
		}
		else if(0 == strcmp("POST", method))
		{
			//�����POST�������ɵģ�����ͨ��CONTENT_LENGTH����������ȡ��
			char *data = getenv("CONTENT_LENGTH");
			if(NULL != data)
			{
				int len = atoi(data);
				if(len >= 0)
				{
					fgets(buff, len, stdin);
					return len;
				}
			}
			
		}
		
	}
	
	
	return -1;
	
}



/*********************************************************************
*����:	URL�Ľ���
*����:	result: URL�Ľ�������
		url_src��URL�ı���
*����ֵ:URL�Ľ�������ַ
*********************************************************************/
char *url_decode(char *result, const char *url_src)
{
	const char *src = url_src;
	char *dst = result;
	while(*src)
	{
		if(*src == '%')
		{
			char tmp[3];
			tmp[0] = src[1];
			tmp[1] = src[2];
			tmp[2] = 0;
			*dst = strtoul(tmp, NULL, 16);
			src += 2;
		}
		else if(*src=='+')
		{
			*dst=strtoul("20",NULL,16);
		}
		else
			{
				*dst = *src;
			}
		dst++;
		src++;
	}
	*dst = 0;
	return result;
}



/*
	��������main
	������	������������ݲ����ش�����
	������	��
	����ֵ����
	��ע��	��������͵����ݸ�ʽΪled?Ϊ��ȡled��״̬�����Ϊled:1(1-3):1(0-1)����Ϊ����led�ģ����ͳһ����led:0(0-15)���������ʧ�ܷ���led:-1
*/
int main(void)
{
	//��ȡ��������ݣ����浽buff��
	char buff[512] = "";
	char buff_decode[1024] = {0};
	char buff_recv[1024] = {0};

	get_html_data(buff);
	//k_print�ǶԴ��ڷ������ݵķ�װ��������������նˣ����ڷ��͵����ݻ����ն�����ʾ�������Ϳ�������k_print����ӡ������Ϣ�ˡ�
	k_print(("buff = %s\n", buff));
	//printf�Ѿ����ض����ˣ���������ӡ�ڱ�׼����ϣ��᷵�ظ��������printf��һ���ӡ������content-type:text/html�� ����һ��ͷ����Ϣ��������Ϊʵ�����ݷ��������
	printf("content-type:text/html\n\n");


	//1:url decoder
	url_decode(buff_decode, buff);
	//����k_print��ӡת��֮�������
	k_print(("buff_decode = %s\n", buff_decode));

	//����ҳ�����ݴ���server����������ͨ��buff_recv���շ�������
	comm_with_server(buff_decode, buff_recv);
	k_print(("buff_recv = %s\n", buff_recv));

	//cgi�����server����֮��Ľ�����ظ���ҳ
	printf("server:%s", buff_recv);
	
	return 0;
	
}
