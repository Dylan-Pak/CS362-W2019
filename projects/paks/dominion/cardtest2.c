#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
//smithy
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
	state.hand[currentPlayer][0] = smithy;
	printf("SMITHY TESTS:\n\n");
	if(cardEffect(smithy, 0, 0, 0, &state, 0, &bonus)) // checking if smithy effect completes
	{
		printf("FAILED: CARD EFFECT\n");
		failedTest = 1;
	}
	else printf("PASSED: CARD EFFECT\n");
	
	if(state.handCount[currentPlayer] != (currentHandCount + 2)) //checking if smithy ends with the correct number of cards in the hand
	{
		failedTest = 1;
		printf("FAILED: WRONG NUMBER OF CARDS IN HAND\n");
	}
	else printf("PASSED: CORRECT NUMBER IF CARDS IN HAND\n");
	currentHandCount = currentHandCount + 2;
	
	if(state.playedCards[state.playedCardCount-1] != smithy) // checking if smithy is discarded
	{
		printf("FAILED: SMITHY WAS NOT DISCARDED\n");
		failedTest = 1;
	}
	else printf("PASSED: SMITHY WAS DISCARDED\n");
	
	if(!failedTest)
	printf("Smithy PASSED ALL TESTS\n\n");
	else printf("Smithy Tests FAILED\n\n");
	
	return 0;
}