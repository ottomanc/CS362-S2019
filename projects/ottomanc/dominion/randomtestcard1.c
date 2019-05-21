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

int checkCouncilRoom(int p, struct gameState *post){
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

  int i, j, n, p, numPlayers, it;
  //int numPlayers = 2;
  //int seed = 1000;
  struct gameState G;

  printf ("Testing Council Room Card.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(3);
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};

  for (n = 0; n < 2000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * numPlayers);
    //G.whoseTurn = p;
    G.playedCardCount = floor(Random() * MAX_HAND);
    //G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);

    //set player decks
    for (i = 0; i < numPlayers; i++)
    {
      G.deckCount[i] = 0;
      for (j = 0; j < 3; j++)
        {
        G.deck[i][j] = estate;
        G.deckCount[i]++;
        }
      for (j = 3; j < 10; j++)
        {
        G.deck[i][j] = copper;
        G.deckCount[i]++;		
        }
    }


    //create player hands
    for (i = 0; i < numPlayers; i++)
    {  
        //initialize hand size to Random
        G.handCount[i] = floor(Random() * MAX_DECK);
        G.discardCount[i] = floor(Random() * MAX_DECK);
    }

    //initialize first player's turn
    G.outpostPlayed = 0;
    G.phase = 0;
    G.numActions = 1;
    G.numBuys = 1;
    G.playedCardCount = 0;
    G.whoseTurn = p;
    G.handCount[G.whoseTurn] = 0;

    //Moved draw cards to here, only drawing at the start of a turn
    for (it = 0; it < G.handCount[p]; it++){
        drawCard(G.whoseTurn, &G);
    }

    updateCoins(G.whoseTurn, &G, 0);


    printf("now going to check council room");
    checkCouncilRoom(p, &G);
    printf("you made it out of the checkCouncilRoom");
    printf("completed test %d", n);
  }

  printf ("ALL TESTS OK\n");

  return 0;
}
