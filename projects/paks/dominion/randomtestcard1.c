#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <math.h>
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CARD_TEST "Council Room"
#define ITERATIONS 10000

//global vairables to count failures
int failCardEffect = 0;              
int failDiscardCard = 0;             
int failDrawCard = 0;                
int failNumBuys = 0;                 
int failDeckHandCountActive = 0;    
int failDeckHandCountOpponent = 0;  

void randomCouncilRoomTest(int p, struct gameState *game)
{
    struct gameState pTest;   // Allows for manipulation of the gameState during test.
    int bonus = 0;          // Counts value of bonus.
    int resultCE, resultDR1, resultDR2, resultDR3, resultDR4, resultDRO, resultDI;
    int i;                  // Loop counter.

    // Sets up initial gameState prior to manipulation during test.
    memcpy(&pTest, game, sizeof(struct gameState));

    // Invokes and stores the council_room case from cardEffect. 
    resultCE = cardEffect(council_room, 0, 0, 0, game, 0, &bonus);

    // Draws 4 cards, per the Council Room specification.
    resultDR1 = drawCard(p, &pTest);
    resultDR2 = drawCard(p, &pTest);
    resultDR3 = drawCard(p, &pTest);
    resultDR4 = drawCard(p, &pTest);

    // Increments number of buys (+1), per the Council Room specification.
    pTest.numBuys++;

    // Draws +1 card for each opponent, per the Council Room specification.
    for (i = 0; i < pTest.numPlayers; i++)
    {
        if (i != p) // Draws only for the opponent players.
        {
            resultDRO = drawCard(i, &pTest);
            // Tests for failure of drawcard. 
            if (resultDRO == -1 && pTest.deckCount[i] != 0)
            {
                failDrawCard++;
            }
        }
    }

    // Places used Council Room card in the discard pile.
    resultDI = discardCard(0, p, &pTest, 0);

    // Counts expected hand and deck. 
    int eHandCount = game->handCount[p];
    int eDeckCount = game->deckCount[p];

    // Counts actual hand and deck. 
    int aHandCount = pTest.handCount[p];
    int aDeckCount = pTest.deckCount[p];

    // Tests if resulting numBuys matches expected numBuys. 
    if (pTest.numBuys != game->numBuys)
    {
        failNumBuys++;
    }

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
    // Tests for failure of fourth drawcard. 
    if (resultDR4 == -1 && pTest.deckCount[p] != 0)
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

    // Tests if expected values match actual values for hand and deck of active player. 
    if (!(eHandCount == aHandCount && eDeckCount == aDeckCount))
    {
        failDeckHandCountActive++;
    }

    // Tests if expected values match actual values for hand and deck of each opponent. 
    for (i = 0; i < pTest.numPlayers; i++)
    {
        if (i != p)
        {
            if (!(game->handCount[i] == pTest.handCount[i] &&
                  game->deckCount[i] == pTest.deckCount[i]))
            {
                      failDeckHandCountOpponent++;
            }
        }
    }
}

int main ()
{
    printf("RANDOM TEST: %s\n", CARD_TEST);

    int i, j;           
    int player;         
    int deckCount;      
    int handCount;      
    int discardCount;   
    int players[] = {2, 3, 4};  //total number of players
    struct gameState G; 
    srand(time(NULL));  // Provides random seed from system time.

    // Initializes gameState to a random value. Referenced from testDrawCard.c.
    for (i = 0; i < ITERATIONS; i++)
    {
        for (j = 0; j < sizeof(struct gameState); j++)
        {
            ((char*)&G)[j] = floor(Random() * 256); // Provides random values for initial gameState.
        }
        // generating random values for initialized variables
        G.numPlayers = players[rand() % 3];
        G.numBuys = 1;
        G.playedCardCount = floor(Random() * (MAX_DECK - 1));
        player = G.numPlayers - 2;
        deckCount = floor(Random() * MAX_DECK);
        handCount = floor(Random() * MAX_HAND);
        discardCount = floor(Random() * MAX_DECK);
        G.whoseTurn = player;

        // initializing deckcount, handcount, and discardcount
        for (j = 0; j < G.numPlayers; j++)
        {
            G.deckCount[j] = deckCount;
            G.handCount[j] = handCount;
            G.discardCount[j] = discardCount;
        }

        // Calls the random test function
        randomCouncilRoomTest(player, &G);
    }

    // Counts total number of failures for all tests.
    int totalFailCount = failCardEffect + failDiscardCard + failDrawCard
                    + failDeckHandCountActive + failNumBuys;

    printf ("\nFAILED: %d TESTS\n\n", totalFailCount);
    
    if (failDrawCard > 0)
        printf("\nFAILED: %d DRAW CARD TESTS\n", failDrawCard);   
    if (failCardEffect > 0)
        printf("\nFAILED: %d CARD EFFECT TESTS\n\n", failCardEffect);
    if (failDiscardCard > 0)
        printf("\nFAILED: %d DISCARD TESTS\n", failDiscardCard);  
    if (failNumBuys > 0)
        printf("\nFAILED: %d NUMBER BUYS TESTS\n", failNumBuys);
    if (failDeckHandCountOpponent > 0)
        printf("\nFAILED: %d OPPONENT HAND TESTS\n", failDeckHandCountOpponent);
    if (failDeckHandCountActive > 0)
        printf("\nFAILED: %d YOUR HAND TESTS\n", failDeckHandCountActive);
    printf("\n");
    
    return 0;
}

