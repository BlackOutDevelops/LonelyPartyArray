// Sean Szumlanski
// COP 3502, Spring 2020

// ==============================
// LonelyPartyArray: testcase03.c
// ==============================
// Basic check to ensure createLonelyPartyArray() is initializing everything
// correctly.


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "LonelyPartyArray.h"

int main(void)
{
	int i;
	LPA *party = createLonelyPartyArray(3, 12);

	assert(party != NULL);
	assert(party->size == 0);
	assert(party->num_fragments == 3);
	assert(party->fragment_length == 12);
	assert(party->num_active_fragments == 0);
	assert(party->fragments != NULL);
	assert(party->fragment_sizes != NULL);

	for (i = 0; i < 3; i++)
		assert(party->fragments[i] == NULL);

	for (i = 0; i < 3; i++)
		assert(party->fragment_sizes[i] == 0);

	destroyLonelyPartyArray(party);

	return 0;
}
