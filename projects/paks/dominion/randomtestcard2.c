#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define CARD_TEST "Smithy"
#define ITERATIONS 50000

// Global variables
int failCardEffect = 0;        
int failDiscardCard = 0;       
int failDrawCard = 0;          
int failDeckHandCount = 0;     


void testSmithy(int p, struct gameState *game)
{
    struct gameState pTest;   // Allows for manipulation of the gameState during test.
    int bonus = 0;          // Counts value of bonus.
    int resultCE, resultDR1, resultDR2, resultDR3, resultDI;

    // Sets up initial gameState prior to manipulation during test. 
    memcpy(&pTest, game, sizeof(struct gameState));

    // Invokes and stores the smithy case from cardEffect. */
    resultCE = cardEffect(smithy, 0, 0, 0, game, 0, &bonus);

    // Draws 3 cards, per the Smithy specification. */
    resultDR1 = drawCard(p, &pTest);
    resultDR2 = drawCard(p, &pTest);
    resultDR3 = drawCard(p, &pTest);

    // Places used Smithy card in the discard pile. */
    resultDI = discardCard(0, p, &pTest, 0);

    // Counts expected hand and deck. 
    int eHandCount = game->handCount[p];
    int eDeckCount = game->deckCount[p];
    int eDiscardCount = game->discardCount[p];

    // Counts actual hand and deck. 
    int aHandCount = pTest.handCount[p];
    int aDeckCount = pTest.deckCount[p];
    int aDiscardCount = pTest.discardCount[p];

    // Tests for failure of first drawcard. 
    if (resultDR1 == -1 && pTest.deckCount[p] != 0)
    {
        failDrawCard++;
    }
    // Tests for failure of second drawcard. 
    if (resultDR2 == -1 && pTest.deckCount[p] != 0)
    {
        failDrawCard++;
    }
    // Tests for failure of third drawcard. 
    if (resultDR3 == -1 && pTest.deckCount[p] != 0)
    {
        failDrawCard++;
    }

    // Tests cardEffect() and discardCard() for failure. 
    if (!(resultCE == 0 && resultDI == 0))
    {
        if (resultCE)  // Tests result of cardEffect().
        {
            failCardEffect++;
        }
        if (resultDI)  // Tests result of discardCard().
        {
            failDiscardCard++;
        }
    }

    // Tests if expected values match actual values for hand, deck, and discard pile. 
    if (!(eHandCount == aHandCount && eDeckCount == aDeckCount && eDiscardCount == aDiscardCount))
    {
        failDeckHandCount++;
    }
}

int main ()
{
     printf("RANDOM TEST: %s\n", CARD_TEST);

    int i, j;          
    int player;         
    struct gameState G; 
    srand(time(NULL));

    // Initializes gameState to a random value. Referenced from testDrawCard.c
    for (i = 0; i < ITERATIONS; i++)
    {
        for (j = 0; j < sizeof(struct gameState); j++)
        {
            ((char*)&G)[j] = floor(Random() * 256); // Provides random values for initial gameState.
        }
        // generating random values for initialized variables
        player = floor(Random() * MAX_PLAYERS);
        G.deckCount[player] = floor(Random() * MAX_DECK);
        G.handCount[player] = floor(Random() * MAX_HAND);
        G.discardCount[player] = floor(Random() * MAX_DECK);
        G.playedCardCount = floor(Random() * (MAX_DECK - 1));
        G.whoseTurn = player;
        //
        testSmithy(player, &G);
    }

    // Counts total number of failures for all tests.
    int totalFailCount = failCardEffect + failDiscardCard +
                        failDrawCard + failDeckHandCount;
    printf ("\nFAILED: %d TESTS\n\n", totalFailCount);
    
    if (failDrawCard > 0)
        printf("\nFAILED: %d DRAW CARD TESTS\n", failDrawCard);   
    if (failCardEffect > 0)
        printf("\nFAILED: %d CARD EFFECT TESTS\n\n", failCardEffect);
    if (failDiscardCard > 0)
        printf("\nFAILED: %d DISCARD TESTS\n", failDiscardCard);  
    if (failDeckHandCount > 0)
        printf("\nFAILED: %d YOUR HAND TESTS\n", failDeckHandCount);
    printf("\n");

    return 0;
}

