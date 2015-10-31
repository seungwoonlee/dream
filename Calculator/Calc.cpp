#include "dream2.h"
#include "zString.h"
#include <string.h>

const char BUF_MAX = 100;
const char ENTER = 13;
const char CR = 13;
const char LF = 10;

void GetB(char buf[BUF_MAX])
{	
	int i = 0;

	while (i < BUF_MAX)
	{
		buf[i] = GetCh();
		PutCh(buf[i]);
		i++;
		if (buf[i-1] == CR)
		{
			buf[i] = '\0';
			break;
		}
	}	
	PutCh(CR);
	PutCh(LF);
	return;
}

void main(void)
{
	char buf[BUF_MAX] = "12345";
	char buf2[BUF_MAX] = "67890+-*/% ";
	char* cp;

	int x = 0;	

	//	strncpy(buf2+4, buf, 5);
	//	zStrncpy(buf2+4, buf, 5);
	//	strncpy(buf2+5, " ", 3);
	//	zStrncpy(buf2+5, " ", 1);
	//	strcat(buf, buf2);
	strncat(buf, buf2, 3);
	strtok(buf2, "+");
	cp = strtok(NULL, "*");
	//	zStrcat(buf, buf2);
	//	zStrcat(buf, buf2);
	//	strncat(buf2, buf, 2);




	x = +1 + +1;
	x = -1 * 1;

	GetB(buf);
	PutInt(-10000);
	zStrcmp("", "");

	GetCh();

#if 0
	buf[0] = GetCh();
	PutCh(buf[0]);
	buf[1] = GetCh();
	PutCh(buf[1]);
	buf[2] = GetCh();
	PutCh(buf[2]);
	buf[3] = GetCh();
	PutCh(buf[3]);
	buf[4] = GetCh();
	PutCh(buf[4]);
#endif
	return;
}