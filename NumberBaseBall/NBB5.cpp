// 5 Level : Removing Global Variables
#include <stdlib.h>
#include <time.h>
#include "dream.h"

int a[3];	// objective score
int n[3];	// using numbers
int expect[10];
int select[10];
int history[999][3];
int strike;
int ball;
int inning;
int except;
int cumInning;
int cumGame;

int i;
int cum;
int temp;
int exceed;
int max;
int premax;

void History(void)
{
	history[inning][0] = n[0];
	history[inning][1] = n[1];
	history[inning][2] = n[2];
	return;
}

void Init(void)
{
	// a[3] 맞춰야할 숫자 설정
	a[0] = rand() % 10;
	while (true)
	{
		a[1] = rand()%10;
		if (a[0] != a[1])
		{
			break;
		}		
	}
	while (true)
	{
		a[2] = rand() % 10;
		if (!(a[0] == a[1] || a[1] == a[2] || a[2] == a[0]))
		{
			break;
		}
	}
	// n[3] 생성
	n[0] = rand()%10;
	while (true)
	{
		n[1] = rand()%10;
		if (n[0] != n[1])
		{
			break;
		}
	}
	while (true)
	{
		n[2] = rand() % 10;
		if (!(n[0] == n[1] || n[1] == n[2] || n[2] == n[0]))
		{
			break;
		}
	}
	i = 0;
	// Table Reset
	while (true)
	{
		if (i >= 10 )
		{
			break;
		}
		expect[i] = 1;
		select[i] = 1;
		i = i + 1;
	}
// Variables Reset
	i = 0;
	inning = 0;
	History();
	inning = inning + 1;	// 최초 n[3] 생성시를 1회로 침
	return;
}

void Defense(void)
{
	strike = 0;
	ball   = 0;

	if (a[0] == n[0])
	{
		strike = strike + 1;
	}
	if (a[1] == n[0])
	{
		ball = ball + 1;
	}
	if (a[2] == n[0])
	{
		ball = ball + 1; 
	}
	if (a[0] == n[1])
	{
		ball = ball + 1;
	}
	if (a[1] == n[1])
	{
		strike = strike + 1;
	}
	if (a[2] == n[1])
	{
		ball = ball + 1;
	}
	if (a[0] == n[2])
	{
		ball = ball + 1;
	}
	if (a[1] == n[2])
	{
		ball = ball + 1;
	}
	if (a[2] == n[2])
	{
		strike = strike + 1;
	}
	return;
}

void FindExpect(void)
{
	while (true)
	{
		n[0] = rand() % 10;
		while (true)
		{
			if (!(expect[n[0]]) == 0)
			{
				break;
			}
			n[0] = rand() % 10;
		}
		n[1] = rand() % 10;
		while (true)
		{
			if (!(expect[n[1]] == 0 || n[0] == n[1]))
			{
				break;
			}
			n[1] = rand() % 10;
		}
		n[2] = rand() % 10;
		while (true)
		{
			n[2] = rand() % 10;
			if (n[0] != n[2] && n[1] != n[2] && expect[n[2]] != 0)
			{
				break;
			}
		}

		i = 0;
		while (true)
		{
			if (!(i < inning))
			{
				break;
			}
			if (history[i][0] == n[0] && history[i][1] == n[1] && history[i][2] == n[2])
			{
				exceed = 1;
				return;
			}
			i++;
		}
		premax = max;
		max = expect[n[0]] + expect[n[1]] + expect[n[2]];

		if (!(premax > max))
		{
			break;
		}
	}
	return;
}

void ResetExpect(void)
{
	i = 0;
	while (true)
	{
		if (!(i < 10))
		{
			break;
		}
		if (expect[i] != 0)
		{
			expect[i] = 1;
		}
		i++;
	}
	FindExpect();
	return;
}

void CalcExcept(void)
{
	i = 0;
	except = 0;

	while (true)	// Except 가 몇개 인지 계산 - Except 는 확실하게 기대값이 아닌것의 갯수
	{
		if (!(i < 10))
		{
			break;
		}
		if (expect[i] == 0)
		{
			except++;
			select[i] = 0;
		}
		i++;
	}
	if (except <= 7)
	{
		FindExpect();
	}
	else if (except <= 5 || exceed != 1 || max < 20)
	{
		ResetExpect();
	}
	return;
}

void DetA(void)
{
	i = 0;
	while (true)
	{
		if (!(i < 10))
		{
			break;
		}
		expect[i] = 0;
		i = i + 1;
	}
	expect[n[0]] = 1;
	expect[n[1]] = 1;
	expect[n[2]] = 1;
	if (cum < 2)
	{
		temp = n[0];
		n[0] = n[1];
		n[1] = n[2];
		n[2] = temp;	
		cum++;
	}
	else
	{
		temp = n[1];
		n[1] = n[2];
		n[2] = temp;
		cum = 0;
	}
	return;
}

void DetB(void)
{
	expect[n[0]] = 0;
	expect[n[1]] = 0;
	expect[n[2]] = 0;
	CalcExcept();
	return;
}

void Offense(void)
{
	while (true)
	{
		if (strike == 3)
		{
			break;
		}
		else if (strike + ball == 3)
		{
			DetA();
		}
		else if (strike + ball == 0)
		{
			DetB();
		}
		else if (strike != 0)
		{
			i = 0;
			while (true)
			{
				if (!(i < 3))
				{
					break;
				}
				if (expect[n[i]] != 0)
				{
					expect[n[i]] += strike;
				}
				i++;
			}
		}
		else if (ball != 0)
		{
			i = 0;
			while (true)
			{
				if (!(i < 3))
				{
					break;
				}
				if (expect[n[i]] != 0)
				{
					expect[n[i]] += ball;
				}
				i++;
			}
		}
		CalcExcept();
		History();
		inning = inning + 1;		
		Defense();
	}
}

void ShowResult(void)
{
	PutStr("Result is ");
	PutInt(n[0]), PutInt(n[1]), PutInt(n[2]);
	PutStr(" at ");
	PutInt(inning);
	PutStr(" inning\n");
	return;
}

void ShowTotalResult(void)
{
	PutStr("Average is ");
	PutInt(cumInning/cumGame);
	PutStr("\n");
	return;
}

void main(void)
{
	srand((unsigned)time(NULL));
	while (true)
	{
		if (cumGame >= 100)
		{
			break;
		}
		Init();
		Defense();
		Offense();
		ShowResult();
		cumInning = cumInning + inning;
		cumGame = cumGame + 1;
	}
	ShowTotalResult();
	return;
}