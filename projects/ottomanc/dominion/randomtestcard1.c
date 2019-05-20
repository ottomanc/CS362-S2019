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

int checkCouncilRoom(int thisPlayer, struct gameState *post) {

  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

  struct gameState pre;

  int r;

  memcpy(&pre, post, sizeof(struct gameState));

  //run the cardEffect function with the random gameState setup
  r = cardEffect(adventurer, choice1, choice2, choice3, post, handpos, &bonus);

  assert (r == 0);
  assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);

}

int main () {

  int i, n, p;

  struct gameState G;

  printf ("Testing Council Room Card.\n");

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
    checkCouncilRoom(p, &G);
    printf("completed test %d", n);
  }

  printf ("ALL TESTS OK\n");

  return 0;
}
