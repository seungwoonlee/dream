#include "dream3.h"
#include <string.h>

/* for GetS() */
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
const int COLON = ';';

const int MAX_VARIABLE_COUNT = 10;	// 최대 지원 가능 변수 갯수
const int MAX_VARIABLE_NAME_LENGTH = 10;	// 최대 변수이름 길이

/* Type of String */
const int TYPE_STRING_ERROR = 0;
const int TYPE_STRING_NORMAL = 1;
const int TYPE_STRING_COMMAND = 2;
const int TYPE_STRING_EQUATION = 3;
const int TYPE_STRING_DECLARATION = 4;
const int STATUS_CONTINUE = 1;
const int STATUS_BREAK = 0;


void Error(char *msg)
{	
	PutS(msg);
	//	exit(1);
}

int GetS(char* buf)
{
	int i = 0;

	while (i < MAX_BUF)
	{
		buf[i]  = GetCh();
		if (!( zIsAlnum(buf[i]) || buf[i] == ENTER || buf[i] == BACKSPACE || buf[i] == '+' || buf[i] == '-' || buf[i] == '*' || buf[i] == '/' || buf[i] == '%' || buf[i] == '(' || buf[i] == ')' || buf[i] == '=' || buf[i] == ' ' || buf[i] == ';' || buf[i] == '<' || buf[i] == '>' || buf[i] == '&' || buf[i] == '|' || buf[i] == '?' || buf[i] == '!'))
		{
			continue;
		}		
		PutCh(buf[i]);
//		buf[i] = zToLower(buf[i]);	// 대문자가 입력되면 소문자로 변환해버려라
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

char* RemoveEnter(char* dst, const char* src)
{
	int cnt = 0;
	char* start = (char*)src;
	char temp[MAX_BUF2] = { 0, };
	while (*src != '\0')
	{
		if (*src == CR)
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

char* RemoveSpace(char* dst, const char* src)
{
	// src문자열로부터 SPACE가 제거된 문자열을 만들어서 dst 로 리턴
	int cnt = 0;
	char* start = (char*)src;
	char temp[MAX_BUF2] = { 0, };
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

void OrderOp(char op[MAX_BUF2][2])
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
			Error("Divide by Zero\n");
			return 0;	// todo
		}
		return n1 / n2;
	case '%':
		if (n2 == 0)
		{
			Error("Divide by Zero");
			return 0;	// todo
		}
		return n1 % n2;
	default:
		Error("!!! The Expresion has Error !!!\n");
		return 0;
	}
}

void EvalNumArrary(int num[MAX_BUF2], int term, int idx)
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

void EvalOpArrary(char op[MAX_BUF2][2], int idx)
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

int EvalExpresion(int num[MAX_BUF2], char op[MAX_BUF2][2])
{
	int buf[MAX_BUF2] = { 0, };
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
	int num[MAX_BUF2] = { 0, };	// 숫자배열 저장
	char op[MAX_BUF2][2] = { 0, };	// 0번행은 Op저장, 1번행은 우선순위 저장
	char temp[MAX_BUF2]  = { 0, };
	char A[MAX_BUF2] = { 0, };
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
		if (!zIsDigit(*str))
		{
			Error("!!! The Expresion has Error !!!\n");
		}		
		break;		
	}

	while (*str != '\0')	// 첫번째 기호를 제거했기 때문에 첫번째 글자는 숫자로 시작한다.
	{
		if (!(IsOp(*str) || zIsDigit(*str)))	// 숫자나 기호만 허용된다.
		{
			Error("!!! The Expresion has Error !!!\n");
			return (char*)0;
		}
		i = 0;
		while (zIsDigit(*str))
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
			return (char*)0;
		}
		while (IsOp(*str))
		{
			P[0] = *str++;
			P[1] = *str;
			if (zIsDigit(P[1]))
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
				break;
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

char* ParseBuf(char* buf)
{
	char* cp = buf;	
	int iPosEq = 0;
	int iPosBs = 0;
	int iPosCR = 0;

	if (*buf == '\0') // 버퍼의 첫글자가 NULL이면, 마친다.
	{
		return (char*)0;
	}
	if (*buf == CR)	// 첫글자로 Enter 를 치면 마친다.
	{		
		return (char*)0;
	}
	// Backspace 삭제루틴 - 백스페이스 자체와 바로 앞글자를 삭제한다. 백스페이스가 문자열에 없어질때까지 반복
	iPosBs = zStrnchr(buf, BACKSPACE);
	while (iPosBs)	// Backspace 를 발견못할때까지 
	{
		iPosBs = zStrdelchr(buf, BACKSPACE);	// Backspace 자체를 지우고
		zStrdelpos(buf, iPosBs-1);	// 그 앞글자도 지운다.
		iPosBs = zStrnchr(buf, BACKSPACE);
	}
	// 마지막 Enter 삭제루틴
	while (iPosCR)
	{
		iPosCR = zStrdelchr(buf, CR);
		iPosCR = zStrnchr(buf, CR);
	}
	return buf;
}

int HasChr(const char* str, int ch)
{
	int cnt = 0;

	while (*str != '\0')
	{
		if (*str == ch)
		{
			return 1;
		}
		cnt++;
		str++;
	}
	return 0;
}

int HasAlpha(const char* str)
{
	int idx = 0;
	for (idx = 'A'; idx <= 'Z'; idx++)
	{
		if (HasChr(str, idx))
		{
			return idx;
		}
	}
	for (idx = 'a'; idx <= 'z'; idx++)
	{
		if (HasChr(str, idx))
		{
			return idx;
		}
	}
	return 0;
}

int DetectStringType(char* str)
{
	if (HasChr(str, ';'))
	{
		if (zStrstr(str, "int "))
		{
			return TYPE_STRING_DECLARATION;
		}
		else
		{
			return TYPE_STRING_EQUATION;
		}
	}
	else
	{
		if (zStrstr(str, "print ") || zStrstr(str, "exit") || zStrstr(str, "quit"))
		{
			return TYPE_STRING_COMMAND;
		}
		else
		{
			return TYPE_STRING_NORMAL;
		}
	}
	return TYPE_STRING_ERROR;
}

int CountChr(char* str, int ch)		// str 내에 ch 가 몇번 나오는지 리턴
{
	int cnt = 0;

	while (*str != '\0')
	{
		if (*str == ch)
		{
			cnt++;
		}
		str++;
	}
	return cnt;
}

char* ParseBrace(char* str)
{
	char* cp = str;
	char temp[MAX_BUF2] = { 0, };
	char term[MAX_BUF2] = { 0, };

	int cnt = 0;
	int closeBraceIdx = 0;
	int openBraceIdx = 0;
	int leftBraceCount = 0;
	int rightBraceCount = 0;
	int n = 0;

	leftBraceCount = CountChr(str, '(');
	rightBraceCount = CountChr(str, ')');
	if (leftBraceCount != rightBraceCount)
	{
		Error("Brace mismatch\n");
		return (char*)0;
	}
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

int HasBrase(char* str)
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

void ProcessNormal(char* str)
{
	char buf[MAX_BUF2] = { 0, };
	int statusProcess = STATUS_CONTINUE;

	RemoveSpace(buf, str);
	while (HasBrase(buf) && statusProcess)
	{
		if (!ParseBrace(buf))
		{
			statusProcess = STATUS_BREAK;
			break;
		}
	}
	CalcExpresion(buf);
	PutS(buf);
	PutS("\n");
	return;
}

void ProcessCommand(char* str, int* statusCmd, char var[])
{
	const int CMD_ERROR = -1;
	const int CMD_NOTHING = 0;
	const int CMD_PRINT = 1;
	const int CMD_EXIT  = 2;
	char buf[MAX_BUF2] = { 0, };
	int cnt = 0;
	int i = 0;

	*statusCmd = CMD_NOTHING;

	while (zIsAlpha(*(str+cnt)))
	{
		cnt++;
	}
	if (!zStrncmp(str, "print", cnt))
	{
		*statusCmd = CMD_PRINT;
	}
	if (!zStrncmp(str, "exit", cnt))
	{
		*statusCmd = CMD_EXIT;
	}
	if (!zStrncmp(str, "quit", cnt))
	{
		*statusCmd = CMD_EXIT;
	}

	if (*statusCmd == CMD_PRINT)
	{
		while (str[cnt] != '\0')
		{
			if (zIsAlpha(str[cnt]))
			{
				buf[i] = str[cnt];
				i++;
				cnt++;
				continue;
			}
			cnt++;
		}
		buf[i+1] = '\0';
		zStrcpy(var, buf);
	}
	return;
}

int IdxAlpha(int ch)	// 문자코드를 넣으면 배열인덱스를 리턴   'a' -> 0 첫번째 배열 인덱스로
{
	return (ch - 'a');
}

int FindLastVariablePos(char varName[MAX_VARIABLE_COUNT][MAX_VARIABLE_NAME_LENGTH])
{ // varName 에 변수들이 선언된 마지막 위치 (새로 변수를 선언할 수 있는 인덱스를 리턴
	int cnt = 0;
	while (varName[cnt][0] != '\0')
	{
		cnt++;
	}
	return cnt;
}

int CheckAlreadyDeclare(char* str, char varName[MAX_VARIABLE_COUNT][MAX_VARIABLE_NAME_LENGTH])
{ // str 이 varName 에 이미 선언된 이름이면 1 을 리턴
	int cnt = 0;

	while (varName[cnt][0] != '\0')
	{
		if ( !(zStrcmp(str, varName[cnt])) )
		{
			return 1;
		}
		cnt++;
	}
	return 0;
}

int SetVariableValue(char* str, int value, char varName[MAX_VARIABLE_COUNT][MAX_VARIABLE_NAME_LENGTH], int varValue[MAX_VARIABLE_COUNT])
{	// str 의 이름을 가진 변수를 찾아서 해당 인덱스에 value 를 써넣고 1을 리턴. str 이름의 변수가 없으면 0 리턴
	int i = 0;

	while (varName[i])
	{
		if (zStrcmp(varName[i], str) == 0)
		{
			varValue[i] = value;
			return 1;
		}
		i++;
	}
	return 0;
}

int GetVariableValue(char* str, char varName[MAX_VARIABLE_COUNT][MAX_VARIABLE_NAME_LENGTH], int varValue[MAX_VARIABLE_COUNT])
{ // str 의 이름을 가진 변수를 찾아서 해당 인덱스의 varValue 값을 리턴한다. str 이름의 변수가 없으면 -1 을 리턴한다.
	int i = 0;

	while (varName[i])
	{
		if (zStrcmp(varName[i], str) == 0)
		{
			return varValue[i];
		}
		i++;
	}
	return -1;
}

int HasAlpha2(const char* str)
{
	while (*str)
	{
		if (zIsAlpha(*str))
		{
			return 1;
		}
		str++;
	}
	return 0;
}

void ProcessEquation(char* str, char varName[MAX_VARIABLE_COUNT][MAX_VARIABLE_NAME_LENGTH], int varValue[MAX_VARIABLE_COUNT])
{
	char buf[MAX_BUF2] = { 0, };
	char leftSide[MAX_VARIABLE_NAME_LENGTH] = { 0, };
	char rightSide[MAX_BUF2] = { 0, };
	char buf4comp[MAX_BUF2] = { 0, };
	int termValue;
	char termString[MAX_BUF2] = { 0, };
	int posEq;
	int i = 0;
	int statusProcess = STATUS_CONTINUE;

	RemoveSpace(buf, str);
	posEq = zStrnchr(buf, '=');

	zStrncpy(leftSide, buf, posEq);
	zStrcpy(rightSide, buf+posEq+1);

	while (1)
	{ // rightSide 에 있는 모든 변수가 없어질때까지 변수값으로 치환
		if (!HasAlpha2(rightSide)) // 수식에 알파벳이 없으면
		{
			break;
		}
		termValue = GetVariableValue(varName[i], varName, varValue);
		zItoa(termValue, termString);
		zStrreplaceWhole(rightSide, varName[i], termString);  // 변수명과 똑같은 첫번째 단어를 찾아서 termString(=termValue의 문자열버전) 으로 바꾼다.
		i++;
		if (varName[i][0] == '\0')	// 변수테이블 끝에 다다르면
		{
			if (!zStrcmp(buf4comp, rightSide)) // 보관했던 문자열과 바뀐게 없다면 남아있는 문자는 지원되지 않는 변수이다.
			{
				PutS("Undeclared Variable exist\n");
				return;
			}
			zStrcpy(buf4comp, rightSide);		
			i = 0;	// 변수가 2번이상 사용될수 있으므로 처음부터 다시 또 검색
		}
	}
	
	while (HasBrase(rightSide) && statusProcess)
	{
		if (!ParseBrace(rightSide))
		{
			statusProcess = STATUS_BREAK;
			break;
		}
	}
	CalcExpresion(rightSide);
	SetVariableValue(leftSide, zAtoi(rightSide), varName, varValue);

	return;
}

void ProcessDeclaration(char* str, char varName[MAX_VARIABLE_COUNT][MAX_VARIABLE_NAME_LENGTH])
{
	// todo
	// str 로  "int 변수" 를 받아서 변수이름이 이미 varName 에 이미 정의되어 있는지 검사하고, 없으면 새로 변수영역을 할당해준다.
	char buf[MAX_BUF2] = { 0, };
//	int temp;

	if (zStrncmp(str, "int", 3))	// 첫부분이 "int " 가 아니면 오류케이스
	{
		PutS("Error : Only support 'int' type\n");
		return;
	}
	if (str[3] == '\0' || str[4] == '\0')
	{
		PutS("Error : Variable Name miss\n");
		return;
	}
	zStrcat(buf, str+4);
	if (CheckAlreadyDeclare(buf, varName))
	{
		PutS("Error : Variable Already declared\n");
		return;
	}
	zStrcpy(varName[FindLastVariablePos(varName)], buf);
//	varArray[FindLastVariablePos(varName)] = -1;	// 선언만 하면 되니 값은 넣을 필요가 없다?

	return;
}

void main(void)
{
	char ConsoleBuf[MAX_BUF2] = { 0, };
	char buf[MAX_BUF2] = { 0, };
	char buftemp[MAX_BUF2] = { 0, };
//	char* cp;
//	int posSemicolon;
	int tString = 0;	// Type of String

	int test = 0;
	int test2 = 0;

	int count;
	int statusCmd = 0;
	char varPrint[MAX_VARIABLE_NAME_LENGTH] = { 0, }; 
	char varPrintValue[MAX_BUF2] = { 0, }; 
	int varValue[MAX_VARIABLE_COUNT] = { 0, };
	char varName[MAX_VARIABLE_COUNT][MAX_VARIABLE_NAME_LENGTH] = { 0, };


	PutS("> Mini Interpreter\n");
	PutS("> Available Command :  print [Variable] , quit , exit, <Enter>\n> \n");

	while (1)
	{
		PutS("> ");		// Prompt
		count = GetS(ConsoleBuf);
		RemoveEnter(buf, ConsoleBuf);	// buf : Enter제거됨,  ConsoleBuf : Enter제거 안됨

		if (!ParseBuf(buf))	// 입력이 NULL 이면 멈춘다.
		{
			break;
		}
		tString = DetectStringType(buf);	// 입력문장의 타입분석  1)평계산문  2)명령문  3)방정식 4)선언문

		switch (tString)		// 각 타입별 처리
		{
		case TYPE_STRING_NORMAL:	// 일반 수식인 경우
			ProcessNormal(buf);		// 계산기 모드로 계산한다.
			break;
		case TYPE_STRING_COMMAND:
			ProcessCommand(buf, &statusCmd, varPrint);		// 콘솔명령어 모드 변수명과 변수에 현재 저장된 값을 보여준다.
			PutS(varPrint);
			PutS("=");
			zItoa(GetVariableValue(varPrint, varName, varValue), varPrintValue);
			PutS(varPrintValue);
			PutS("\n");
			break;
		case TYPE_STRING_EQUATION:
			ProcessEquation(buf, varName, varValue);
			break;
		case TYPE_STRING_DECLARATION:
			ProcessDeclaration(buf, varName);
			break;
		default:
			PutS("Unknown Error\n");
			break;
		}
	}
	zStrcpy(buf, "> Quit\n");

	PutS(buf);
	PutCh('\n');
	return;
}