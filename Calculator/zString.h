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
		while (--cnt)
		{
			*cp++ = '\0';
		}
		return dst;
}

char* zStrcat(char* dst, const char* src)
{
	char *cp = dst;
	while (*++cp != '\0')
	{
		;
	}
	cp--;
	while (*++cp = *++src)
	{
		;
	}
	return dst;
}

char* zStrncat(char* dst, const char* src, unsigned int cnt)
{
	return dst;
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