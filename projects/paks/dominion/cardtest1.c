#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
//adventurer
int main(int argc, char** argv)
{
	struct gameState state;
	int bonus = 0;
	int currentPlayer = whoseTurn(&state);
	int failedTest = 0;
	int arr[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	if(argv[1])
	{
		initializeGame(2, arr, atoi(argv[1]), &state);
	}
	else
	{
		initializeGame(2, arr, 4, &state);
	}
	int currentHandCount = state.handCount[currentPlayer];
	printf("ADVENTURER TESTS:\n\n");
	if(cardEffect(adventurer, 0, 0, 0, &state, 0, &bonus))
	{
		printf("FAILED: CARD EFFECT\n"); //checking is adventurer is working correctly
		failedTest = 1;
	}
	else printf("PASSED: CARD EFFECT\n");
	
	if(state.handCount[currentPlayer] != (currentHandCount + 2))
	{
		failedTest = 1;
		printf("FAILED: HANDS DOES NOT MATCH\n");
	}
	else printf("PASSED: HANDS DOES MATCH\n");

	currentHandCount = currentHandCount + 2;
	if	  (((state.hand[currentPlayer][currentHandCount-1] == copper) 
		|| (state.hand[currentPlayer][currentHandCount-1] == silver)
		|| (state.hand[currentPlayer][currentHandCount-1] == gold))
		&&
		   ((state.hand[currentPlayer][currentHandCount-2] == copper) 
		|| (state.hand[currentPlayer][currentHandCount-2] == silver)
		|| (state.hand[currentPlayer][currentHandCount-2] == gold)))
		{
			printf("PASSED: CARDS ARE TREASURE\n");
		}
	else
	{
		printf("FAILED: CARDS ARE NOT TREASURE\n");
		failedTest = 1;
	}
	
	if(!failedTest)
	{
		printf("Adventurer PASSED ALL TESTS\n\n");
	}
	else printf("Adventurer Tests FAILED\n\n");
	return 0;
}