#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//Unit testing the compare function in dominion.c
int main()
{
	int x = 0;
	int y = 1;
	if(compare(&x, &y) != -1) // should output -1. 
		//Please note: going to get an implicit warning because the function is located in dominion.c and is not in the dominion helper file. Dont know if I was suppose to add the the h file
	{
		printf("Less Than TEST FAILED\n");
		return 0;
	}
	x = 1;
	y = 0;
	if(compare(&x, &y) != 1) //should output 1
	{
		printf("Greater Than TEST FAILED\n");
		return 0;
	} 
	x = 1;
	y = 1;
	if(compare(&x, &y) != 0) // should return 0
	{
		printf("Equal to TEST FAILED\n");
		return 0;
	}
	printf("compare TEST SUCCESSFULLY COMPLETED\n\n");
	return 0;
}