#ifndef _UART_DEBUG_H_
#define _UART_DEBUG_H_

#define MAX_FILENAMESIZE 			20
#define MAX_LINESIZE 				5





#define kitty_print(line,_msg_)	{my_printf(__FILE__,__LINE__);kitty_p _msg_;}
#define k_print(_x_) kitty_print(MAX_LINESIZE,_x_)


void my_printf(char* filepath, int line);
void kitty_p( const char *const fmt, ... );



#endif
