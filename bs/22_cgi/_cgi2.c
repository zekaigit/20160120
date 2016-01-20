#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *data = NULL;
	float a = 0.0, b = 0.0;
	char  c = 0;
	printf("content-type:text/html\n\n");
	data = getenv("QUERY_STRING");
	if(NULL == data)
	{
		printf("error");
		return 0;
	}
	//printf("data is:%s\n", data);
	sscanf(data, "%f%c%f",&a, &c, &b);
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
		printf("error");
	}
	
	return 0;
}
