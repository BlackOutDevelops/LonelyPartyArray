// Sean Szumlanski
// COP 3502, Spring 2020

// ==============================
// LonelyPartyArray: testcase16.c
// ==============================
// Various negative index checks.


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "LonelyPartyArray.h"

int main(void)
{
	LPA *party = createLonelyPartyArray(11, 10);

	int **ptr1;
	int *ptr2;

	// Set a few elements.
	printf("\n");
	set(party, 34, 1);
	set(party, 83, 2);
	set(party, 92, 5);
	set(party, 95, 8);
	set(party, 98, 6);
	set(party, 109, 3);

	// Negative index checks. Note that printIfValid() should not grumble if it
	// receives a negative index.
	printf("\n");
	assert(set(party, -1, 100) == LPA_FAILURE);
	assert(get(party, -1) == LPA_FAILURE);
	assert(delete(party, -1) == LPA_FAILURE);
	assert(printIfValid(party, -1) == LPA_FAILURE);

	// Negative index checks. Again, printIfValid() should not grumble if it
	// receives a negative index.
	printf("\n");
	assert(set(party, -9, 100) == LPA_FAILURE);
	assert(get(party, -9) == LPA_FAILURE);
	assert(delete(party, -9) == LPA_FAILURE);
	assert(printIfValid(party, -9) == LPA_FAILURE);

	// Negative index checks. Again, printIfValid() should not grumble if it
	// receives a negative index.
	printf("\n");
	assert(set(party, -10, 100) == LPA_FAILURE);
	assert(get(party, -10) == LPA_FAILURE);
	assert(delete(party, -10) == LPA_FAILURE);
	assert(printIfValid(party, -10) == LPA_FAILURE);

	// Negative index checks. Again, printIfValid() should not grumble if it
	// receives a negative index.
	printf("\n");
	assert(set(party, -11, 100) == LPA_FAILURE);
	assert(get(party, -11) == LPA_FAILURE);
	assert(delete(party, -11) == LPA_FAILURE);
	assert(printIfValid(party, -11) == LPA_FAILURE);

	// Negative index checks. Again, printIfValid() should not grumble if it
	// receives a negative index.
	printf("\n");
	assert(set(party, -321, 100) == LPA_FAILURE);
	assert(get(party, -321) == LPA_FAILURE);
	assert(delete(party, -321) == LPA_FAILURE);
	assert(printIfValid(party, -321) == LPA_FAILURE);

	// Clean up after yourself.
	printf("\n");
	destroyLonelyPartyArray(party);

	return 0;
}
