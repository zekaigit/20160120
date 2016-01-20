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
	函数名：get_html_data
	描述：	获取浏览器(html)发送来的数据
	参数：	用于存储浏览器(html)发送来的数据的内存地址
	返回值：浏览器(html)发送来的数据长度
	备注：	无
*/
int get_html_data(char *buff)
{
	//先判断下浏览器是通过什么方法发送数据给cgi的，通过REQUEST_METHOD环境变量可以获取到
	char *method = getenv("REQUEST_METHOD");
	if(NULL != method)
	{
		if(0 == strcmp("GET", method))
		{
			//如果是GET方法发送的，数据通过QUERY_STRING环境变量获取到
			char *data = getenv("QUERY_STRING");
			if(NULL != data)
			{
				strncpy(buff, data, strlen(data));
				return strlen(buff);
			}
			
		}
		else if(0 == strcmp("POST", method))
		{
			//如果是POST方法放松的，数据通过CONTENT_LENGTH环境变量获取到
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
*功能:	URL的解码
*参数:	result: URL的解码结果；
		url_src：URL的编码
*返回值:URL的解码结果地址
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
	函数名：main
	描述：	处理浏览器数据并返回处理结果
	参数：	无
	返回值：无
	备注：	浏览器发送的数据格式为led?为获取led的状态；如果为led:1(1-3):1(0-1)，则为设置led的，这边统一返回led:0(0-15)，如果设置失败返回led:-1
*/
int main(void)
{
	//获取浏览器数据，保存到buff中
	char buff[512] = "";
	char buff_decode[1024] = {0};
	char buff_recv[1024] = {0};

	get_html_data(buff);
	//k_print是对串口发送数据的封装，串口是特殊的终端，串口发送的数据会在终端中显示，这样就可以利用k_print来打印调试信息了。
	k_print(("buff = %s\n", buff));
	//printf已经被重定向了，结果不会打印在标准输出上，会返回给浏览器，printf第一句打印必须是content-type:text/html， 这是一个头部信息，不会作为实际数据返给浏览器
	printf("content-type:text/html\n\n");


	//1:url decoder
	url_decode(buff_decode, buff);
	//利用k_print打印转码之后的数据
	k_print(("buff_decode = %s\n", buff_decode));

	//将网页的数据传给server程序处理，并且通过buff_recv接收返回数据
	comm_with_server(buff_decode, buff_recv);
	k_print(("buff_recv = %s\n", buff_recv));

	//cgi程序把server处理之后的结果返回给网页
	printf("server:%s", buff_recv);
	
	return 0;
	
}
