void ProcessEquation(char* str, char varName[MAX_VARIABLE_COUNT][MAX_VARIABLE_NAME_LENGTH], int varValue[MAX_VARIABLE_COUNT])
{
	int leftVarIdx = 0;
	char leftVarValue[16] = { 0, };
	char rightTerm[MAX_BUF2] = { 0, };
	int rightValue = 0;
	char buf[MAX_BUF2] = { 0, };
	char P[2] = { 0, 0 };
	char z[MAX_BUF2] = { 0, };
	int idx = 0;
	int statusProcess = STATUS_CONTINUE;

	RemoveSpace(buf, str);

	if (!zIsAlpha(buf[0]))
	{
		zStrcpy(str, "Variable Error\n");
		return;
	}
	if (buf[1] != '=')
	{
		zStrcpy(str, "Equation Error\n");
		return;
	}

	leftVarIdx = buf[0];
	zStrcpy(rightTerm, buf+2);

	while (rightTerm[idx] != 0)
	{
		if (zIsAlpha(rightTerm[idx]))
		{
			P[0] = rightTerm[idx];
			zItoa(varValue[IdxAlpha(P[0])], z);
			zStrreplace(rightTerm, P, z);
			continue;
		}
		idx++;
	}

	while (HasBrase(rightTerm) && statusProcess)
	{
		if (!ParseBrace(rightTerm))
		{
			statusProcess = STATUS_BREAK;
			break;
		}
	}
	CalcExpresion(rightTerm);

	zStrcpy(leftVarValue, rightTerm);
	varValue[IdxAlpha(leftVarIdx)] = zAtoi(rightTerm);

	return;
}