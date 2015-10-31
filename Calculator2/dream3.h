#include <conio.h>

const int MAX_BUF = 1000;
const int MAX_BUF2 = 100;	// 1000 으로 개발하면 너무 커서 디버그가 불편하므로 임시로 쓴다.
const int CR = 13;			// 캐리지리턴(=엔터)
const int ENTER = 13;		
const int LF = 10;			// 라인피드 = 다음줄로
const int SPACE = 32;
const int BACKSPACE = 8;
const int PLUS = '+';
const int MINUS = '-';
const int MULTIPLE = '*';
const int DIVIDE = '/';
const int PERCENT = '%';
const int AMPERSAND = '&';

/* Prototypes */

int GetCh(void);

void PutCh(char ch);

int GetCon(void);		// 콘솔을 통해 한글자만 입력 받는다. 

void PutInt(int num);	// 정수출력 (음수도 됨)

void PutS(const char* str);

//int GetS(char* buf);	// 문자열 입력받는다. 버퍼크기는 MAX_BUF에 따르며, 리턴값은 입력된 문자열의 길이이다.

int zStrlen(const char *str);

char* zStrcpy(char* dst, char* src);

char* zStrncpy(char* dst, const char* src, unsigned int cnt);

char* zStrncpy2(char* dst, const char* src, unsigned int cnt);	// n 이 src문자열길이보다 작을때 뒤쪽에 NULL을 채우지 않은것을 채운것으로 바꾼 버전

char* zStrcat(char* dst, const char* src);

char* zStrncat(char* dst, const char* src, unsigned int cnt);

int zStrcmp(const char *str1, const char *str2);

int zStrncmp(const char *str1, const char *str2, unsigned int cnt);

char* zStrchr(char* str, int ch);

unsigned int zStrnchr(char* str, int ch);	// ch 를 처음 찾은곳의 인덱스를 리턴

char* zStrstr(char* str, char* key );

int zAtoi(const char *str);

char* zItoa(int num, char* str);

int zIsAlpha(int c);

int zIsDigit(int c);

int zIsAlnum(int c);	

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
		*cp = '\0';	// cnt == 0 으로 리턴될때 끝에 NULL 추가하는 zStrncpy() 개조버전
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
	while (1)
	{
		if (*str1 == '\0')
		{
			return 0;
		}
		if (*++str1 != *++str2)
		{
			break;
		}
	}
	return ( (*str1 - *str2) < 0 ? -1 : 1 );
}

int zStrncmp(const char *str1, const char *str2, unsigned int cnt)
{
	while (1)
	{
		if (*str1 == '\0' || cnt == 0)
		{
			return 0;
		}		
		if ((*++str1 != *++str2) || (--cnt == 0))
		{
			break;
		}
	}
	//return ( (*str1 - *str2) < 0 ? -1 : 1 );
	return *str1 - *str2;	// 여기가 왜 strcmp() 와 strncmp 가 다른지 모르겠음. 항상 *str1 - *str2 는 아님 규칙을 모르겠음, 특정경우 +/- 1 차이가 남 
}

char* zStrchr(char* str, int ch)	// ch 글자를 처음찾은 곳을 리턴
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

unsigned int zStrnchr(char* str, int ch)	// ch 글자를 처음찾은 곳까지의 index 를 리턴
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
	return -1;
}

char* zStrstr(char* str, char* key )
{ 
	int lengh = zStrlen(key);

	while (1)
	{
		str = zStrchr(str, key[0]); 
		if (str == '\0') 
		{
			return '\0';
		}
		if (!zStrncmp(str, key, lengh))
		{
			return (char*) str; 
		}
		str++; 
	} 
}

int zIsDigit(char c)
{
	return (c >= 48 && c <=57 ? 1 : 0);
}

int zAtoi(const char *str)
{
	int ret = 0;
	int sign = 0;

	while (1)	// 숫자로 시작하는것이 아닐수 있는 앞부분
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
	while (1)	// 숫자부분 시작
	{
		if (*str == '\0' || ret > 0x80000000 )
		{
			break;
		}
		if (!zIsDigit(*str))	// 중간에 숫자가 아닌게 나오면 바로 0 리턴
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