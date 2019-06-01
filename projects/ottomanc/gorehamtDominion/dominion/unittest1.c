/*
 * unittest1.c
 * Positive test case for Adventurer
 
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

	// ----------- TEST 1: add 2 cards to hand from their own deck--------------
	printf("TEST 1: add two cards to current player hand\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 2;
	xtraCoins = 0;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
	assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
	assert(testG.coins == G.coins + xtraCoins);

	// ----------- TEST 2: no state changes for other players --------------
	printf("TEST 2: check no state changes for other players\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

    //check each player to see if their cards in hand and deck have changed
	newCards = 0;
	for(i=1; i<G.numPlayers; i++){
        printf("player %d hand count = %d, expected = %d\n", i, testG.handCount[i], G.handCount[i]);
        assert(testG.handCount[i] == G.handCount[i]);
        printf("player %d deck count = %d, expected = %d\n", i, testG.deckCount[i], G.deckCount[i]);
        assert(testG.deckCount[i] == G.deckCount[i]);     
    }

	// ----------- TEST 3: no state changes for victory card piles and kingdom card piles --------------

	printf("TEST 3: check no change in victory + kingdom card piles\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

    //check for each victory card pile that there is no change
    printf("estate count = %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate]);
    printf("duchy count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
    printf("province count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);
    assert(testG.supplyCount[estate] == G.supplyCount[estate]);
    assert(testG.supplyCount[duchy] == G.supplyCount[duchy]);
    assert(testG.supplyCount[province] == G.supplyCount[province]);        

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


