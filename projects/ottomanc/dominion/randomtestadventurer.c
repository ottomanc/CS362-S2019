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

int checkAdventurer(int p, struct gameState *post){
  //printf("you are inside the checkcouncilroom\n");
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

  int r, i, currentPlayer;
  currentPlayer = p;
 
  r = cardEffect(adventurer, choice1, choice2, choice3, post, handpos, &bonus);

  assert (r == 0);

  //replicate what the function call should do to see if the pre and post states then match
  int cardDrawn;
  int temphand[MAX_HAND];
  int z = 0;// this is the counter for the temp hand
  int drawntreasure = 0;
  
  while(drawntreasure<2){
    if (pre.deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
      shuffle(currentPlayer, &pre);
    }
    drawCard(currentPlayer, &pre);
    cardDrawn = pre.hand[currentPlayer][pre.handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
      drawntreasure++;
    else{
      temphand[z]=cardDrawn;
      pre.handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
      z++;
    }
  }
  while(z-1>=0){
    pre.discard[currentPlayer][pre.discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
    z=z-1;
  }

  //check and see if they match
  assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
}


int main () {

  int n, p;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing Adventurer Card.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 2000; n++) {
    //initialize the game to set up all the variables
    initializeGame(2, k, 1, &G);
    //choose the player randomly from the 2 available
    p = floor(Random() * 2);
    //randomly assign the deckCount to a value <500
    G.deckCount[p] = floor(Random() * MAX_DECK);
    //randomly assign the discardCount to a value <500
    G.discardCount[p] = floor(Random() * MAX_DECK);
    //randomly assign the handCount to a value <500
    G.handCount[p] = floor(Random() * MAX_HAND);
    //set the current player to the randomly choosen one
    G.whoseTurn = p;
    //set the playedCardCount to 0
    G.playedCardCount = 0;
    //randomly assign the numBuys
    G.numBuys = floor(Random() * MAX_DECK);

    //printf("now going to check council room\n");
    checkAdventurer(p, &G);
    //printf("you made it out of the checkCouncilRoom\n");
    //printf("completed test %d\n", n);

  }

  printf ("ALL TESTS OK\n");

  return 0;
}
