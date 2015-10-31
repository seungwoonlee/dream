#include <stdio.h>
#include <stdlib.h>

const int card[52] = {
	2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 1,
	2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 1,
	2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 1,
	2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 1
};

const char *cardname[52] = {
/*	  2 ,   3 ,   4 ,   5 ,   6 ,   7 ,   8 ,   9 ,  10 ,   J ,   Q ,   K ,   A */
	"C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9", "C0", "CJ", "CQ", "CK", "CA",
	"D2", "D3", "D4", "D5", "D6", "D7", "D8", "D9", "D0", "DJ", "DQ", "DK", "DA",
	"H2", "H3", "H4", "H5", "H6", "H7", "H8", "H9", "H0", "HJ", "HQ", "HK", "HA",
	"S2", "S3", "S4", "S5", "S6", "S7", "S8", "S9", "S0", "SJ", "SQ", "SK", "SA"
};

void main(void)
{
	int i = 0;

MAIN0:
	if (!( i < 52 )) goto MAIN1;
	printf("%s ", cardname[i]);
	i++;
	goto MAIN0;
MAIN1:
	return;
}