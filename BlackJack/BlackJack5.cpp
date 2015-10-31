// 5 Level : Blackjack Determin and Defense - Removing Global Variables
#include <stdlib.h>
#include <time.h>
#include "dream.h"

const int card[52] = {
	2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11, 
	2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11, 
	2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11, 
	2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11 
};
const char *cardname[52] = {
  /*  0     1     2     3     4     5     6     7     8      9    10    11    12
   	 13    14    15    16    17    18    19    20    21     22    23    24    25
	 26    27    28    29    30    31    32    33    34     35    36    37    38
	 39    40    41    42    43    44    45    46    47     48    49    50    51 */
	"C2 ","C3 ","C4 ","C5 ","C6 ","C7 ","C8 ","C9 ","C10 ","CJ ","CQ ","CK ","CA ",
	"D2 ","D3 ","D4 ","D5 ","D6 ","D7 ","D8 ","D9 ","D10 ","DJ ","DQ ","DK ","DA ",
	"H2 ","H3 ","H4 ","H5 ","H6 ","H7 ","H8 ","H9 ","H10 ","HJ ","HQ ","HK ","HA ",
	"S2 ","S3 ","S4 ","S5 ","S6 ","S7 ","S8 ","S9 ","S10 ","SJ ","SQ ","SK ","SA "
};

const int Invalid = -1;
const int GameStop = 0;
const int Hit = 1;
const int Stand = 2;
const int Split = 3;

const int HandyBurst = 0;	
const int DealerBurst = 1;
const int Race = 2;
const int DealerBlackjack = 3;
const int BothBlackjack = 4;

const int LOOP = 1000;	// 총 게임루프 횟수

// Global Variables
int flagGameLoopStop = 0;
int cntGameLoop = 0;
int flagDealerIsBlackjack = 0;
int flagHandyBlackjack = 0;

int stateGameSet = 0;		// 게임이 끝나는 유형
int stateHandyBurst = 0;
int stateDealerBurst = 0;

int cntHandyWin = 0;	// count of Handy's Win
int cntDealerWin = 0;	// count of Dealer's Win
int cntPush = 0;		// count of Draw
int earnPoint = 10000;

int flagGameSet;
int currentDealerCardIndex;
int currentHandyCardIndex;

void Init(int dealer[10], int handy[2][10], int deck[52])
{
	int i;
	int j;

	// deck[52] 초기화
	for (i = 0; i < 52; i++)
	{
		deck[i] = Invalid;	// Invalid == -1 값이 채워졌는지 확인용으로 사용됨
	}
	// dealer[10] 초기화
	for (i = 0; i < 10; i++)
	{
		dealer[i] = Invalid;
		// handy[2][10] 초기화 - Split 때문에 준비
		for (j = 0; j < 2; j++)
		{
			handy[j][i] = Invalid;
		}
	}
	return;
}

void Shuffle(int deck[52])
{
	int i;
	int j;

	// 비중복 랜덤 나쁜 알고리즘
	for (i = 0; i < 52; i++)
	{
		deck[i] = rand() % 52;
		for (j = 0; j < i; j++)
		{
			if ( deck[j] == deck[i] )
			{
				deck[i] = rand() % 52;
				j = 0;
				continue;
			}
		}
	}
	return;
}

void Deal(int dealer[10], int handy[2][10], int deck[52])
{
	Shuffle(deck);
	dealer[0] = deck[0];
	dealer[1] = deck[1];
	handy[0][0] = deck[2];
	handy[0][1] = deck[3];

	currentDealerCardIndex = 2;
	currentHandyCardIndex = 2;	
	PutStr("Dealer's Card is ");
	PutStr(cardname[dealer[0]]);
	PutStr("\n");
	PutStr("Handy's  Card is ");
	PutStr(cardname[handy[0][0]]);
	PutStr(cardname[handy[0][1]]);
	PutStr("     ");
	PutInt(card[handy[0][0]] + card[handy[0][1]]);
	PutStr("\n");
	return;
}

int SumHandy(int handy[2][10])
{
	int i;
	int sumOfHandy = 0;

	for (i = 0; handy[0][i] != -1 && i < 10; i++)
	{
		sumOfHandy = sumOfHandy + card[handy[0][i]];
	}
	return sumOfHandy;
}

int CheckSplitAvailable(int handy[2][10], int stateSplit)
{
	int possibleSplit = 0;

	if (stateSplit == 1)
	{
		possibleSplit = 0;
		return 0;
	}
	if ( handy[0][0] % 13 == handy[0][1] % 13 )
	{
		possibleSplit = 1;
	}
	else
	{
		possibleSplit = 0;
	}	
	return possibleSplit;
}

int Determine(int dealer[10], int handy[2][10], int stateSplit)
{
	
	int input = 0;
	int sumOfHandy;
	int possibleSplit = 0;	// 스프릿 가능여부


	if (cntGameLoop >= LOOP)
	{
		input = GameStop;
		return input;
	}
	sumOfHandy = SumHandy(handy);
	possibleSplit = CheckSplitAvailable(handy, stateSplit);
	if (possibleSplit == 1)
	{
		if (handy[0][0] == 11 || handy[0][0] == 11 )
		{
			input = 3;
			return input;
		}
		else if (handy[0][0] == 4 || handy[0][0] == 5 || handy[0][0] == 10)
		{
			// Skip
		}
		else if (handy[0][0] == 2 || handy[0][0] == 3)
		{
			if (dealer[0] >= 4 && dealer[0] <= 7)
			{
				input = 3;
				return input;
			}
		}
		else if (handy[0][0] == 6)
		{	
			if (dealer[0] >= 3 && dealer[0] <= 6)
			{
				input = 3;
				return input;
			}
		}
		else if (handy[0][0] == 7)
		{
			if (dealer[0] >= 2 && dealer[0] <= 7)
			{
				input = 3;
				return input;
			}
		}
		else if (handy[0][0] == 9)
		{
			if ((dealer[0] >= 2 && dealer[0] <= 6) || (dealer[0] >= 8 && dealer[0] <= 9))
			{
				input = 3;
				return input;
			}
		}
	}
	if ( (dealer[0] == 2 || dealer[0] == 3) && sumOfHandy == 12 )
	{
		input = Stand;
		return input;
	}
	else if (sumOfHandy <= 11)
	{
		input = Hit;
		return input;
	}
	else if (sumOfHandy > 17)
	{
		input = Stand;
		return input;
	}
	else if (dealer[0] >= 7)
	{
		input = Hit;
		return input;
	}
	else if (dealer[0] <= 6)
	{
		input = Stand;
		return input;
	}
	return input;
}

int Ask(int dealer[10], int handy[2][10], int stateSplit)
{
//	PutStr("\n");
//	PutStr("1) Hit\n");
//	PutStr("2) Stand\n");
//	PutStr("3) Split\n");
//	PutStr("Your Choice ? ");
//	input = GetInt();
//	PutStr("\n\n");
	return Determine(dealer, handy, stateSplit);
}

void CheckHandyBurst(int handy[2][10])
{
	int sumOfHandy;

	sumOfHandy = SumHandy(handy);
	if (sumOfHandy > 21)
	{
		stateHandyBurst = 1;
	}
	else
	{
		stateHandyBurst = 0;
	}	
	return;
}

void ShowHandyCard(int handy[2][10])
{
	int i;

	PutStr("Handy's  Card is ");
	for (i = 0; handy[0][i] == -1; i++)
	{
		PutStr(cardname[handy[0][i]]);
	}
	PutStr("\n");
	return;
}

int PhaseHit(int input, int dealer[10], int handy[2][10], int deck[52], int stateSplit)
{	
	handy[0][currentHandyCardIndex] = deck[currentHandyCardIndex+2];
	CheckHandyBurst(handy);
	if (stateHandyBurst == 1)
	{
		flagGameSet = 1;
		stateGameSet = HandyBurst;
		return input;
	}
	currentHandyCardIndex = currentHandyCardIndex + 1;
	ShowHandyCard(handy);
	input = Ask(dealer, handy, stateSplit);
	return input;
}

int SumDealer(int dealer[10])
{
	int i;
	int sumOfDealer = 0;

	// 예외케이스 딜러의 첫카드가 A, A 일경우
	if ((card[dealer[0]] % 13) == 11 && (card[dealer[1]] % 13) == 11 && dealer[2] == -1)
	{
		sumOfDealer = 12;
		return sumOfDealer;
	}
	for (i = 0; dealer[i] != -1 && i < 10; i++)
	{
		sumOfDealer = sumOfDealer + card[dealer[i]];
	}
	return sumOfDealer;
}

void CheckDealerBurst(int dealer[10])
{
	int sumOfDealer;

	sumOfDealer = SumDealer(dealer);
	if (sumOfDealer > 21)
	{
		stateDealerBurst = 1;
	}
	else
	{
		stateDealerBurst = 0;
	}
	return;
}

void ShowDealerCard(int dealer[10])
{
	int i;
	PutStr("Dealer's Card is ");
	for (i = 0; dealer[i] != -1; i++)
	{
		PutStr(cardname[dealer[i]]);
	}
	PutStr("\n");
	return;
}

void PhaseStand(int dealer[10], int handy[2][10], int deck[52])
{
	int sumOfHandy;
	int sumOfDealer;
	
	sumOfDealer = SumDealer(dealer);
	sumOfHandy = SumHandy(handy);
	while (true)
	{
		
		if (sumOfDealer >= 17)
		{	// 딜러가 17이상이면 게임종료
			ShowDealerCard(dealer);
			PutStr("Dealer is not Burst\n\n");
			flagGameSet = 1;
			stateGameSet = Race;
			return;
		}
		else
		{	// 딜러가 16이하이면 추가로 한장을 더 받고  버스트인지 체크한다. 버스트라면 게임종료
			dealer[currentDealerCardIndex] = deck[currentDealerCardIndex + 2];
			CheckDealerBurst(dealer);
			if (stateDealerBurst == 1)
			{
				flagGameSet = 1;
				stateGameSet = DealerBurst;
				return;
			}			
			if (sumOfDealer >= sumOfHandy)
			{
				ShowDealerCard(dealer);
				PutStr("Dealer is not Burst\n\n");
				flagGameSet = 1;
				stateGameSet = Race;
				return;
			}
		}
		currentDealerCardIndex = currentDealerCardIndex + 1;
	}
	return;
}

int NextSplit(int input, int dealer[10], int handy[2][10], int deck[52], int stateSplit)
{
	handy[0][0] = handy[1][0];
	handy[0][1] = deck[currentHandyCardIndex+3];
	handy[0][2] = -1;
	PutStr("Next Split Phase\n");
	ShowHandyCard(handy);	
	return Ask(dealer, handy, stateSplit);
}

int PhaseSplit(int input, int dealer[10], int handy[2][10], int deck[52], int stateSplit)
{
	int possibleSplit = 0;

	possibleSplit = CheckSplitAvailable(handy, stateSplit);
	if (possibleSplit == 0)
	{
		PutStr("Split is impossible, retry\n");
		return Ask(dealer, handy, stateSplit);
	}
	while (1)
	{
		CheckSplitAvailable(handy, stateSplit);
		if (possibleSplit == 0)
		{
			stateSplit = 0;
			ShowHandyCard(handy);			
			return Ask(dealer, handy, stateSplit);
		}
		if (handy[1][0] != handy[0][1])
		{
			handy[1][0] = handy[0][1];
			handy[0][1] = deck[currentHandyCardIndex+2];
			currentHandyCardIndex = currentHandyCardIndex + 1;
			break;
		}
		else
		{
			currentHandyCardIndex = currentHandyCardIndex + 1;
			handy[0][1] = deck[currentHandyCardIndex+2];
		}
	}	
	stateSplit = 1;
	ShowHandyCard(handy);
	return Ask(dealer, handy, stateSplit);
}

void ShowGameResult(int dealer[10], int handy[2][10], int stateSplit)
{
	int sumOfHandy;
	int sumOfDealer;

	sumOfHandy = SumHandy(handy);
	sumOfDealer = SumDealer(dealer);

	if (stateGameSet == 0)	// Handy Burst
	{
		if (stateSplit != 1)
		{
			ShowDealerCard(dealer);
		}		
		ShowHandyCard(handy);
		PutStr("\n");
		PutStr("You Lose, Handy Burst\n");
		cntDealerWin = cntDealerWin + 1;
		earnPoint = earnPoint - 10;
	}
	else if (stateGameSet == 1) // Dealer Burst
	{
		if (stateSplit != 1)
		{
			ShowDealerCard(dealer);
		}	
		ShowHandyCard(handy);
		PutStr("\n");
		PutStr("You Win, Dealer Burst\n");
		cntHandyWin = cntHandyWin + 1;
		earnPoint = earnPoint + 10;
	}
	else if (stateGameSet == 2)	// Race
	{		
		if ( sumOfHandy > sumOfDealer )
		{
			if (stateSplit != 1)
			{
				ShowDealerCard(dealer);
			}	
			ShowHandyCard(handy);
			PutStr("\n");
			PutStr("You Win, ");
			PutInt(sumOfHandy);
			PutStr(" vs ");
			PutInt(sumOfDealer);
			PutStr("\n");
			cntHandyWin = cntHandyWin + 1;
			earnPoint = earnPoint + 10;
		}
		if ( sumOfHandy < sumOfDealer )
		{
			if (stateSplit != 1)
			{
				ShowDealerCard(dealer);
			}	
			ShowHandyCard(handy);
			PutStr("\n");
			PutStr("You Lose, ");
			PutInt(sumOfHandy);
			PutStr(" vs ");
			PutInt(sumOfDealer);
			PutStr("\n");
			cntDealerWin = cntDealerWin + 1;
			earnPoint = earnPoint - 10;
		}
		if ( sumOfHandy == sumOfDealer )
		{
			if (stateSplit != 1)
			{
				ShowDealerCard(dealer);
			}	
			ShowHandyCard(handy);
			PutStr("\n");
			PutStr("Push, ");
			PutInt(sumOfHandy);
			PutStr(" vs ");
			PutInt(sumOfDealer);
			PutStr("\n");
			cntPush = cntPush + 1;
		}
	}
	else if (stateGameSet == 3)
	{
		if (stateSplit != 1)
		{
			ShowDealerCard(dealer);
		}	
		ShowHandyCard(handy);
		PutStr("\n");
		PutStr("Dealer is Blackjack, ");
		PutInt(sumOfHandy);
		PutStr(" vs ");
		PutInt(sumOfDealer);
		PutStr("\n");
		cntDealerWin = cntDealerWin + 1;
		earnPoint = earnPoint - 10;
	}
	else if (stateGameSet == 4)
	{
		if (stateSplit != 1)
		{
			ShowDealerCard(dealer);
		}	
		ShowHandyCard(handy);
		PutStr("\n");
		PutStr("Both Blackjack, ");
		PutInt(sumOfHandy);
		PutStr(" vs ");
		PutInt(sumOfDealer);
		PutStr("\n");
		cntPush = cntPush + 1;
	}
	PutStr("\n");
	return;
}

void CheckDealerBackjack(int dealer[10])
{
	if (card[dealer[0]] + card[dealer[1]] == 21)
	{
		flagDealerIsBlackjack = 1;
	}
	else
	{
		flagDealerIsBlackjack = 0;
	}
	return;
}

void CheckHandyBlackjack(int handy[2][10])
{
	if (card[handy[0][0]] + card[handy[0][1]] == 21)
	{
		flagHandyBlackjack = 1;
	}
	else
	{
		flagHandyBlackjack = 0;
	}
	return;
}

void main(void)
{
	int deck[52] = { 0, };		// Card Deck
	int dealer[10] = { 0, };	// Dealer's cards
	int handy[2][10] = { 0, };	// Handy's cards

	int stateSplit = 0;
	int input;

	srand((unsigned)time(NULL));	
	while (true)
	{
		Init(dealer, handy, deck);
		Deal(dealer, handy, deck);	// 딜러2장, 핸디2장을 받고 딜러1장과 핸디2장을 화면에 보여주면서, 1) Hit, 2) Stand, 3) Split 을 물어본다.		
		CheckDealerBackjack(dealer);
		CheckHandyBlackjack(handy);
		if (flagDealerIsBlackjack == 1)	// 딜러가 블랙잭이면 일단 게임셋 모드로 간다. 단 핸디가 블랙잭인 경우는 Push 이므로 체크
		{			
			if (flagHandyBlackjack == 1)	
			{
				stateGameSet = 4;	// 딜러가 블랙잭이면서 핸디도 블랙잭인 경우
			}
			else
			{
				stateGameSet = 3;	// 딜러가 블랙잭인경우
			}
		}
		else
		{
			input = Ask(dealer, handy, stateSplit);
			while (true)	// 유저의 입력여부에 따라 flagGameSet이 셋팅될때까지 반복
			{
				if (input == GameStop)
				{
					flagGameLoopStop = 1;	// 게임 반복 루프의 종료, Determine() 함수에서 cntGameLoop 가 일정횟수 이상이면 0 입력하도록 한다.
					break;
				}
				if (input == Hit)		// 1)
				{
					input = PhaseHit(input, dealer, handy, deck, stateSplit);
				}
				else if (input == Stand) // 2)
				{
					PhaseStand(dealer, handy, deck);
				}
				else if (input == Split) // 3)
				{
					input = PhaseSplit(input, dealer, handy, deck, stateSplit);
				}
				else if ( input != GameStop && input != Hit && input != Stand && input != Split )	// 1,2,3 이외의 입력이 왔을경우 다시 입력 요구
				{
					PutStr("Wrong Input retry!\n");
					input = Ask(dealer, handy, stateSplit);
				}
				if (flagGameSet == 1)
				{
					if (stateSplit == 1)
					{
						ShowGameResult(dealer, handy, stateSplit);
						stateSplit = 0;
						input = NextSplit(input, dealer, handy, deck, stateSplit);
						continue;
					}
					break;
				}
			}
		}
		if (flagGameLoopStop == 1)
		{
			PutStr("\nAll Game is finished!\n");
			break;
		}
		ShowGameResult(dealer, handy, stateSplit);
		cntGameLoop = cntGameLoop + 1;		
	}
	PutStr("\nCount of Dealer Win is ");
	PutInt(cntDealerWin);
	PutStr("\nCount of Handy  Win is ");
	PutInt(cntHandyWin);

	PutStr("\nHandy Win Ratio is ");
	PutInt( (int) (((double)cntHandyWin/((double)LOOP-(double)cntPush)) *(double)100) );
	PutStr(" Percents\n");	
	PutStr("\n Total Earned Point is ");
	PutInt(earnPoint);
	PutStr("  (from 10000)\n");	
	return;
}