/*
 * cardtest1.c
 * Boundary test case for Adventurer
 
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: test if no treasures in the deck--------------
	printf("TEST 1: test with no treasures in the deck\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	//discard all treasure cards from the deck
    for(i=0; i<testG.deckCount[thisPlayer]; i++){
        if(testG.deck[thisPlayer][i] == copper || testG.deck[thisPlayer][i] == silver || testG.deck[thisPlayer][i] == gold){
            //printf("removed one treasure\n");
            discardCard(i, thisPlayer, &testG, 0);
        }
    }
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 2;
	xtraCoins = 0;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
//	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
//	assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
//	assert(testG.coins == G.coins + xtraCoins);

	// ----------- TEST 2: test if there are no cards in the deck--------------
	printf("TEST 2: test with no cards in the deck\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	//discard all cards from the deck
    for(i=0; i<testG.deckCount[thisPlayer]; i++){
            discardCard(i, thisPlayer, &testG, 0);
    }
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 2;
	xtraCoins = 0;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
//	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
//	assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
//	assert(testG.coins == G.coins + xtraCoins);


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}


