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

unsigned int zStrnchr(char* str, int ch)	// ch ���ڸ� ó��ã�� �������� index �� ����
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