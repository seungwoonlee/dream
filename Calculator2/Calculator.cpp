#include "dream2.h"
#include "z.h"

#include <stdlib.h>	// because  exit() function
#include <string.h>

const int BUF_MAX = 1000;
const int BUF_TEST = 100;
const char ENTER = 13;
const char CR = 13;
const char LF = 10;

char* ParseBrace(char* str);

void Error(char *msg)
{	
	PutS(msg);
	exit(1);
}

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

int FindRepeatedPlusMinus(char* str)
{
	int idx = 0;
	int cont = 0;
	int max = 0;

	while (*str != '\0')
	{
		while (*str != '+' && *str != '-')
		{
			if (*str == '\0')
			{
				return max;
			}
			str++;
		}
		if (*(str+1) == '+' || *(str+1) == '-')
		{
			cont = 1;
			idx++;
			str++;
			continue;
		}
		cont = 0;
		max < idx ? max = idx : max = max ;
		idx = 0;
		str++;
	}
	return (max > idx ? max : idx);
}

char* InsertChar(char* dst, int ch, int pos)
{
	char* cp = dst;
	char temp[BUF_MAX] = { 0, };
	char C[2] = { 0, 0 };

	zStrncpy(temp, cp, pos);
	C[0] = ch;
	zStrcat(temp, C);
	zStrncat(temp, dst+pos, zStrlen(dst)-pos);
	zStrcpy(cp, temp);

	return cp;
}

char* InsertBrace4PlusMinus(char* str)
{
	char* cp = str;
	int start = FindRepeatedPlusMinus(str);
	char temp[BUF_MAX] = { 0, };
	int idx = 0;
	int cont = 0;

	zStrcpy(temp, str);

	while ( temp[idx] != '+' && temp[idx] != '-' )
	{
		cont++;
		idx++;
	}
	if (cont < start)
	{
		// ) 치는 곳 뒤에 +- 연속되는 곳이 있다. 너무 많은 것을 ( ) 싸는 것은 한계가 있는 것 같고 우선 대충 너무 많이 +- 중복되는 것은 미리 걸러주고 시작해야할듯;
	}
	cont = 0;
	start = start + idx;
	InsertChar(temp, '(', start);
	// 다음숫자가 나오는곳 다음칸에 ) 를 넣기
	while ( !zIsDigit(temp[idx]) )
	{		
		idx++;
	}
	while ( zIsDigit(temp[idx]) )
	{
		idx++;
	}
	start = idx;
	InsertChar(temp, ')', start);
	zStrcpy(cp, temp);
	return cp;
}

char* RemoveSpace(char* dst, const char* src)
{
	// src문자열로부터 SPACE가 제거된 문자열을 만들어서 dst 로 리턴
	int cnt = 0;
	char* start = (char*)src;
	char temp[BUF_MAX] = { 0, };
	while (*src != '\0')
	{
		if (*src == ' ')
		{
			zStrncat(temp, start, cnt);
			start += cnt + 1;
			cnt = 0;
			src++;
			continue;
		}
		cnt++;
		src++;
	}
	zStrncat(temp, start, cnt);
	zStrcpy(dst, temp);
	return dst;
}

int IsFirstOp(int ch)
{
	switch (ch)
	{
	case '+':
		return 0;
	case '-':
		return 0;
	case '*':
		return 1;
	case '/':
		return 1;
	case '%':
		return 1;
	default:
		return 0;
	}
}

int IsOp(int ch)
{
	switch (ch)
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
	default:
		return 0;
	}
}

int IsDigit(int num)
{
	int ret = 0;

	if (num >= '0' && num <= '9')
	{
		return 1;
	}
	return 0;
}

void OrderOp(char op[BUF_MAX][2])
{
	int idx = 0;
	int cnt = 1;

	while (op[idx][0])
	{
		if (IsFirstOp(op[idx][0]))
		{
			op[idx][1] = cnt;		
			cnt++;
		}
		idx++;
	}
	idx = 0;
	while (op[idx][0])
	{		
		if (op[idx][1] == 0)
		{
			op[idx][1] = cnt;		
			cnt++;
		}
		idx++;
	}
	return;
}

int EvalTerm(int n1, int n2, char op)
{
	switch(op)
	{
	case '+':
		return n1 + n2;
	case '-':
		return n1 - n2;
	case '*':
		return n1 * n2;
	case '/':
		if (n2 == 0)
		{
			Error("Divide by Zero Error\n");
		}
		return n1 / n2;
	case '%':
		if (n2 == 0)
		{
			Error("Divide by Zero Error\n");
		}
		return n1 % n2;
	default:
		Error("!!! The Expresion has Error !!!\n");
		return 0;
	}
}

void EvalNumArrary(int num[BUF_MAX], int term, int idx)
{
	int i = idx;

	num[i] = term;
	i++;
	while (num[i+1] != 0)
	{	
		num[i] = num[i+1];
		i++;
	}
	num[i] = 0;
	return;
}

void EvalOpArrary(char op[BUF_MAX][2], int idx)
{
	int i = idx;
	while (op[idx+1][0] != 0)
	{
		op[idx][0] = op[idx+1][0];
		op[idx][1] = op[idx+1][1];
		idx++;
	}
	op[idx][0] = 0;
	op[idx][1] = 0;
	return;
}

int EvalExpresion(int num[BUF_MAX], char op[BUF_MAX][2])
{
	int buf[BUF_MAX] = { 0, };
	int idx = 0;
	int order = 1;
	int term = 0;

	while (op[idx][0])
	{
		if (op[idx][1] == order)
		{
			term = EvalTerm(num[idx], num[idx+1], op[idx][0]);
			EvalNumArrary(num, term, idx);
			EvalOpArrary(op, idx);
			order++;
			idx = 0;
			continue;
		}
		idx++;
	}
	return num[0];
}

char* CalcExpresion(char* str)
{
	char* cp = str;
	int num[BUF_MAX] = { 0, };	// 숫자배열 저장
	char op[BUF_MAX][2] = { 0, };	// 0번행은 Op저장, 1번행은 우선순위 저장
	char temp[BUF_MAX]  = { 0, };
	char A[BUF_MAX] = { 0, };
	char P[2] = { 0, 0 };
	int flagMinus = 1;
	int i = 0;
	int idxNum = 0;
	int idxOp = 0;
	int eval = 0;
	
	switch(*str)	// 첫번째 글자체크  비연속 +, 비연속 -, 숫자 만 허용하고 나머지는 모두 에러
	{
	case '+':
		zStrcpy(temp, str);
		zStrcpy(str, temp+1);
		break;
	case '-':
		if (*(str+1) == '-')
		{
			flagMinus = 1;
			zStrcpy(temp, str);
			zStrcpy(str, temp+2);
			break;
		}
		flagMinus = -1;
		zStrcpy(temp, str);
		zStrcpy(str, temp+1);
		break;
	default:
		if (!IsDigit(*str))
		{
			Error("!!! The Expresion has Error !!!\n");
		}		
		break;		
	}
	
	while (*str != '\0')	// 첫번째 기호를 제거했기 때문에 첫번째 글자는 숫자로 시작한다.
	{
		if (!(IsOp(*str) || IsDigit(*str)))	// 숫자나 기호만 허용된다.
		{
			Error("!!! The Expresion has Error !!!\n");
		}
		i = 0;
		while (IsDigit(*str))
		{
			A[i] = *str;	// atoi() 용 임시버퍼
			i++;
			str++;
		}
		num[idxNum] = zAtoi(A) * flagMinus;
		flagMinus = 1;
		idxNum++;
		while (i-- != 0)
		{
			A[i] = '\0';
		}
		if (!IsOp(*str))
		{
			if (op[0][0] == 0)
			{
				break;
			}
			if (*str == '\0')
			{
				break;
			}
			Error("!!! The Expresion has Error !!!\n");
		}
		while (IsOp(*str))
		{
			P[0] = *str++;
			P[1] = *str;
			if (IsDigit(P[1]))
			{
				break;
			}
			switch (P[1])
			{
				case '+':
					str++;
					break;
				case '-':
					flagMinus = -1;
					str++;
					break;
				case '*':
				case '/':
				case '%':
					Error("!!! The Expresion has Error !!!\n");
				default:
					Error("!!! The Expresion has Error !!!\n");
			}
			break;
		}
		op[idxOp][0] = P[0];
		idxOp++;
		P[0] = 0;
		P[1] = 0;
	}

	OrderOp(op);	// Op 배열에 우선순위를 기록한다.

	eval = EvalExpresion(num, op);

	return zItoa(eval, cp);
}

char* ParseBrace(char* str)
{
	char* cp = str;
	char temp[BUF_MAX] = { 0, };
	char term[BUF_MAX] = { 0, };

	int cnt = 0;
	int closeBraceIdx = 0;
	int openBraceIdx = 0;

	while (*str != '\0')
	{
		if (*str == ')')
		{
			closeBraceIdx = cnt;
			break;
		}
		str++;
		cnt++;
	}
	if (*str == '\0')
	{
		return cp;	// Brace를 못찾으면 리턴
	}

	while (1)
	{
		if (*str == '(')
		{
			openBraceIdx = cnt;
			break;
		}
		str--;
		cnt--;
	}
	zStrncpy(temp, cp, openBraceIdx);
	zStrncpy(term, str+1, closeBraceIdx-openBraceIdx-1);
	CalcExpresion(term);
	zStrcat(temp, term);
	zStrcat(temp, cp+closeBraceIdx+1);
	zStrcpy(cp, temp);	
	return cp;
}

int HasBrase(const char* str)
{
	while (*str != '\0')
	{
		if (*str == '(' || *str == ')')
		{
			return 1;
		}
		str++;
	}
	return 0;
}

char* ReduceTogglePlusMinus(char* str)
{
	char* cp = str;
	char temp[BUF_MAX] = { 0, };
	int flagStartToggle = 0;
	char ch[2] = { 0, 0 };
	int idx = 0;

	while (*str++ != '\0')
	{
		idx++;
		if (*str == '+' && *(str+1) == '-' && *(str+2) == '+')
		{
			zStrncpy(temp, cp, idx);
			ch[0] = '-';
			zStrcat(temp, ch);
			zStrcat(temp, str+3);
			str+=2;
		}
		else if (*str == '-' && *(str+1) == '+' && *(str+2) == '-')
		{
			zStrncpy(temp, cp, idx);
			ch[0] = '+';
			zStrcat(temp, ch);
			zStrcat(temp, str+3);
			str+=2;
		}
	}
	if (ch[0] != 0)
	{
		zStrcpy(cp, temp);
	}
	return cp;
}

char* ReduceTogglePlusMinus2(char* str)
{
	char* cp = str;
	char temp[BUF_MAX] = { 0, };
	int flagStartToggle = 0;
	int cumMinus = 0;
	int idx = 0;
	char ch[2] = { 0, 0 };
	
	while (*str++ != '\0')
	{
		idx++;
		if (*str == '+')
		{
			str++;
			while (*(str) == '-' && *(str+1) == '+')
			{
				zStrncpy(temp, cp, idx);
				flagStartToggle = 1;
				cumMinus++;
				str+=2;
			}
			break;
		}
		else if (*str == '-')
		{
			cumMinus++;
			str++;
			while (*(str) == '+' && *(str+1) == '-')
			{
				zStrncpy(temp, cp, idx);
				flagStartToggle = 1;
				cumMinus++;
				str+=2;
			}
			break;
		}		
	}
	if (flagStartToggle)
	{
		if (cumMinus % 2)
		{
			ch[0] = '-';
		}
		else
		{
			ch[0] = '+';
		}		
		zStrcat(temp, ch);
		zStrcat(temp, str);		
		zStrcpy(cp, temp);
	}
	return cp;
}



void main(void)
{
	int i;
	const int TC_MAX = 26;
	char buf[BUF_MAX] = { 0, };
	char exp[TC_MAX][BUF_MAX] =
	{
		"1+2+3",
		"(1+2)+3",
		"1+(2+3)",
		"-(1+2)+3",
		"-(-1+2)+3",
		"(-2)*3",
		"-3*(-3)",
		"((1+2)*3)-2",
		"(((1+2)*(2-3))/3)",
		"-(-(2+3))",
		"2+(-4*2-(2+3))",
		"-((1+(-2)+(3+(4+(-5)+6+(-7))+8)+9)+(-10))",
		"(((1+2)*(2-3))/3) % 7 + (-34*7-98/2*(-2))",
		"-( 28 * (( -23 - 7 % 9 )-( 22 / 3 - 9 * 4 -( -8 + 6 * 3 )))) ",
		"(-(28*((-44 -7%5) - (22/3645-977*4 -(8+654*3)))) -(28*((-23 -7%9) - (22/3-9*4 -(-8+6*3))))) * 6-45",
		"-123456789 + 123456789 + 4 * 596 % 10 -87 /14",		
		"1*2*3*4*5*6*7*8*9",
		"-(1*((-2)*(3*(-4)*5*(-6)*7)))*(-8*9)",
		"1234567890/24444/21/2",
		"1234567890/((-24444)/21)/(-2)",
		"1*+3",
		"11231*-324",
		"1+(+1)",
		"1-(-1)",
		"-5*-4-5*4+5*4+5*-4",
//		"1+-+1",
//		"1-+-1",
//		"1+-+-1",
//		"1-+-+1",
//		"1*+-+-1",
//		"1*+-+1",
//		"-+-+1-+1",		// +/- 의 배치에 따라 안되는 경우 잔존함
//		"+-+1-+1",
//		"-341*-(+-+-+-+1)",
//		"-341+(-(+-+-+-+12))",
//		"-+-+-+(-+-34)*-+-(32/-+-+-5)"
//		"(-(28*((-44*1*1 -7%5 -341*-(+1)) - (22/3645-977*4 -(8+1-1+654*3)))) -(28*((-23 -7%9) - (22/3-9*4 -(-8+6*3))))) * 6-45 +1-+1"
		"(-(28*((-44*1*-1 -7%5 -341*-(+1)) - (22/3645-977*4 -(8+1+1+654*3)))) -(28*((-23 -7%9) - (22/3-9*4 -(-8+6*3))))) * 6-45 -1-+1"
	};

	// Expresion Test
	i = -((1+(-2)+(3+(4+(-5)+6+(-7))+8)+9)+(-10));
	i = -(1*((-2)*(3*(-4)*5*(-6)*7)))*(-8*9);
	i = 1*+-+-1;
	i = 1+-+1;
	i = 1+-+-+1;
	i = 1-+-+-+1;
	i = 1-+-+-+-+1;
	i = 1-+-+-+-+-1;

	for (i = 0; i < TC_MAX; i++)
	{
		RemoveSpace(buf, exp[i]);
		while (HasBrase(buf))
		{
			ParseBrace(buf);
		}
		CalcExpresion(buf);		
		PutS(buf);
		PutS(" \t");
		PutS(exp[i]);
		PutS("\n");
	}
	return;
}