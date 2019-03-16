#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//Unit testing the getCost function. Just checking the cost of a few cards instead of the whole set...
int main()
{
        int cardNumber = embargo;
        if(getCost(cardNumber) != 2) //should return 2
        { 
                printf("Embargo TEST FAILED\n");
                return 0;
        }
        cardNumber = silver;
        if(getCost(cardNumber) != 3) //should return 3
        { 
                printf("Silver TEST FAILED\n");
                return 0;
        }
        cardNumber = cutpurse;
        if(getCost(cardNumber) != 4) //should return 4
        {
                printf("Cutpurse TEST FAILED\n");
                return 0;
        }
        printf("getCost TEST SUCCESSFULLY COMPLETED\n\n");
        return 0;
}