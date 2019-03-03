#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <math.h>
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CARD "Adventurer"
#define RUNS 10000

// Global variables to count failures
int carEffFailCount = 0;    
int shufFailCount = 0;       
int drawFailCount = 0;     
int dckHndFailCount = 0; 
int trsrFailCount = 0;

void testAdv(int p, struct gameState *game)
{
    struct gameState pTest; //initialize test environment
    int bonus = 0; //bonus counter
    int resultCE, resultsSHF, resultDRW; //results
    int i; //loop counter
    int played = 0;              //  played cards.
    int aTreasureCount = 0;  // actual treasure results
    int eTreasureCount = 0;  // expecected treasure results
    int curHand[MAX_HAND];   // current hand
    int treasureDrawn = 0;   // number of drawn treasures drawn
    int cardDrawn;          //  number of cards drawn from deck
    int inspect;               // inspect card

    memcpy(&pTest, game, sizeof(struct gameState)); //set game state
    resultCE = cardEffect(adventurer, 0, 0, 0, game, 0, &bonus); //store adventurer effect
    if (resultCE) //testing for card effect
    {
        carEffFailCount++;
    }
    while(treasureDrawn < 2) //test adventure effects
    {
        if (pTest.deckCount[p] < 1)
        {
            resultsSHF = shuffle(p, &pTest); //shufffle when deck is empty
            if (resultsSHF == -1 && pTest.deckCount[p] >= 1)  //testing for shuffle failure 
            {
                shufFailCount++;
            }
        }
        resultDRW = drawCard(p, &pTest); //testing for draw failure
        if (resultDRW == -1 && pTest.deckCount[p] != 0)
        {
            drawFailCount++;
        }
        cardDrawn = pTest.hand[p][pTest.handCount[p] - 1]; //testing is card is a treasure
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
            treasureDrawn++;    
        else
        {                  
            curHand[played] = cardDrawn;
            pTest.handCount[p]--; //go to next card in hand
            played++;    // tested cards
        }
    }

    while(played - 1 >= 0) // discard played cards in pile. */
    {
        pTest.discard[p][pTest.discardCount[p]++] = curHand[played - 1];
        played = played - 1; 
    }

    for (i = 0; i < game->handCount[p]; i++) // Counts actual number of treasures. 
    {
        inspect = game->hand[p][i];
        if (inspect == copper || inspect == silver || inspect == gold)
        {
            aTreasureCount++;
        }
    }
   
    for (i = 0; i < pTest.handCount[p]; i++) // Counts expected number of treasures. 
    {
        inspect = pTest.hand[p][i];
        if (inspect == copper || inspect == silver || inspect == gold)
        {
            eTreasureCount++;
        }
    }
    if (aTreasureCount != eTreasureCount) //does treasure match?
    {
        trsrFailCount++;
    }
    //expected outcome
    int aHandCount = game->handCount[p];
    int aDeckCount = game->deckCount[p];
    int aDiscardCount = game->discardCount[p];

    //actual outcome 
    int eHandCount = pTest.handCount[p];
    int eDeckCount = pTest.deckCount[p];
    int eDiscardCount = pTest.discardCount[p];

    //doese it match
    if (!(aHandCount == eHandCount && aDeckCount == eDeckCount && aDiscardCount == eDiscardCount))
    {
        dckHndFailCount++;
    }
}

int main ()
{
    printf("RANDOM TEST: %s\n", CARD);

    int i, j;  // Loop counters.
    int player;             
    int treasureCount; //number of treasures
    int treasures[] = {copper, silver, gold};
    struct gameState game;     
    srand(time(NULL));      
    //initialize to random values
    for (i = 0; i < RUNS; i++)
    {
        for (j = 0; j < sizeof(struct gameState); j++)
        {
            ((char*)&game)[j] = floor(Random() *256); // Provides random values for initial gameState.
        }
        //more random values
        player = floor(Random() * MAX_PLAYERS);
        game.deckCount[player] = floor(Random() * ((MAX_DECK - 3) + 1) + 3);
        treasureCount = floor(Random() * ((game.deckCount[player] - 3) + 1) + 3);
        //placing treasures cards in deck
        for (i = 0; i < treasureCount; i++)
        {
            game.deck[player][i] = treasures[rand() % 3];
        }
        game.discardCount[player] = 0;
        game.handCount[player] = floor(Random() * ((MAX_HAND - 3) + 1) + 3);
        game.whoseTurn = player;

        testAdv(player, &game); //test with random initialization
    }

    int totalFailCount = carEffFailCount + drawFailCount + shufFailCount + dckHndFailCount + trsrFailCount;

    printf ("\nFAILED: %d TESTS\n\n", totalFailCount);

    if (shufFailCount > 0)
        printf("\nFAILED: %d SHUFFLE TESTS\n", shufFailCount);
    if (drawFailCount > 0)
        printf("\nFAILED: %d DRAW CARD TESTS\n", drawFailCount);
    if (carEffFailCount > 0)
        printf("\nFAILED: %d CARD EFFECT TESTS\n", carEffFailCount);
    if (trsrFailCount > 0)
        printf("\nFAILED: %d TREASURE TESTS\n", trsrFailCount);
    if (dckHndFailCount > 0)
        printf("\nFAILED: %d YOUR HAND TESTS\n", dckHndFailCount);
    printf("\n");
    
    return 0;
}

