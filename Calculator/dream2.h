#include <conio.h>

int GetCh(void)
{
	return _getch();
}

void PutCh(char ch)
{
	_putch(ch);
}

int GetCon(void)
{
	int ret;

	ret = GetCh();
	PutCh(ret);
	return ret;
}

void PutUInt(unsigned num)
{
	char     str[16];
	unsigned strn = 0;

	for (unsigned n = num; strn < 16; n /= 10, strn++)
	{
		str[strn] = '0' + (n % 10);
		if (n < 10) break;
	}
	for (unsigned c = 0; c <= strn; c++)
	{
		PutCh(str[strn - c]);
	}
	return;
}

void PutInt(int num)
{
	if (num < 0)
	{
		PutCh('-');
		num = -num;
	}
	PutUInt(num);
	return;
}

#if 0
char* GetS(int str[100])
{
	int i;

	for (i = 0; i < 100; i++)
	{
		str[i] = '\0';
	}
	i = 0;
	while (str[i] != 13)
	{
		str[i++] = (char)GetCh();
	}
	return (char*)str;
}
#endif

void PutS(const char* str)
{
	while (*str)
	{
		PutCh(*str++);
	}
}