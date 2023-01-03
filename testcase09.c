// Sean Szumlanski
// COP 3502, Spring 2020

// ==============================
// LonelyPartyArray: testcase09.c
// ==============================
// A hodgpodge of calls to set(), delete(), and printIfValid().


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "LonelyPartyArray.h"

int main(void)
{
	int i;
	LPA *party = createLonelyPartyArray(3, 12);

	// Toggle.
	assert(set(party, 14, 28) == LPA_SUCCESS);
	assert(delete(party, 14) == LPA_SUCCESS);
	assert(set(party, 14, 28) == LPA_SUCCESS);
	assert(delete(party, 14) == LPA_SUCCESS);
	assert(set(party, 14, 28) == LPA_SUCCESS);
	assert(delete(party, 14) == LPA_SUCCESS);

	// Check that set() is capable of overwriting an existing value.
	assert(set(party, 14, 28) == LPA_SUCCESS);
	assert(printIfValid(party, 14) == LPA_SUCCESS);
	assert(set(party, 14, 56) == LPA_SUCCESS);
	assert(printIfValid(party, 14) == LPA_SUCCESS);

	// Check that calling set() on the same index twice doesn't increase the
	// size variables twice.
	assert(set(party, 14, 112) == LPA_SUCCESS);
	assert(printIfValid(party, 14) == LPA_SUCCESS);
	assert(set(party, 14, 224) == LPA_SUCCESS);
	assert(printIfValid(party, 14) == LPA_SUCCESS);
	assert(delete(party, 14) == LPA_SUCCESS);
	assert(party->fragments[1] == NULL);
	assert(printIfValid(party, 14) == LPA_FAILURE);
	assert(delete(party, 14) == LPA_FAILURE);
	assert(printIfValid(party, 14) == LPA_FAILURE);

	destroyLonelyPartyArray(party);

	return 0;
}
