#include <stdlib.h>
#include <Windows.h>
//#include <time.h>
#include "dream.h"


void main(void)
{
	int deck[52] = { 0, };
	int com[5];
	int user[5];	
	int a[5];
	int kind[2][13] = { 0, };
	int isUser = 0;		// 0:User,  1:Com
	int status[2] = { 0, }; // name of cards
	const int	NoPair		= 0;
	const int	OnePair		= 1;
	const int	TwoPair		= 2;
	const int	ThreeKind	= 3;
	const int	Straight	= 4;
	const int	Flush		= 5;
	const int	FullHouse	= 6;
	const int	FourKind	= 7;
	const int	StraightFlush	= 8;
	const int	RoyalStraightFlush	= 9;
	const char *statusStr[10] = {"No Pair",
								 "One Pair",
								 "Two Pairs",
								 "Three of a Kind",
								 "Straight",
								 "Flush",
								 "Full House",
								 "Four of a Kind",
								 "Straight Flush",
								 "Royal Flush"};
	const int	ComWin = 0;
	const int	YouWin = 1;
	const int	DrawComWin = 2;
	const int	DrawYouWin = 3;
	int result;
	const char *resultStr[5] = {"You Lose",
								"You Win",
								"Draw but You Lose by Top ",
								"Draw but You Win by Top ",
								"Draw"};
	const char *card[52] = {   /* 0     1     2     3     4     5     6     7     8      9    10    11    12
								 13    14    15    16    17    18    19    20    21     22    23    24    25
								 26    27    28    29    30    31    32    33    34     35    36    37    38
								 39    40    41    42    43    44    45    46    47     48    49    50    51 */
								"C2 ","C3 ","C4 ","C5 ","C6 ","C7 ","C8 ","C9 ","C10 ","CJ ","CQ ","CK ","CA ",
								"D2 ","D3 ","D4 ","D5 ","D6 ","D7 ","D8 ","D9 ","D10 ","DJ ","DQ ","DK ","DA ",
								"H2 ","H3 ","H4 ","H5 ","H6 ","H7 ","H8 ","H9 ","H10 ","HJ ","HQ ","HK ","HA ",
								"S2 ","S3 ","S4 ","S5 ","S6 ","S7 ","S8 ","S9 ","S10 ","SJ ","SQ ","SK ","SA "};
								
	int i;
	int j;
	int temp;
	int com_max = 0;
	int user_max = 0;
//	time_t ltime;
	int count = 0;
	int cntStraightFlush = 0;
	int cntStraight = 0;
	int cntFlush = 0;
	int cntFourCard = 0;
	int cntFullHouse = 0;
	int cntTriple = 0;
	int cntTwoPair = 0;
	int cntOnePair = 0;
	int cntNoPair = 0;

Phase1:
	i = 0;
	deck[i] = (GetTickCount() * rand()) % 52;	// real random 이 나오질 않아 부득히 GetTickCount() 함수 사용
	i++;

P10:
	if (! (i < 52) ) goto P15;

P11:
	deck[i] = (rand()) % 52;
	j = i - 1;

P12:
	if (! (j >= 0) ) goto P14;
	if (! (deck[j] != deck[i]) ) goto P13;
	j--;
	goto P12;

P13:
	goto P11;

P14:
	i++;
	goto P10;

// Deal
P15:
	i = 0;
	j = rand()%43;

P16:
	if (! (i < 5) ) goto P17;
	com[i] = deck[j+i*2];
	user[i]  = deck[j+i*2+1];
	i++;
	goto P16;

P17:

Phase2:
// Copy to a[]
	if (! (isUser == 0) ) goto P22;
	i = 0;

P20:
	if (! (i < 5) ) goto P21;
	a[i] = com[i];
	i++;
	goto P20;

P21:
	goto P24;

P22:
	i = 0;

P23:
	if (! (i < 5) ) goto P24;
	a[i] = user[i];
	i++;
	goto P23;


// Sorting
P24:	
	j = 0;

P25:
	i = 0;
	if (! (j < 4) ) goto P29;

P26:
	if (! (i < 4) ) goto P28;
	if (! (a[i]%13 > a[i+1]%13) ) goto P27;
	temp = a[i];
	a[i] = a[i+1];
	a[i+1] = temp;
P27:
	i++;
	goto P26;

P28:
	j++;
	goto P25;

P29:

//Phase3:
// Straight Check
	if (!( a[0]%13+4 == a[1]%13+3 &&
		   a[1]%13+3 == a[2]%13+2 &&
		   a[2]%13+2 == a[3]%13+1 &&
		   a[3]%13+1 == a[4]%13   &&
		   a[4]%13   == a[0]%13+4    )) goto P30;
	status[isUser] = Straight;
	cntStraight++;

P30:
// Flush Check
	if (!( a[0]/13 == a[1]/13 &&
		   a[1]/13 == a[2]/13 &&
		   a[2]/13 == a[3]/13 &&
		   a[3]/13 == a[4]/13 &&
		   a[4]/13 == a[0]/13    )) goto P32;
	if (!( status[isUser] == Straight )) goto P31;
	status[isUser] = StraightFlush;
	cntStraightFlush++;
	goto Phase4;

P31:	
	status[isUser] = Flush;
	cntFlush++;
	goto Phase4;

P32:
	if (!( status[isUser] == Straight )) goto P33;
	goto Phase4;

P33:
	i = 0;
	
P34:
	if (!( i < 5 )) goto P35;
	kind[isUser][a[i]%13]++;
	i++;
	goto P34;

P35:
// FourCard Check
	i = 0;

P36:
	if (!( i < 13 )) goto P38;
	if (!( kind[isUser][i] == 4 )) goto P37;
	status[isUser] = FourKind;
	cntFourCard++;
	goto Phase4;

P37:
	i++;
	goto P36;

P38:
// Triple and FullHouse Check
	i = 0;

P39:
	if (!( i < 13 )) goto P44;
	if (!( kind[isUser][i] == 3 )) goto P43;
	j = i + 1;

P40:
	if (!( j < 13 )) goto P42;
	if (!( kind[isUser][j] == 2 )) goto P41;	// FullHouse Check
	status[isUser] = FullHouse;
	cntFullHouse++;
	goto Phase4;

P41:
	j++;
	goto P40;

P42:
	status[isUser] = ThreeKind;
	cntTriple++;
	goto Phase4;

P43:
	i++;
	goto P39;

P44:
// Two Pairs Check
	i = 0;

P45:
	if (!( i < 13 )) goto P50;
	if (!( kind[isUser][i] == 2 )) goto P49;	// One Pair Check
	j = i + 1;

P46:
	if (!( j < 13 )) goto P48;
	if (!( kind[isUser][j] == 2 )) goto P47;
	status[isUser] = TwoPair;
	cntTwoPair++;
	goto Phase4;

P47:
	j++;
	goto P46;

P48:
	status[isUser] = OnePair;
	cntOnePair++;
	goto Phase4;

P49:
	i++;
	goto P45;

P50:
	status[isUser] = NoPair;
	cntNoPair++;

// Phase 4
Phase4:
	if (!( isUser == 0 )) goto P51;
	isUser = 1;
	goto Phase2;

P51:
	if (!( status[0] > status[1] )) goto P52;
	result = ComWin;
	goto Final;
P52:
	if (!( status[0] < status[1] )) goto P53;
	result = YouWin;
	goto Final;

P53:
	com_max = 0;
	user_max = 0;
	i = 0;

L54:
	if (!( i < 5 )) goto L56;
	if (!( com_max%13 < com[i]%13 )) goto L55;
	com_max = com[i];

L55:
	i++;
	goto L54;

L56:
	i = 0;

L57:
	if (!( i < 5 )) goto L59;
	if (!( user_max%13 < user[i]%13 )) goto L58;
	user_max = user[i];

L58:
	i++;
	goto L57;

L59:
	if (!( com_max%13 > user_max%13 )) goto L60;
	result = DrawComWin;
	goto Final;

L60:
	if (!( com_max%13 < user_max%13 )) goto L61;
	result = DrawYouWin;
	goto Final;

L61:
	if (!( com_max/13 > user_max/13 )) goto L62;
	result = DrawComWin;
	goto Final;

L62:
	result = DrawYouWin;
	goto Final;

// Final Phase
Final:
	PutStr("Com is  ");
	PutStr(card[com[0]]);PutStr(card[com[1]]);PutStr(card[com[2]]);PutStr(card[com[3]]);PutStr(card[com[4]]);
	PutStr(statusStr[status[0]] );
	PutStr("\nYou are ");
	PutStr(card[user[0]]);PutStr(card[user[1]]);PutStr(card[user[2]]);PutStr(card[user[3]]);PutStr(card[user[4]]);
	PutStr(statusStr[status[1]] );
	PutStr("\n");

	if (!( result == DrawComWin || result == DrawYouWin )) goto P58;
	PutStr("\nSame but Com Top card is ");
	PutStr(card[com_max]);
	PutStr("\n        User Top card is ");
	PutStr(card[user_max]);
	PutStr("\n\n");
	PutStr(resultStr[result]);
	PutStr("\n\n");
	goto END;
P58:
	PutStr(resultStr[result]);
	PutStr("\n\n");

END:
	status[0] = 0;
	status[1] = 0;
	
	i = 0;
P59:
	if (!( i < 13 )) goto P60;
	kind[0][i] = 0;
	kind[1][i] = 0;
	i++;
	isUser = 0;
	goto P59;
P60:

	if (!( count < 5000 )) goto EXIT;
	count++;
	goto Phase1;

EXIT:
	PutStr("\nNo Pair         : "); PutInt(cntNoPair);
	PutStr("\nOne Pair        : "); PutInt(cntOnePair);
	PutStr("\nTwo Pairs       : "); PutInt(cntTwoPair);
	PutStr("\nThree of a Kind : "); PutInt(cntTriple);
	PutStr("\nStraight        : "); PutInt(cntStraight);
	PutStr("\nFlush           : "); PutInt(cntFlush);
	PutStr("\nFull House      : "); PutInt(cntFullHouse);
	PutStr("\nFour of a Kind  : "); PutInt(cntFourCard);
	PutStr("\nStraight Flush  : "); PutInt(cntStraightFlush);
	PutStr("\n");
	return;
}