#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <stdarg.h>
#include "uart_debug.h"

static char dbg_filename[MAX_FILENAMESIZE], vsbuf[512];

struct termios options, oldoptions;
/*************************************************************
* 功能：	串口初始化程序
* 参数：	串口设备文件序号
* 返回值：	串口设备文件描述符
**************************************************************/

int k_uart_init(int num)
{
	int fd = -1;
	
	char *serial_dev[] = {"/dev/s3c2410_serial0",
						"/dev/s3c2410_serial1",
						"/dev/s3c2410_serial2",
						"/dev/s3c2410_serial3",
						"/dev/ttyUSB0",
						"/dev/ttyUSB1"};
	fd = open(serial_dev[num], O_RDWR);
	tcgetattr(fd, &oldoptions);
	tcgetattr(fd, &options);
	
	cfsetispeed(&options, B115200);
	cfsetospeed(&options, B115200);

	options.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|IGNCR|ICRNL|IXON);
	
	options.c_cflag &= ~PARENB; //无奇偶校验位
	options.c_cflag &= ~CSTOPB;	//停止位为1位
	options.c_cflag &= ~CSIZE;	
	options.c_cflag |= CS8;		//数据位为8位
	
	options.c_lflag &= ~(ICANON|ECHO|ECHOE|ISIG);
	tcsetattr(fd,TCSANOW,&options);
	return fd;
}


/*************************************************************
* 功能：	串口恢复程序
* 参数：	串口设备文件序号
* 返回值：	串口设备文件描述符
**************************************************************/

void k_uart_uninit(int fd)
{
	tcsetattr(fd,TCSANOW,&oldoptions);
	close(fd);
}





void my_printf(char* filepath, int line)
 {
 
	 int filepath_len;
	 char *ptr = vsbuf;
 
	 filepath_len = strlen(filepath);
 
	 if(filepath_len>=MAX_FILENAMESIZE)
	 {
		 strncpy(dbg_filename, filepath + filepath_len - MAX_FILENAMESIZE, MAX_FILENAMESIZE);
	 }
	 else
	 {
		 strncpy(dbg_filename, filepath, filepath_len);
	 }
 
	 sprintf(ptr, " %*.*s, %0*d ", MAX_FILENAMESIZE, MAX_FILENAMESIZE, dbg_filename, MAX_LINESIZE, line);
 
	 ptr += MAX_FILENAMESIZE+MAX_LINESIZE+3;
	 
	 strncpy(ptr, "  -----=> ", 10);
 }




 /* 
 * ===	FUNCTION  ======================================================================
 *		   Name:  void kitty_p( const char *const fmt, ... )
 *	Description:  print format info in stdout and log
 *		return :  void
 *	  parameter:  const char *const fmt, ...:format info
 * =====================================================================================
 */
 void kitty_p( const char *const fmt, ... )
 {
	 // FILE* fp_log = 0;
	 
	 va_list Argument;
	 // char head_buf[] = "kdebug say:";
	 
	 va_start(Argument, fmt);
		 vsprintf(&vsbuf[MAX_FILENAMESIZE+MAX_LINESIZE+3+10], fmt, Argument);
		 va_end(Argument);
		 
	
	int fd_uart = k_uart_init(0);
		 
	write(fd_uart, vsbuf, strlen(vsbuf));
	// printf("%s", vsbuf);
	
	k_uart_uninit(fd_uart);
 }


