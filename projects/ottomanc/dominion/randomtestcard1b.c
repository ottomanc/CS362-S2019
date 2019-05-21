//Random Testing code for Council Room Code
//Colleen Ottomano
//Assignment 4

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

int checkCouncilRoom(struct gameState *post){
  printf("you are inside the checkcouncilroom");
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

  int r;
 
  r = cardEffect(council_room, choice1, choice2, choice3, post, handpos, &bonus);

  assert (r == 0);

  //assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
}

int main () {

  int n, p;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing Council Room Card.\n");

  printf ("RANDOM TESTS.\n");

  initializeGame(2, k, 1, &G);

  printf("now going to check council room");
  checkCouncilRoom(&G);
  printf("you made it out of the checkCouncilRoom");
  //printf("completed test %d", n);

  printf ("ALL TESTS OK\n");

  return 0;
}
