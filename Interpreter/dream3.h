#include <conio.h>
#include <string.h>

const int MAX_BUF = 1000;
const int MAX_BUF2 = 100;	// 1000 ���� �����ϸ� �ʹ� Ŀ�� ����װ� �����ϹǷ� �ӽ÷� ����.


/* Prototypes */

int GetCh(void);

void PutCh(char ch);

int GetCon(void);		// �ܼ��� ���� �ѱ��ڸ� �Է� �޴´�. 

void PutInt(int num);	// ������� (������ ��)

void PutS(const char* str);

//int GetS(char* buf);	// ���ڿ� �Է¹޴´�. ����ũ��� MAX_BUF�� ������, ���ϰ��� �Էµ� ���ڿ��� �����̴�.

int zStrlen(const char *str);

char* zStrcpy(char* dst, char* src);

char* zStrncpy(char* dst, const char* src, unsigned int cnt);

char* zStrncpy2(char* dst, const char* src, unsigned int cnt);	// n �� src���ڿ����̺��� ������ ���ʿ� NULL�� ä���� �������� ä������� �ٲ� ����

char* zStrcat(char* dst, const char* src);

char* zStrncat(char* dst, const char* src, unsigned int cnt);

int zStrcmp(const char *str1, const char *str2);

int zStrncmp(const char *str1, const char *str2, unsigned int cnt);

char* zStrchr(char* str, int ch);

int zStrnchr(char* str, int ch);	// ch �� ó�� ã������ �ε����� ����

char* zStrstr(char* str, char* key );

int zStrdelchr(char* str, int ch);		// ch ���ڸ� �˻��ؼ� ���ڸ� �����. ch�� ���ٸ� �׳� str�״�� ����, ���ϰ��� ch ���ڰ� ���� ����

int zStrdelpos(char* str, int pos);		// pos ��°�� ���ڸ� �����.

char* zStrreplace(char* dst, char* key, char* add);	// dst ���� key�� ã�Ƽ� add �� �ٲ�ġ���Ѵ�

int zAtoi(const char *str);

char* zItoa(int num, char* str);

int zIsAlpha(int c);

int zIsDigit(int c);

int zIsAlnum(int c);	

int zIsDelimiter(int c);

int zToLower(int c);

int zToUpper(int c);

/* Function Bodies */

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

void PutS(const char* str)
{
	while (*str)
	{
		PutCh(*str++);
	}
}

int zStrlen(const char *str)
{
	int i = 0;
	while (1)
	{
		if ( str[++i] == '\0')
		{
			break;
		}
	}
	return i;
}

char* zStrcpy(char* dst, char* src)
{
	char* cp = dst;

	while (*cp++ = *src++)
	{
		;
	}
	return dst;
}

char* zStrncpy(char* dst, const char* src, unsigned int cnt)
{
	char *cp = dst;

	while (cnt && (*cp++ = *src++))
	{
		cnt--;
	}
	if (cnt)
	{
		while (--cnt)
		{
			*cp++ = '\0';
		}
	}
	return dst;
}

char* zStrncpy2(char* dst, const char* src, unsigned int cnt)
{
	char *cp = dst;

	while (cnt && (*cp++ = *src++))
	{
		cnt--;
	}
	if (cnt)
	{
		while (--cnt)
		{
			*cp++ = '\0';
		}
		*cp = '\0';	// cnt == 0 ���� ���ϵɶ� ���� NULL �߰��ϴ� zStrncpy() ��������
	}
	return dst;
}

char* zStrcat(char* dst, const char* src)
{
	char *cp = dst;
	while (*cp++ != '\0')
	{
		;
	}
	cp--;
	while (*cp++ = *src++)
	{
		;
	}
	return dst;
}

char* zStrncat(char* dst, const char* src, unsigned int cnt)
{
	char* cp = dst;
	while (*cp++ != '\0')
	{
		;
	}
	cp--;
	while (cnt-- != 0)
	{
		if (!(*cp++ = *src++))
			return cp;
	}
	*cp = '\0';
	return cp;
}

int zStrcmp(const char *str1, const char *str2)
{
	int ret = 0;

	while( ! (ret = *str1 - *str2) && *str1)
	{
		++str1, ++str2;
	}
	if (ret < 0)
	{
		ret = -1;
	}
	else if (ret > 0) 
	{
		ret = 1;
	}
	return(ret);
}

int zStrncmp(const char *str1, const char *str2, unsigned int cnt)
{
	while (*str1)
	{
		if (*str2 == '\0' || cnt == 0)
		{
			return 0;
		}		
		if ((*str1++ != *str2++) || (cnt-- == 0))
		{
			break;
		}
	}
	//return ( (*str1 - *str2) < 0 ? -1 : 1 );
	return *str1 - *str2;	// ���Ⱑ �� strcmp() �� strncmp �� �ٸ��� �𸣰���. �׻� *str1 - *str2 �� �ƴ� ��Ģ�� �𸣰���, Ư����� +/- 1 ���̰� �� 
}

char* zStrchr(char* str, int ch)	// ch ���ڸ� ó��ã�� ���� ����
{
	while (*str && *str != ch)
	{
		str++;
	}
	if (*str == ch)
	{
		return str;
	}
	return (char*)0;
}

int zStrnchr(char* str, int ch)	// ch ���ڸ� ó��ã�� �������� index �� ����
{
	unsigned int cnt = 0;
	while (*str && *str != ch)
	{
		cnt++;
		str++;
	}
	if (*str == ch)
	{
		return cnt;
	}
	return 0;
}

int zStrdelchr(char* str, int ch)		// ch ���ڸ� �˻��ؼ� ���ڸ� �����. ch�� ���ٸ� �׳� str�� �״�� �д�. ���ϰ��� ch ���ڸ� ������ġ ������� ���ٸ� 0 �� ����
{
	int pos;

	pos = zStrnchr(str, ch);
	if (!pos)
	{
		return 0;
	}
	zStrdelpos(str, pos);
	
	return pos;
}

int zStrdelpos(char* str, int pos)		// pos ��°�� ���ڸ� �����.
{
	char buf[MAX_BUF2] = { 0, };

	if (pos < 0 || pos > zStrlen(str))
	{	
		return 0;
	}
	zStrncpy(buf, str, pos);
	zStrcat(buf, str+pos+1);
	zStrcpy(str, buf);
	return pos;
}

char* zStrstr(char* str, char* key)
{ 
	int length = zStrlen(key);

	while (1)
	{
		str = zStrchr(str, key[0]); 
		if (str == '\0') 
		{
			return '\0';
		}
		if (!zStrncmp(str, key, length))
		{
			return (char*) str; 
		}
		str++; 
	} 
}

char* zStrreplace(char* dst, char* key, char* add)	// dst ���� key�� ã�Ƽ� add �� �ٲ�ġ���Ѵ�
{
	char* cp = dst;
	char* temp;
	int idx = 0;
	int length = 0;

	char buf[MAX_BUF2] = { 0, };

	if (!(temp = zStrstr(dst, key)))
	{
		return (char*)0;	// ��ã���� NULL ����
	}
	while (temp-- != cp)
	{
		idx++;
	}
	zStrncat(buf, dst, idx);
	zStrcat(buf, add);

	length = zStrlen(key);
	zStrcat(buf, dst+idx+length);
	zStrcpy(dst, buf);

	return cp;
}

char* zStrreplaceWhole(char* dst, char* key, char* add)	// dst ���� key �� ������ �ܾ ã�Ƽ� add �� �ٲ�ġ���Ѵ�. zStrreplace()�� �ܾ�ӿ� ���Ե� �͵� �ٲ۴�.
{
	int base = 0;
	int offset = 0;
	char buf[MAX_BUF2] = { 0, };
	char buf2[MAX_BUF2] = { 0, };

	while (dst[base])
	{
		while (!zIsDelimiter(dst[base+offset]))
		{
			buf[offset] = dst[base+offset];
			buf[offset+1] = '\0';
			offset++;
		}
		offset++;
		if (!zStrcmp(buf, key))
		{
			zStrncpy(buf2, dst, base);
			zStrcat(buf2, add);
			zStrcat(buf2, dst+base+zStrlen(key));
			zStrcpy(dst, buf2);
			return dst;
		}
		base = base + offset;
		offset = 0;
	}
	return (char*)0;
}

int zAtoi(const char *str)
{
	int ret = 0;
	int sign = 0;

	while (1)	// ���ڷ� �����ϴ°��� �ƴҼ� �ִ� �պκ�
	{
		if (*str == '\0')
		{
			return 0;
		}		
		else if (zIsDigit(*str))
		{
			break;			
		}
		else if (*str == '+')
		{
			if (sign != 0)
			{
				return 0;
			}
			sign = 1;
			str++;
			continue;
		}
		else if (*str == '-')
		{
			if (sign != 0)
			{
				return 0;
			}
			sign = -1;
			str++;
			continue;
		}
		str++;
		return 0;
	}
	while (1)	// ���ںκ� ����
	{
		if (*str == '\0' || ret > 0x80000000 )
		{
			break;
		}
		if (!zIsDigit(*str))	// �߰��� ���ڰ� �ƴѰ� ������ �ٷ� 0 ����
		{
			return 0;
		}
		ret = ret*10 + (*str++ - '0');
	}
	return (sign == 0 ? 1 : sign) * ret;
}

char* zItoa(int num, char* str)
{
	char* cp = str;
	char* first;
	char temp;
	int next;	

	if (num < 0)
	{
		*cp++ = '-';
		num = -num;
	}
	first = cp;
	do {
		next = num % 10;
		num = num / 10;
		*cp++ = next + '0';
	} while (num > 0);
	*cp-- = '\0';
	do {
		temp = *cp;
		*cp = *first;
		*first = temp;
		--cp;
		++first;
	} while (first < cp);

	return cp;
}

int zIsDelimiter(int c)
{
	switch (c)
	{
		case '+':
			return 1;
		case '-':
			return 1;
		case '*':
			return 1;
		case '/':
			return 1;
		case '%':
			return 1;
		case '(':
			return 1;
		case ')':
			return 1;
		case '"':
			return 1;
		case '=':
			return 1;
		case '>':
			return 1;
		case '<':
			return 1;
		case '?':
			return 1;
		case ':':
			return 1;
		case '&':
			return 1;
		case '|':
			return 1;
		case '~':
			return 1;
		case '!':
			return 1;
		case '\0':
			return 1;
		default:
			return 0;
	}
}

int zIsDigit(int c)
{
	return (c >= '0' && c <='9' ? 1 : 0);
}

int zIsAlpha(int c)
{
	return ( (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ? 1 : 0 );
}

int zIsAlnum(int c)
{
	return zIsAlpha(c) || zIsDigit(c);
}

int zToLower(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return c + 32; 
	}
	return c;
}

int zToUpper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		return c - 32;
	}
	return c;
}