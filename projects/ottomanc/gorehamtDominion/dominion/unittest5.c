/*
 * unittest5.c
 * Positive test case for Cutpurse
 
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest5: unittest5.c dominion.o rngs.o
 *      gcc -o unittest5 -g unittest4.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "cutpurse"

int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j;
    //int newActions;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG, testG2;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: add 2 coins to the current player--------------
	printf("TEST 1: add 2 coints to the current player\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(cutpurse, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 0;
	xtraCoins = 2;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
	assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
	assert(testG.coins == G.coins + xtraCoins);

	// ----------- TEST 2: other players lose 1 copper from their hand if they have one--------------
	printf("TEST 2: other players lose 1 copper from their hand if they have one (all copper)\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));


	//to make sure that that the coppers are being removed, set the cards all to copper in the deck
	for(i=1; i<testG.numPlayers; i++){
		for(j=0; j<testG.deckCount[i]; j++){
			testG.deck[i][j] = copper;
		}
	}

	//have all other players draw 5 cards
	for(i=1; i<testG.numPlayers; i++){
		for(j=0; j<5; j++){
			drawCard(i, &testG);
		}
	}
	
	// copy the testgame state to a second test case
	memcpy(&testG2, &testG, sizeof(struct gameState));

	cardEffect(cutpurse, choice1, choice2, choice3, &testG, handpos, &bonus);

    //check each player to see if their cards in hand and deck have changed
	//check how many coppers they had to start
	//if 0, then starting hand count should be the same 
	//if > 0 then starting hand count should be one more than ending hand count

	newCards = 0;
	int coppers = 0;
	for(i=1; i<testG2.numPlayers; i++){
		coppers = 0;
		for (j=0; j < testG2.handCount[i]; j++){
			if (testG2.hand[i][j] == copper){
				coppers++;
			}
		}

		if (coppers < 1){
			discarded = 0;
		}
		else
		{
			discarded = 1;
		}
		
		printf("player %d copper count = %d\n", i, coppers);
		printf("player %d hand count = %d, expected = %d\n", i, testG.handCount[i], testG2.handCount[i] - discarded);
        assert(testG.handCount[i] == testG2.handCount[i] - discarded);
        printf("player %d deck count = %d, expected = %d\n", i, testG.deckCount[i], testG2.deckCount[i]);
        assert(testG.deckCount[i] == testG2.deckCount[i]);     
    }

	// ----------- TEST 3: other players lose 1 copper from their hand if they have one--------------
	printf("TEST 3: other players lose 1 copper from their hand if they have one (random copper)\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	//have all other players draw 5 cards
	for(i=1; i<G.numPlayers; i++){
		for(j=0; j<5; j++){
			drawCard(i, &testG);
		}
	}

	cardEffect(cutpurse, choice1, choice2, choice3, &testG, handpos, &bonus);

    //check each player to see if their cards in hand and deck have changed
	//check how many coppers they had to start
	//if 0, then starting hand count should be the same 
	//if > 0 then starting hand count should be one more than ending hand count

	newCards = 0;
	coppers = 0;
	for(i=1; i<G.numPlayers; i++){
		coppers = 0;
		for (j=0; j < G.handCount[i]; j++){
			if (G.hand[i][j] == copper){
				coppers++;
			}
		}

		if (coppers < 1){
			discarded = 0;
		}
		else
		{
			discarded = 1;
		}
		
		printf("player %d copper count = %d\n", i, coppers);
		printf("player %d hand count = %d, expected = %d\n", i, testG.handCount[i], G.handCount[i] - discarded);
        assert(testG.handCount[i] == G.handCount[i] - discarded);
        printf("player %d deck count = %d, expected = %d\n", i, testG.deckCount[i], G.deckCount[i]);
        assert(testG.deckCount[i] == G.deckCount[i]);     
    }


	// ----------- TEST 4: no state changes for victory card piles and kingdom card piles --------------

	printf("TEST 4: check no change in victory + kingdom card piles\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(cutpurse, choice1, choice2, choice3, &testG, handpos, &bonus);

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


