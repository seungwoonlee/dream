// 4 Level : School
#include "main.c"

void get_school_position(int school_index, int* posX, int* posY);
void get_student_position(int student_index, int* posX, int* posY);
void set_student_school(int student_index, int school_index);

int stud[10000][6];
int sorted[10000][7];
int OverFlowPos = 0;


char* idname(void)
{
	return __FILE__;
}

int Abs(int x)
{
	return ( x < 0 ? -x : x);
}

int Distance(int x, int y, int school_index)
{
	int x1, x2, y1, y2, w, h;
	double d;

	x1 = x;
	y1 = y;
	get_school_position(school_index, &x2, &y2);
	w = Abs(x2 - x1);
	h = Abs(y2 - y1);
	d = w*w + h*h;

	return (int)d;
}

#if 0
int find_shortest(int school_idx)
{
	int min = 9999999;
	int min_idx = 0;
	int i;

	for (i = 0; i<10000; i++)
	{
		if (min > stud[i][school_idx+2])
		{
			if (stud[i][5] == -1)
			{
				min = stud[i][school_idx+2];
				min_idx = i;
			}
		}
	}
	stud[min_idx][5] = school_idx;
	return min_idx;
}
#endif

int Min(int a, int b, int c)
{
	int min = a;

	if (min > b)
	{
		min = b;
	}
	if (min > c)
	{
		min = c;
	}
	return min;
}

int MinExcept(int a, int b, int c, int except)
{
	int min = a;

	switch (except)
	{
	case 0:
		min = b;
		if (min > c)
		{
			min = c;
		}
		break;
	case 1:
		if (min > c)
		{
			min = c;
		}
		break;
	case 2:
		if (min > b)
		{
			min = b;
		}
		break;
	}
	return min;
}

int MinIndex(int a, int b, int c)
{
	int min = a;
	int idx = 0;

	if (min > b)
	{
		min = b;
		idx = 1;
	}
	if (min > c)
	{
		idx = 2;
	}	
	return idx;
}

int MinIndexExcept(int a, int b, int c, int block)
{
	int min = a;
	int idx = 0;

	switch (block)
	{
	case 0:
		min = b;
		idx = 1;
		if (min > c)
		{
			idx = 2;
		}
		break;
	case 1:
		idx = 0;
		if (min > c)
		{
			idx = 2;
		}
		break;
	case 2:
		idx = 0;
		if (min > b)
		{
			idx = 1;
		}
		break;
	}
	return idx;
}

int find_shortest(void)
{
	int i;
	int min = 9999999;
	int min_idx = 0;

	for (i=0; i<10000; i++)
	{
		if (min > Min(stud[i][2], stud[i][3], stud[i][4]))
		{
			if (stud[i][5] == -1)
			{
				min = Min(stud[i][2], stud[i][3], stud[i][4]);
				min_idx = i;
			}
		}		
	}
	stud[min_idx][5] = MinIndex(stud[min_idx][2], stud[min_idx][3], stud[min_idx][4]);
	return min_idx;
}

void SortByDistance1(void)
{
	int i;
	int j;
	int min_idx;

	for (i=0; i<10000; i++)
	{
		min_idx = find_shortest();
		for (j=0; j<6; j++)
		{
			sorted[i][j] = stud[min_idx][j];			
		}
		sorted[i][6] = min_idx;
	}
	return;
}

void Swap(int dst, int src)
{
	int temp[7];
	int i = 0;

	for (i=0; i<7; i++)
	{
		temp[i] = sorted[dst][i];
		sorted[dst][i] = sorted[src][i];
		sorted[src][i] = temp[i];
	}
	return;
}


void SortByDistance2(int block)
{
	int i;
	int j;
	int min = 99999999;
	int min_idx = OverFlowPos;

	for (i=OverFlowPos; i<10000; i++)
	{
		for (j=i; j<10000; j++)
		{
			if (min > MinExcept(sorted[j][2], sorted[j][3], sorted[j][4], block))
			{
				min = MinExcept(sorted[j][2], sorted[j][3], sorted[j][4], block);
				sorted[j][5] = MinIndexExcept(sorted[j][2], sorted[j][3], sorted[j][4], block);
				Swap(j, i);
			}
		}
		min = 99999999;
	}
	return;
}

int CheckOverFlow(void)
{
	int cntSch1 = 0;
	int cntSch2 = 0;
	int cntSch3 = 0;
	int i;

	for (i=0; i<10000; i++)
	{
		switch (sorted[i][5])
		{
		case 0:
			cntSch1++;
			break;
		case 1:
			cntSch2++;
			break;
		case 2:
			cntSch3++;
			break;
		}
		if (cntSch1 >= 3500)
		{
			OverFlowPos = i;
			return 0;
		}
		else if (cntSch2 >= 3500)
		{
			OverFlowPos = i;
			return 1;
		}
		else if (cntSch3 >= 3500)
		{
			OverFlowPos = i;
			return 2;
		}
	}
	return -1;
}

void run_contest(void)
{
	// write the codes for stud allocation
	int i;
	int cnt = 0;
	int blockSchool = -1;
	int blockSchool2 = -1;
	int temp;

	i = 0;
	while (1)
	{
		if ( i > 9999)
		{
			break;
		}
		get_student_position(i, &stud[i][0], &stud[i][1] );
		stud[i][2] = Distance(stud[i][0], stud[i][1], 0);
		stud[i][3] = Distance(stud[i][0], stud[i][1], 1);
		stud[i][4] = Distance(stud[i][0], stud[i][1], 2);
		stud[i][5] = -1;
		i = i + 1;
	}
	SortByDistance1();
	blockSchool = CheckOverFlow();
	for (i=OverFlowPos; i<10000; i++)
	{		
		sorted[i][blockSchool+2] = 99999999;
		sorted[i][5] = (blockSchool+1)%3;
	}

	SortByDistance2(blockSchool);
	blockSchool2 = CheckOverFlow();
	if (blockSchool2 != -1)
	{
		switch (blockSchool + blockSchool2)
		{
		case 1:
			temp = 2;
			break;
		case 2:
			temp = 1;
			break;
		case 3:
			temp = 0;
			break;
		}
		for (i=OverFlowPos; i<10000; i++)
		{
			sorted[i][5] = temp;
		}
	}

	i = 0;
	while(1)
	{
		if (i >= 10000 )
		{
			break;
		}
		set_student_school(sorted[i][6], sorted[i][5]);
		i = i + 1;
	}
	
	return;
}
