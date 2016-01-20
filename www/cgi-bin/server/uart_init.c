#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>

static struct termios option_old;

/*************************************************************
* ���ܣ�	���ڳ�ʼ������
* ������	�����豸�ļ����
* ����ֵ��	�����豸�ļ�������
**************************************************************/
int uart_init(char *devname)
{
	int uart_fd;
	struct termios option_new;
	
	uart_fd = open(devname, O_RDWR);
	if(uart_fd < 0)
	{
		perror("open_dev");
		_exit(-1);
	}
	tcgetattr(uart_fd, &option_old);		//���洮������
	tcgetattr(uart_fd, &option_new);

	cfsetispeed(&option_new, B19200);		//������Ϊ115200
	cfsetospeed(&option_new, B19200);		//������Ϊ115200
	option_new.c_cflag &= ~CSIZE;			//��������λʱ�ȹر���ʷ����
	option_new.c_cflag |= CS8;				//����λΪ8λ
	option_new.c_cflag &= ~CSTOPB;			//1λֹͣλ
	option_new.c_cflag &= ~PARENB;			//����żУ��λ
	option_new.c_lflag &= ~(ICANON);		//�Ǳ�׼ģʽ
	// option_new.c_lflag &= ~ECHO;			//�ػ��ԣ���ʹ��GPRSģ��ʱ��ػ���
	option_new.c_lflag |= ECHO;				//������
	tcsetattr(uart_fd, TCSANOW, &option_new);
	return uart_fd;
}

/*************************************************************
* ���ܣ�	���ڷ���ʼ������
* ������	�����豸�ļ�������
* ����ֵ��	��
**************************************************************/
void uart_uninit(int uart_fd)
{
	/*��ԭ��������*/
	tcsetattr(uart_fd, TCSANOW, &option_old);
	
	/*�رմ���*/
	close(uart_fd);
}

/*************************************************************
* ���ܣ�	���ڷ����ַ���
* ������	uart_fd�������豸�ļ�������
			str�������͵��ַ�
* ����ֵ��	��
**************************************************************/
void uart_send_str(int uart_fd, char *str)
{
	int ret;
	
	ret = write(uart_fd, str, strlen(str));
	if(ret < 0)
	{
		perror("write");
	}
}

/*************************************************************
* ���ܣ�	���ڶ�һ���ַ��������趨��ʱ���ڶ�����������������
* ������	uart_fd�������豸�ļ�������
			buffer��������ݵ��ڴ���׵�ַ
			len��������ݵ��ڴ�ռ�Ĵ�С
			timeout_ms����ʱʱ��(��λ��ms)
* ����ֵ��	
			�ɹ���ʵ�ʶ������ַ���
			ʧ�ܣ�-1
**************************************************************/
int uart_readline(int uart_fd, char *buffer, int len, int timeout_ms)
{
	char c = '\0';
	fd_set fds;
	struct timeval tv;
	int i;
	int ret;

	memset(buffer, 0, len);
	for(i=0; i<len && c != '\n'; i++){
		tv.tv_sec = 0;
		tv.tv_usec = timeout_ms*1000;
		FD_ZERO(&fds);
		FD_SET(uart_fd, &fds);
		ret = select(FD_SETSIZE, &fds, NULL, NULL, &tv);
		if(ret < 0){
			perror("seclect");
			return -1;
		}else if(ret > 0){
			ret = read(uart_fd, &c, 1);
			if(ret < 0)
			{
				perror("read");
			}
		}else{
			return -1;
		}
		*buffer++ = c;
		//printf("c=%c\n", c);
	}
	return i;
}
