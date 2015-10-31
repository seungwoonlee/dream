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
		buf[i] = zToLower(buf[i]);	// �빮�ڰ� �ԷµǸ� �ҹ��ڷ� ��ȯ�ع�����
		i++;
		if (buf[i-1] == CR)	// ���Ͱ� �ԷµǸ� �������� NULL�� �߰��ϰ� �����.
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
	if (*buf == CR)	// ù���ڷ� Enter �� ġ�� ��ģ��.
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

		if (!ParseBuf(ConsoleBuf))	// �Է��� NULL �̸� �����.
		{
			break;
		}
	}
	PutS(ConsoleBuf);	
	PutInt(count);
	return;
}