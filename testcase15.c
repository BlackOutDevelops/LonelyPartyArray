// Sean Szumlanski
// COP 3502, Spring 2020

// ==============================
// LonelyPartyArray: testcase15.c
// ==============================
// Various NULL pointer checks.


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
	set(party, 34, 1);
	set(party, 83, 2);
	set(party, 92, 5);
	set(party, 95, 8);
	set(party, 98, 6);
	set(party, 109, 3);

	// NULL checks. Note that printIfValid() should not grumble if it receives
	// a NULL party pointer.
	assert(set(NULL, 14, 100) == LPA_FAILURE);
	assert(get(NULL, 14) == LPA_FAILURE);
	assert(delete(NULL, 14) == LPA_FAILURE);
	assert(printIfValid(NULL, 14) == LPA_FAILURE);

	destroyLonelyPartyArray(party);

	return 0;
}
