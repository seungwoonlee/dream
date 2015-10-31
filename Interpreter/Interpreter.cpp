#include "dream3.h"
#include <string.h>

/* for GetS() */
const int CR = 13;			// ĳ��������(=����)
const int ENTER = 13;		
const int LF = 10;			// �����ǵ� = �����ٷ�
const int SPACE = 32;
const int BACKSPACE = 8;
const int PLUS = '+';
const int MINUS = '-';
const int MULTIPLE = '*';
const int DIVIDE = '/';
const int PERCENT = '%';
const int AMPERSAND = '&';
const int COLON = ';';

const int MAX_VARIABLE_COUNT = 10;	// �ִ� ���� ���� ���� ����
const int MAX_VARIABLE_NAME_LENGTH = 10;	// �ִ� �����̸� ����

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
//		buf[i] = zToLower(buf[i]);	// �빮�ڰ� �ԷµǸ� �ҹ��ڷ� ��ȯ�ع�����
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
	// src���ڿ��κ��� SPACE�� ���ŵ� ���ڿ��� ���� dst �� ����
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
	int num[MAX_BUF2] = { 0, };	// ���ڹ迭 ����
	char op[MAX_BUF2][2] = { 0, };	// 0������ Op����, 1������ �켱���� ����
	char temp[MAX_BUF2]  = { 0, };
	char A[MAX_BUF2] = { 0, };
	char P[2] = { 0, 0 };
	int flagMinus = 1;
	int i = 0;
	int idxNum = 0;
	int idxOp = 0;
	int eval = 0;

	switch(*str)	// ù��° ����üũ  �񿬼� +, �񿬼� -, ���� �� ����ϰ� �������� ��� ����
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

	while (*str != '\0')	// ù��° ��ȣ�� �����߱� ������ ù��° ���ڴ� ���ڷ� �����Ѵ�.
	{
		if (!(IsOp(*str) || zIsDigit(*str)))	// ���ڳ� ��ȣ�� ���ȴ�.
		{
			Error("!!! The Expresion has Error !!!\n");
			return (char*)0;
		}
		i = 0;
		while (zIsDigit(*str))
		{
			A[i] = *str;	// atoi() �� �ӽù���
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

	OrderOp(op);	// Op �迭�� �켱������ ����Ѵ�.

	eval = EvalExpresion(num, op);

	return zItoa(eval, cp);
}

char* ParseBuf(char* buf)
{
	char* cp = buf;	
	int iPosEq = 0;
	int iPosBs = 0;
	int iPosCR = 0;

	if (*buf == '\0') // ������ ù���ڰ� NULL�̸�, ��ģ��.
	{
		return (char*)0;
	}
	if (*buf == CR)	// ù���ڷ� Enter �� ġ�� ��ģ��.
	{		
		return (char*)0;
	}
	// Backspace ������ƾ - �齺���̽� ��ü�� �ٷ� �ձ��ڸ� �����Ѵ�. �齺���̽��� ���ڿ��� ������������ �ݺ�
	iPosBs = zStrnchr(buf, BACKSPACE);
	while (iPosBs)	// Backspace �� �߰߸��Ҷ����� 
	{
		iPosBs = zStrdelchr(buf, BACKSPACE);	// Backspace ��ü�� �����
		zStrdelpos(buf, iPosBs-1);	// �� �ձ��ڵ� �����.
		iPosBs = zStrnchr(buf, BACKSPACE);
	}
	// ������ Enter ������ƾ
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

int CountChr(char* str, int ch)		// str ���� ch �� ��� �������� ����
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
		return cp;	// Brace�� ��ã���� ����
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

int IdxAlpha(int ch)	// �����ڵ带 ������ �迭�ε����� ����   'a' -> 0 ù��° �迭 �ε�����
{
	return (ch - 'a');
}

int FindLastVariablePos(char varName[MAX_VARIABLE_COUNT][MAX_VARIABLE_NAME_LENGTH])
{ // varName �� �������� ����� ������ ��ġ (���� ������ ������ �� �ִ� �ε����� ����
	int cnt = 0;
	while (varName[cnt][0] != '\0')
	{
		cnt++;
	}
	return cnt;
}

int CheckAlreadyDeclare(char* str, char varName[MAX_VARIABLE_COUNT][MAX_VARIABLE_NAME_LENGTH])
{ // str �� varName �� �̹� ����� �̸��̸� 1 �� ����
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
{	// str �� �̸��� ���� ������ ã�Ƽ� �ش� �ε����� value �� ��ְ� 1�� ����. str �̸��� ������ ������ 0 ����
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
{ // str �� �̸��� ���� ������ ã�Ƽ� �ش� �ε����� varValue ���� �����Ѵ�. str �̸��� ������ ������ -1 �� �����Ѵ�.
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
	{ // rightSide �� �ִ� ��� ������ ������������ ���������� ġȯ
		if (!HasAlpha2(rightSide)) // ���Ŀ� ���ĺ��� ������
		{
			break;
		}
		termValue = GetVariableValue(varName[i], varName, varValue);
		zItoa(termValue, termString);
		zStrreplaceWhole(rightSide, varName[i], termString);  // ������� �Ȱ��� ù��° �ܾ ã�Ƽ� termString(=termValue�� ���ڿ�����) ���� �ٲ۴�.
		i++;
		if (varName[i][0] == '\0')	// �������̺� ���� �ٴٸ���
		{
			if (!zStrcmp(buf4comp, rightSide)) // �����ߴ� ���ڿ��� �ٲ�� ���ٸ� �����ִ� ���ڴ� �������� �ʴ� �����̴�.
			{
				PutS("Undeclared Variable exist\n");
				return;
			}
			zStrcpy(buf4comp, rightSide);		
			i = 0;	// ������ 2���̻� ���ɼ� �����Ƿ� ó������ �ٽ� �� �˻�
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
	// str ��  "int ����" �� �޾Ƽ� �����̸��� �̹� varName �� �̹� ���ǵǾ� �ִ��� �˻��ϰ�, ������ ���� ���������� �Ҵ����ش�.
	char buf[MAX_BUF2] = { 0, };
//	int temp;

	if (zStrncmp(str, "int", 3))	// ù�κ��� "int " �� �ƴϸ� �������̽�
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
//	varArray[FindLastVariablePos(varName)] = -1;	// ���� �ϸ� �Ǵ� ���� ���� �ʿ䰡 ����?

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
		RemoveEnter(buf, ConsoleBuf);	// buf : Enter���ŵ�,  ConsoleBuf : Enter���� �ȵ�

		if (!ParseBuf(buf))	// �Է��� NULL �̸� �����.
		{
			break;
		}
		tString = DetectStringType(buf);	// �Է¹����� Ÿ�Ժм�  1)���깮  2)��ɹ�  3)������ 4)����

		switch (tString)		// �� Ÿ�Ժ� ó��
		{
		case TYPE_STRING_NORMAL:	// �Ϲ� ������ ���
			ProcessNormal(buf);		// ���� ���� ����Ѵ�.
			break;
		case TYPE_STRING_COMMAND:
			ProcessCommand(buf, &statusCmd, varPrint);		// �ָܼ�ɾ� ��� ������� ������ ���� ����� ���� �����ش�.
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