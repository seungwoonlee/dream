// 1 Level : Subroutine
#include <stdlib.h>
#include <time.h>
#include "dream.h"

int expect[10];
int select[10];
int history[999][3];
int n[3];
int strike;
int ball;
int inning = 0;
int i;
int temp;
static int cum;
int except;
int max;
int premax;
int exceed;
int A1;
int A2;
int A3;
int B1;
int B2;
int B3;
int STRIKE;
int BALL;
int OUT;
int LOOP = 1;
int INN = 0;

void Init(void)
{	
	A1 = rand()%10;
	do { A2 = rand()%10; } while (A1 == A2);
	do { A3 = rand()%10; } while (A1 == A2 || A2 == A3 || A3 == A1);

	strike = 0;
	ball   = 0;
	inning = 0;
	temp   = 0;
	cum    = 0;
	except = 0;
	max    = 0;
	premax = 0;
	exceed = 0;

	n[0] = rand()%3;
	do { n[1] = rand()%3+3; } while (n[0] == n[1]);
	do { n[2] = rand()%3+7; } while (n[0] == n[1] || n[1] == n[2] || n[2] == n[0]);
	
	i = 0;
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
	return;
}

void main(void)
{
	srand((unsigned)time(NULL));
Phase0:
	Init();
	goto Phase1;

////////////////////////////////////////////////////////////

DEFENSE:
PHASE0:	// Initialize
	B1 = n[0];
	B2 = n[1];
	B3 = n[2];

	STRIKE = 0;
	BALL   = 0;
	OUT    = 0;

	//PHASE1:	// Compare First
	//	PutStr("\nFirst  : ");
	//	B1 = GetInt();
	if (A1 == B1) goto L1_Strike;
	if (A2 == B1) goto L1_Ball;
	if (A3 == B1) goto L1_Ball;
	goto L1_Out;

L1_Strike:
	STRIKE++; goto PHASE2;

L1_Ball:
	BALL++; goto PHASE2;

L1_Out:
	OUT++; goto PHASE2;

PHASE2:	// Compare Second
	//	PutStr("\nSecond : ");
	//	B2 = GetInt();
	if (B1 == B2) goto L2_Error;
	if (A1 == B2) goto L2_Ball;
	if (A2 == B2) goto L2_Strike;
	if (A3 == B2) goto L2_Ball;
	goto L2_Out;

L2_Strike:
	STRIKE++; goto PHASE3;

L2_Ball:
	BALL++; goto PHASE3;

L2_Out:
	OUT++; goto PHASE3;

L2_Error:
	PutStr("\nError retry!"); goto PHASE0;

PHASE3: // Compare Third
	//	PutStr("\nThird  : ");
	//	B3 = GetInt();
	if (B1 == B3) goto L3_Error;
	if (B2 == B3) goto L3_Error;
	if (A1 == B3) goto L3_Ball;
	if (A2 == B3) goto L3_Ball;
	if (A3 == B3) goto L3_Strike;
	goto L3_Out;

L3_Strike:
	STRIKE++; goto PHASE4;

L3_Ball:
	BALL++; goto PHASE4;

L3_Out:
	OUT++; goto PHASE4;

L3_Error:
	//	PutStr("\nError retry"); goto PHASE0;

PHASE4: // Results
	strike = STRIKE;
	ball = BALL;
	goto RETURN_DEFENSE;

////////////////////////////////////////////////////////////

	// Phase 1
Phase1:
	
	goto DEFENSE;
RETURN_DEFENSE:

//	PutInt(n[0]); PutInt(n[1]); PutInt(n[2]);
//	PutStr("\nStrike ? ");
//	strike = GetInt();
//	PutStr("\nBall ? ");
//	ball = GetInt();
//	PutStr("\n");

	if (!(strike == 3)) goto P11;
	PutStr("Result is ");
	PutInt(n[0]), PutInt(n[1]), PutInt(n[2]);
	PutStr(" at ");
	PutInt(inning+1);
	PutStr(" inning\n");

	LOOP++;
	INN += inning;
	if (LOOP > 1000)
		goto FINISH;
	goto Phase0;
FINISH:
	PutStr("Average is ");
	PutInt(INN/LOOP);
	PutStr("\n");

	return;

P11:
	if (!(strike + ball == 3)) goto P14;
	i = 0;
P12:
	if (!(i < 10)) goto P13;
	expect[i] = 0;
	i++;
	goto P12;
P13:
	expect[n[0]] = 1;
	expect[n[1]] = 1;
	expect[n[2]] = 1;
	goto Phase5;

P14:
	if (!(strike + ball == 0)) goto P15;
	expect[n[0]] = 0;
	expect[n[1]] = 0;
	expect[n[2]] = 0;
	goto Phase2;

P15:
	if (!(strike != 0)) goto P18;
	i = 0;
P17:
	if (!(i < 3)) goto P18;
	if (!(expect[n[i]] != 0)) goto P16;
	expect[n[i]] += strike;
P16:
	i++;
	goto P17;
P18:

	if (!(ball != 0)) goto P21;
	i = 0;
P20:
	if (!(i < 3)) goto P21;
	if (!(expect[n[i]] != 0)) goto P19;
	expect[n[i]] += ball;
P19:
	i++;
	goto P20;
P21:
	goto Phase2;

	// Phase 2
Phase2:
	history[inning][0] = n[0];
	history[inning][1] = n[1];
	history[inning][2] = n[2];
	inning++;

	i = 0;
	except = 0;

P41:	// Except 가 몇개 인지 계산 - Except 는 확실하게 기대값이 아닌것의 갯수
	if (!(i < 10)) goto P43;
	if (!(expect[i]) == 0) goto P42;
	except++;
	select[i] = 0;
P42:
	i++;
	goto P41;

P43:
	if (!(except <= 7)) goto Phase3;
	if (!(except <= 5 || exceed != 1 || max < 20)) goto Phase4;

	// Phase 3
Phase3:
	n[0] = rand() % 10;
L30:
	if (!(expect[n[0]]) == 0) goto L31;
	n[0] = rand() % 10;
	goto L30;
L31:
	n[1] = rand() % 10;
L32:
	if (!(expect[n[1]] == 0)) goto L33;
	n[1] = rand() % 10;
	goto L32;
L33:
	if (!(n[0] == n[1])) goto L34;
	n[1] = rand() % 10;
	goto L32;
L34:
	n[2] = rand() % 10;
L35:
	if (!(expect[n[2]]) == 0) goto L36;
	n[2] = rand() % 10;
	goto L35;
L36:
	if (!(n[0] == n[2] || n[1] == n[2])) goto L37;
	n[2] = rand() % 10;
	goto L35;
L37:
	i = 0;
L38:
	if (!(i < inning)) goto L40;
	if (!(history[i][0] == n[0] && history[i][1] == n[1] && history[i][2] == n[2])) goto L39;
	exceed = 1;
	goto Phase1;
L39:
	i++;
	goto L38;
L40:
	premax = max;
	max = expect[n[0]] + expect[n[1]] + expect[n[2]];
	if (!(premax > max)) goto L41;
	goto Phase3;

L41:	
	goto Phase1;


	// Phase 4
Phase4:
	i = 0;
L60:
	if (!(i < 10)) goto L62;
	if (!(expect[i] != 0)) goto L61;
	expect[i] = 1;
L61:
	i++;
	goto L60;
L62:

	goto Phase3;

	// Phase 5. Final
Phase5:
	if (!(cum < 2)) goto P71;

	temp = n[0];
	n[0] = n[1];
	n[1] = n[2];
	n[2] = temp;	
	cum++;
	goto Phase1;

P71:
	temp = n[1];
	n[1] = n[2];
	n[2] = temp;
	cum = 0;
	goto Phase1;

	return;
}