const int MAX = 1000;
const int MAX_WIDTH = MAX;
const int MAX_HEIGHT = MAX;
const int MAX_POWER = 99;

void Bombing(int iPosX1, int iPosY1, int iPosX2, int iPosY2);


void OpenFire(void)
{
	return;
}


void Fire(int iPosX, int iPosY, int iPower)
{
	if (iPower > 0) {
		Bombing(iPosX - iPower, iPosY - iPower, iPosX + iPower, iPosY + iPower);
	}

	return;
}


void CeaseFire(void)
{
	return;
}


#include "testcase.cpp"