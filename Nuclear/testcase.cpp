#include <stdio.h>
#include <stdlib.h>

int field[1000][1000];


int iTotal = 0;



void Bombing(int iPosX1, int iPosY1, int iPosX2, int iPosY2);


void Bombing(int iPosX1, int iPosY1, int iPosX2, int iPosY2)
{
	int i;
	int j;

	if (iPosX1 < 0)
		iPosX1 = 0;
	if (iPosX2 > 1000)
		iPosX2 = 1000;
	if (iPosY1 < 0)
		iPosY1 = 0;
	if (iPosY2 > 1000)
		iPosY2 = 1000;

	for (i=iPosX1; i<iPosX2; i++)
	{
		for (j=iPosY1; j<iPosY2; j++)
		{
			if (field[i][j] == -10)
			{
				 field[i][j] = 0;
			}
			else if (field[i][j] == 0)
			{
				field[i][j] = -20;
			}
			else
			{
				field[i][j] = field[i][j];
			}
		}
	}
	iTotal += 5;
}


void main(void)
{
	int iTry;
    int iCounter;
    int iFire;
	int iPosX;
	int iPosY;
	int iPower;
	int i;
	int j;
	int cumLost = 0;
	int cnt = 0;

	for (iTry = 0; iTry < 100; iTry++) {
		OpenFire();

		iFire = rand() % 100;

	    for (iCounter = 0; iCounter < iFire; iCounter++)
		{
			iPosX = rand() % (MAX_WIDTH + 1);
			iPosY = rand() % (MAX_HEIGHT + 1);
			iPower = rand() % MAX_POWER;
			for (i=iPosX-iPower; i<iPosX+iPower; i++)
			{
				for (j=iPosY-iPower; j<iPosY+iPower; j++)
				{
					if (i<0 || j<0)
					{
						continue;
					}
					if (i>=MAX_WIDTH || j>=MAX_HEIGHT)
					{
						continue;
					}						
					field[i][j] = -10;
				}
			}
			Fire(iPosX, iPosY, iPower);
		}
		CeaseFire();

		for (i=0; i<1000; i++)
		{
			for(j=0; j<1000; j++)
			{
				cumLost += field[i][j];
			}
		}

		printf("%d: %d(sec) %d\n", iTry, iTotal, cumLost);
		cumLost = 0;
		for (i=0; i<1000; i++)
		{
			for(j=0; j<1000; j++)
			{
				field[i][j] = 0;
			}
		}
	}

	return;
}
