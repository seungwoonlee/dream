/*****************************************************/
/*                                                   */
/*  Dec. 2004 - Software Center Programming Contest  */
/*                                                   */
/*  Written by Jangseok Seo                          */
/*  SAMSUNG Electronics Co., Ltd.                    */
/*                                                   */
/*****************************************************/


extern int srand(unsigned int);
extern int rand(void);


static int process(int command, int param1, int param2)
{
	static int school[3][3];
	static int student[10000][3];

	int counter;

	switch (command)
	{
		case 1: return (school[param1][0]);
		case 2: return (school[param1][1]);
		case 3: return (student[param1][0]);
		case 4: return (student[param1][1]);
		case 5: student[param1][2] = param2; return (0);
	}


	if (command == 0)
	{
		for (counter = 0; counter < 3; counter++)
		{
			school[counter][0] = rand() % 1000;
			school[counter][1] = rand() % 1000;
		}

		for (counter = 0; counter < 10000; counter++)
		{
			student[counter][0] = rand() % 1000;
			student[counter][1] = rand() % 1000;
			student[counter][2] = -1;
		}

		return (0);
	}

	return (-1);
}


void get_school_position(int school_index, int* posX, int* posY)
{
	if ((0 <= school_index) && (school_index < 3))
	{
		*posX = process(1, school_index, 0);
		*posY = process(2, school_index, 0);
	}
	else
	{
		*posX = -1;
		*posY = -1;
	}

	return;
}


void get_student_position(int student_index, int* posX, int* posY)
{
	if ((0 <= student_index) && (student_index < 10000))
	{
		*posX = process(3, student_index, 0);
		*posY = process(4, student_index, 0);
	}
	else
	{
		*posX = -1;
		*posY = -1;
	}

	return;
}


void set_student_school(int student_index, int school_index)
{
	if ((0 <= student_index) && (student_index < 10000) && (0 <= school_index) && (school_index < 3))
	{
		process(5, student_index, school_index);
	}

	return;
}


void run_contest(void);

void testcase(void)
{
	return;
}

void main(void)
{
	int counter;

	srand(3);

	for (counter = 0; counter < 10; counter++)
	{
		process(0, 0, 0);
		run_contest();
		testcase();
	}

	return;
}
