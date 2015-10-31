#include <stdio.h>
#include <stdlib.h>


int iTotal = 0;


void Bombing(int iPosX1, int iPosY1, int iPosX2, int iPosY2)
{
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

	for (iTry = 0; iTry < 100; iTry++) {
		OpenFire();

		iFire = rand() % 100;

	    for (iCounter = 0; iCounter < iFire; iCounter++) {
			iPosX = rand() % (MAX_WIDTH + 1);
			iPosY = rand() % (MAX_HEIGHT + 1);
			iPower = rand() % MAX_POWER;

			Fire(iPosX, iPosY, iPower);
		}

		CeaseFire();
		printf("%d: %d(sec)\n", iTry, iTotal);
	}

	return;
}
