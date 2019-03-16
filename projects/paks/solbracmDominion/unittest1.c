#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h> //adding this in so i can use the atoi function. Getting some error messages char var argv into int.

//unit testing for playCard Function
int main(int argc, char** argv)
{
  struct gameState state;
  int arr[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
  if(argv[1])
  {
    initializeGame(2, arr, atoi(argv[1]), &state); //Note atoi is used so we can convert char to int. Only stating this here at unittest1.c
  }
  else
  {
    initializeGame(2, arr, 4, &state);
  }
  int handPos = 0;
  int choice1 = 0;
  int choice2 = 0;
  int choice3 = 0;
  state.phase = 1;
  struct gameState stateCopy = state; //Will be making a baseline for a new game state
  if(playCard(handPos, choice1, choice2, choice3, &state) != -1) //Making sure the phase is right
  {
    printf("Phase State TEST FAILED\n");
    return 0;
  }
  state = stateCopy;
  state.phase = 0;
  stateCopy = state;
  state.numActions = 0;
  if(playCard(handPos, choice1, choice2, choice3, &state) != -1)
  {
    printf("Action TEST FAILED\n"); //checking for at least 1 action available
    return 0;
  }
  state = stateCopy;
  handPos = 365;
  if(playCard(handPos, choice1, choice2, choice3, &state) != -1)
  {
    printf("Hand Position TEST FAILED\n"); //checking valid hand position
    return 0;
  }
  state = stateCopy;
  state.hand[0][0] = gardens;
  if(playCard(handPos, choice1, choice2, choice3, &state) != -1)
  {
    printf("Action Card TEST FAILED\n"); //Testing if we have an action card
    return 0;
  }
  state = stateCopy;
  handPos = 0;
  state.hand[0][0] = village;
  if(playCard(handPos, choice1, choice2, choice3, &state) != 0) //testing if one is able to play the card
  {
    printf("Unable to play Action TEST FAILED\n");
    return 0;
  }
  printf("playCard TEST SUCESSFULLY COMPLETED\n\n");
  return 0;
}