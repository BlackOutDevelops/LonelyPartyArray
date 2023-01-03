// Sean Szumlanski
// COP 3502, Spring 2020

// ==============================
// LonelyPartyArray: testcase05.c
// ==============================
// Tests various aspects of get() functionality. This builds on testcase04.c.


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "LonelyPartyArray.h"

int main(void)
{
	int i;
	LPA *party = createLonelyPartyArray(3, 12);

	// Call set() twice on same index.
	assert(set(party, 14, 100) == LPA_SUCCESS);
	assert(set(party, 14, 100) == LPA_SUCCESS);

	// Call get() twice on same valid index. We'll want to ensure these get()
	// calls don't affect the struct in any way.
	assert(get(party, 14) == 100);
	assert(get(party, 14) == 100);

	// Check whether the struct is set up correctly.
	assert(party != NULL);
	assert(party->size == 1);
	assert(party->num_fragments == 3);
	assert(party->fragment_length == 12);
	assert(party->num_active_fragments == 1);
	assert(party->fragments != NULL);
	assert(party->fragment_sizes != NULL);

	for (i = 0; i < 3; i++)
	{
		if (i == 1)
			assert(party->fragments[i] != NULL);
		else
			assert(party->fragments[i] == NULL);
	}

	for (i = 0; i < 3; i++)
	{
		if (i == 1)
			assert(party->fragment_sizes[i] == 1);
		else
			assert(party->fragment_sizes[i] == 0);
	}

	for (i = 0; i < 12; i++)
	{
		if (i == 2)
			assert(party->fragments[1][i] == 100);
		else
			assert(party->fragments[1][i] == UNUSED);
	}

	// Also check that calling get() on invalid indices produces the correct
	// output and doesn't unsettle the struct's member values. These first two
	// calls should not produce "invalid access" messages because the indices
	// are within bounds (even though they refer to UNUSED cells).
	assert(get(party, 0) == UNUSED);
	assert(get(party, 35) == UNUSED);
	assert(get(party, 36) == LPA_FAILURE);
	assert(get(party, 48) == LPA_FAILURE);
	assert(get(party, 49) == LPA_FAILURE);
	assert(get(party, 59) == LPA_FAILURE);

	// Check again that the struct is still set up correctly.
	assert(party != NULL);
	assert(party->size == 1);
	assert(party->num_fragments == 3);
	assert(party->fragment_length == 12);
	assert(party->num_active_fragments == 1);
	assert(party->fragments != NULL);
	assert(party->fragment_sizes != NULL);

	for (i = 0; i < 3; i++)
	{
		if (i == 1)
			assert(party->fragments[i] != NULL);
		else
			assert(party->fragments[i] == NULL);
	}

	for (i = 0; i < 3; i++)
	{
		if (i == 1)
			assert(party->fragment_sizes[i] == 1);
		else
			assert(party->fragment_sizes[i] == 0);
	}

	for (i = 0; i < 12; i++)
	{
		if (i == 2)
			assert(party->fragments[1][i] == 100);
		else
			assert(party->fragments[1][i] == UNUSED);
	}

	destroyLonelyPartyArray(party);

	return 0;
}
