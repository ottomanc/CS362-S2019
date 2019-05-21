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
  printf("you are inside the checkcouncilroom\n");
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

  int r;
 
  r = cardEffect(council_room, choice1, choice2, choice3, post, handpos, &bonus);

  assert (r == 0);

  //assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
}

int main () {

  int n, p, it;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing Council Room Card.\n");

  printf ("RANDOM TESTS.\n");

  //initializeGame(2, k, 1, &G);

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 2000; n++) {
//    for (i = 0; i < sizeof(struct gameState); i++) {
//      ((char*)&G)[i] = floor(Random() * 256);
//    }
    initializeGame(2, k, 1, &G);
    p = floor(Random() * 2);
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    G.whoseTurn = p;
    G.playedCardCount = 0;

    //Draw hand pile
    //for (it = 0; it < G.handCount[G.whoseTurn]; it++){
    //  drawCard(G.whoseTurn, &G);
    //}

    printf("now going to check council room\n");
    checkCouncilRoom(&G);
    printf("you made it out of the checkCouncilRoom\n");
    printf("completed test %d\n", n);

  }

  printf ("ALL TESTS OK\n");

  return 0;
}
