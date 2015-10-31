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