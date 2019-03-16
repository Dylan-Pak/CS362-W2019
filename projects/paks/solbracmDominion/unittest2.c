#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
//Unit testing for updateCoinss function
int main(int argc, char** argv)
{
  struct gameState state;
  int bonus = 0;
  int arr[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
  if(argv[1])
  {
    initializeGame(2, arr, atoi(argv[1]), &state);
  }
  else
  {
    initializeGame(2, arr, 4, &state);
  }

  struct gameState stateCopy = state; //Will be making a baseline for a new game state
  //checking is copper card registers correct amount
  state.handCount[0] = 1;
  state.hand[0][0] = copper;
  if(updateCoins(0, &state, bonus) != 0) 
  {
    printf("TEST FAILED: updateCoins failed to complete\n"); //checking if the function completes
    return 0;
  }
  if(state.coins != 1)
  {
    printf("Copper TEST FAILED\n"); //checking if the hand has 1 copper
    return 0;
  }

  state = stateCopy;
  state.handCount[0] = 2;
  state.hand[0][0] = copper;
  state.hand[0][1] = silver;
  if(updateCoins(0, &state, bonus) != 0) 
  {
    printf("TEST FAILED: updateCoins failed to complete\n");
    return 0;
  }
  if(state.coins != 3)
  {
    printf("Silver TEST FAILED\n"); //testing if silver registers as well as testing is multiple cards register
    return 0;
  }
  
  state = stateCopy;
  state.handCount[0] = 3;
  state.hand[0][0] = copper;
  state.hand[0][1] = silver;
  state.hand[0][2] = gold;
  if(updateCoins(0, &state, bonus) != 0) 
  {
    printf("TEST FAILED: updateCoins failed to complete\n");
    return 0;
  }
  if(state.coins != 6) ////testing if gold registers as well as testing is multiple cards register
  {
    printf("gold TEST FAILED\n");
    return 0;
  }
  state = stateCopy;
  state.handCount[0] = 3;
  state.hand[0][0] = copper;
  state.hand[0][1] = silver;
  state.hand[0][2] = gold;
  bonus = 50;
  if(updateCoins(0, &state, bonus) != 0) // Checking if the bonus registers
  {
    printf("TEST FAILED: updateCoins failed to complete\n");
    return 0;
  }
  if(state.coins != 56)
  {
    printf("Bonus TEST FAILED\n");
    return 0;
  }
  printf("updateCoins TEST SUCCESSFULLY COMPLETED\n\n");
  return 0;
}