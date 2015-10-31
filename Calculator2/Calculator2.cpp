#include "dream3.h"
#include <string.h>

const int MAX_VAR_NAMESIZE = 2;

int GetS(char* buf)
{
	int i = 0;

	while (i < MAX_BUF)
	{
		buf[i]  = GetCh();
		if (!( zIsAlnum(buf[i]) || buf[i] == ENTER || buf[i] == BACKSPACE || buf[i] == '+' || buf[i] == '-' || buf[i] == '*' || buf[i] == '/' || buf[i] == '%' || buf[i] == '(' || buf[i] == ')' || buf[i] == '=' ))
		{
			continue;
		}		
		PutCh(buf[i]);
		buf[i] = zToLower(buf[i]);	// 대문자가 입력되면 소문자로 변환해버려라
		i++;
		if (buf[i-1] == CR)	// 엔터가 입력되면 마지막에 NULL을 추가하고 멈춘다.
		{
			buf[i] = '\0';
			break;
		}
	}
	PutCh(CR);
	PutCh(LF);
	return i;
}

char* ParseBuf(char* buf)
{

	char* cp = buf;
	int iPosEq = 0;
	char left[MAX_VAR_NAMESIZE];
	char right[MAX_BUF2];

	if (*buf == '\0')
	{
		return (char*)0;
	}
	if (*buf == CR)	// 첫글자로 Enter 를 치면 마친다.
	{
		zStrcpy(buf, "> Quit\n");
		return buf;
	}
	
	iPosEq = zStrnchr(buf, '=');
	zStrncpy2(left, buf, iPosEq);
	cp = zStrchr(buf, '=');
	zStrcpy(right, cp+1);
		
//	buf = strchr(buf, '=');
	return buf;
}

void main(void)
{
	char ConsoleBuf[MAX_BUF2] = { 0, };

	int count;
	PutS("> Console Calculator\n");
	PutS("> Available Command :  print [a]|[z] , quit , <Enter>\n> \n");

	while (1)
	{
		PutS("> ");		// Prompt
		count = GetS(ConsoleBuf);

		if (!ParseBuf(ConsoleBuf))	// 입력이 NULL 이면 멈춘다.
		{
			break;
		}
	}
	PutS(ConsoleBuf);	
	PutInt(count);
	return;
}