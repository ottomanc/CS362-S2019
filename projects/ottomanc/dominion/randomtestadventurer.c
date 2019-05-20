//Random Testing code for Adventurer Code
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

int checkAdventurer(int thisPlayer, struct gameState *post) {
//  int newCards = 0;
//  int discarded = 1;
  //int xtraCoins = 0;
//  int shuffledCards = 0;

  //int i;
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

  struct gameState pre;

  int r;

	// copy the game state to a test case
	memcpy(&pre, post, sizeof(struct gameState));

  //run the cardEffect function with the random gameState setup
	r = cardEffect(adventurer, choice1, choice2, choice3, post, handpos, &bonus);

  //Check the results with assert statements
	//newCards = 2;
	//printf("hand count = %d, expected = %d\n", post->handCount[thisPlayer], pre.handCount[thisPlayer] + newCards - discarded);
  //printf("deck count = %d, expected = %d\n", post->deckCount[thisPlayer], pre.deckCount[thisPlayer] - newCards + shuffledCards);
  //check if the function happened
  assert (r == 0);
  assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
  //Check the hand count
	//assert(post->handCount[thisPlayer] == pre.handCount[thisPlayer] + newCards - discarded);
  //Check the deck count
	//assert(post->deckCount[thisPlayer] == pre.deckCount[thisPlayer] - newCards + shuffledCards);
  //return 0;
}

int main () {

  int i, n, p;
//r, p, deckCount, discardCount, handCount;

//  int k[10] = {adventurer, council_room, feast, gardens, mine,
//	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing Adventurer Card.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 2000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    checkAdventurer(p, &G);
    printf("completed test %d", n);
  }

  printf ("ALL TESTS OK\n");

  return 0;
}
