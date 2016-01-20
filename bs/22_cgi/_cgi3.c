#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *dataLen = NULL,buff[100] = {0};
	float a = 0.0, b = 0.0;
	char  c = 0;
	int len = 0;
	
	printf("content-type:text/html\n\n");
	dataLen = getenv("CONTENT_LENGTH");
	if(NULL == dataLen)
	{
		printf("error1");
		return 0;
	}
	else
	{
		len = atoi(dataLen);
		if(len > 0)
		{
			if(NULL == fgets(buff, len+1, stdin))
			{
				printf("error2");
				return 0;
			}
			else
			{
				sscanf(buff, "%f%c%f",&a, &c, &b);
				if('+' == c)
				{
					printf("%f", a+b);
				}
				else if('-' == c)
				{
					printf("%f", a-b);
				}
				else
				{
					printf("error3");
				}
			}	
		}
	}
	
	return 0;
}
