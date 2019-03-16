#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
//council room
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
    state.hand[currentPlayer][0] = council_room;
    state.handCount[1] = 0;
    printf("COUNCIL ROOM TESTS:\n\n"); //Testing a known good function. Should return all passing values if done correctly.
    if(cardEffect(council_room, 0, 0, 0, &state, 0, &bonus))
    {
        printf("FAILED: CARD EFFECT\n");
        failedTest = 1;
    }
    else printf("PASSED: CARD EFFECT\n");
    
    if(state.handCount[currentPlayer] != (currentHandCount + 3))
    {
        failedTest = 1;
        printf("FAILED: WRONG NUMBER OF CARDS IN HAND\n");
    }
    else printf("PASSED: CORRECT NUMBER OF CARDS IN HAND\n");
    currentHandCount = currentHandCount + 3;
    
    if(state.playedCards[state.playedCardCount-1] != council_room)
    {
        printf("FAILED: COUNCIL ROOM WAS NOT DISCARDED\n");
        failedTest = 1;
    }
    else printf("PASSED: COUCIL ROOM WAS DISCARDED\n");
    
    if(state.handCount[1] != 1) //checking is opponent discard hand 
    {
        printf("FAILED; OPPONENT HAS DRAWN\n");
        failedTest = 1;
    }
    else printf("PASSED: OPPONENT HAS NOT DRAWN\n");
    
    
    if(!failedTest)
    printf("Council Room PASSED ALL TESTS\n\n");
    else printf("Council Room Tests FAILED\n\n");
    
    return 0;
}