#include <conio.h>

void PutStr(const char* str)
{
	while (*str) _putch(*(str++));
}


int GetInt(void)
{
	unsigned num = 0;

	while (true)
	{
		unsigned key = _getch();
		if ((key < '0') || (key > '9')) return num;

		_putch(key);
		num = num * 10 + key - '0';
	}
}


void PutInt(unsigned num)
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
		_putch(str[strn - c]);
	}

	return;
}
