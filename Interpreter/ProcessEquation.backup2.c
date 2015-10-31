void ProcessEquation(char* str, char varName[MAX_VARIABLE_COUNT][MAX_VARIABLE_NAME_LENGTH], int varValue[MAX_VARIABLE_COUNT])
{
	char buf[MAX_BUF2] = { 0, };
	char leftSide[MAX_VARIABLE_NAME_LENGTH] = { 0, };
	char rightSide[MAX_BUF2] = { 0, };
	char term[MAX_BUF2] = { 0, };
	int termValue;
	char termString[MAX_BUF2] = { 0, };
	int posEq;
	int base = 0;
	int offset = 0;
	int i = 0;
	int statusProcess = STATUS_CONTINUE;

	RemoveSpace(buf, str);
	posEq = zStrnchr(buf, '=');

	zStrncpy(leftSide, buf, posEq);
	zStrcpy(rightSide, buf+posEq+1);

	while (!(rightSide[base+offset] == 0 && offset == 0))
	{
		if (zIsDelimiter(rightSide[base+offset]) == 0)
		{
			offset++;
			continue;
		}
		zStrncpy(term, rightSide+base, offset);
		if (CheckAlreadyDeclare(term, varName))
		{
			termValue = GetVariableValue(term, varName, varValue);
		}
		else
		{
			while (term[i] != 0)
			{
				if (!zIsDigit(term[i]))
				{
					PutS("Not Declared Variable\n");
					return;
				}
				i++;
			}
			termValue = zAtoi(term);
		}		
		zItoa(termValue, termString);
		zStrreplace(rightSide, term, termString);
		base = base + offset + 1;	// 기호부분만큼을 띄우고
		offset = 0;
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

	return;
}
