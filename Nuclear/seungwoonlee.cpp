const int MAX = 1000;
const int MAX_WIDTH = MAX;
const int MAX_HEIGHT = MAX;
const int MAX_POWER = 99;

unsigned int fire[MAX_WIDTH];
unsigned int bomb[MAX_WIDTH];

int idx = 0;


void Bombing(int iPosX1, int iPosY1, int iPosX2, int iPosY2);


void OpenFire(void)
{
	int i;

	for (i = 0; i < MAX; i++)
		fire[i] = 0;

	idx = 0;
	return;
}

int X(int idx)
{
	return fire[idx]/100000;
}

int Y(int idx)
{
	return (fire[idx]%100000)/100;
}

int P(int idx)
{
	return bomb[idx]%100;
}

int BX(int idx)
{
	return bomb[idx]/100000;
}

int BY(int idx)
{
	return (bomb[idx]%100000)/100;
}

int BP(int idx)
{
	return bomb[idx]%100;
}


void Fire(int iPosX, int iPosY, int iPower)
{
	int i;
	int j;
	int x;
	int y;
	int p;

	fire[idx] = iPower + iPosY*100 + iPosX*100000;
	idx++;
	
	if (iPower > 0) {
//		Bombing(iPosX - iPower, iPosY - iPower, iPosX + iPower, iPosY + iPower);
	}

	return;
}


void CeaseFire(void)
{
	int i;
	int j;
	int x1;
	int x2;
	int x3;
	int x4;
	int y1;
	int y2;
	int y3;
	int y4;


	for (i=0; i<idx; i++)
	{
		x3 = X(i)-P(i) > 0 ? X(i)-P(i) : 0;
		y3 = Y(i)-P(i) > 0 ? Y(i)-P(i) : 0;
		x4 = X(i)+P(i) > 0 ? X(i)+P(i) : 0;
		y4 = Y(i)+P(i) > 0 ? Y(i)+P(i) : 0;
		for (j=0; j<idx; j++ )
		{
			if (j==i)
			{
				continue;
			}
			x1 = X(j)-P(j) > 0 ? X(j)-P(j) : 0;
			y1 = Y(j)-P(j) > 0 ? Y(j)-P(j) : 0;
			x2 = X(j)+P(j) > 0 ? X(j)+P(j) : 0;
			y2 = Y(j)+P(j) > 0 ? Y(j)+P(j) : 0;
			if (x3 < x1 || x4 < x2 || y3 < y1 || y4 < y2)
			{
				bomb[idx] = fire[idx];
				continue;
			}
			idx--;
		}		
	}
	for (i=0; i<idx; i++)
	{
		Bombing(BX(idx)-BP(idx), BY(idx)-BP(idx), BX(idx)+BP(idx), BY(idx)+BP(idx));
	}
	return;
}


#include "testcase.cpp"
