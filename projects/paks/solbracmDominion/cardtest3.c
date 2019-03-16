#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
//village
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
	int currentActions = state.numActions;
	printf("VILLAGE TESTS:\n\n");
	if(cardEffect(village, 0, 0, 0, &state, 0, &bonus))
	{
		printf("FAILED: CARD EFFECTS\n");
		failedTest = 1;
	}
	else printf("PASSED: CARD EFFECTS\n");
	
	
	//double checking if number of cards in hand is correct
	if(state.handCount[currentPlayer] != currentHandCount)
	{
		printf("FAILED: WRONG NUMBER OF CARDS IN HAND\n");
		failedTest = 1;
	}
	else printf("PASSED: CORRECT NUMBER OF CARDS IN HAND\n");
	
	if(state.numActions != currentActions+2) //double checking if number of actions in hand is correct
	{
		printf("FAILED: WRONG NUMBER OF ACTIONS\n");
		failedTest = 1;
	}
	else printf("PASSED: CORRECT NUMBER OF ACTIONS\n");
	
	if(!failedTest)
	printf("Village PASSED ALL TESTS\n\n");
	else printf("Village Tests FAILED\n\n");
	
	return 0;
}