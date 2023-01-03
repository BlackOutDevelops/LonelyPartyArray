// Sean Szumlanski
// COP 3502, Spring 2020

// ==============================
// LonelyPartyArray: testcase07.c
// ==============================
// Tests the ability of delete() to cause a fragment deallocation. This builds
// on testcase06.c.


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "LonelyPartyArray.h"

int main(void)
{
	int i;
	LPA *party = createLonelyPartyArray(3, 12);

	// set() a few elements.
	assert(set(party, 14, 200) == LPA_SUCCESS);
	assert(set(party, 14, 100) == LPA_SUCCESS);
	assert(set(party, 15, 100) == LPA_SUCCESS);
	assert(set(party, 26, 100) == LPA_SUCCESS);
	assert(set(party, 27, 100) == LPA_SUCCESS);

	// Check that the struct is set up correctly to begin with.
	assert(party != NULL);
	assert(party->size == 4);
	assert(party->num_fragments == 3);
	assert(party->fragment_length == 12);
	assert(party->num_active_fragments == 2);
	assert(party->fragments != NULL);
	assert(party->fragment_sizes != NULL);

	for (i = 0; i < 3; i++)
	{
		// Fragment 0 should be NULL. The other two should be non-NULL.
		if (i == 0)
			assert(party->fragments[i] == NULL);
		else
			assert(party->fragments[i] != NULL);
	}

	for (i = 0; i < 3; i++)
	{
		// Fragment 0 has no elements. Fragments 1 and 2 have 2 elements.
		if (i == 0)
			assert(party->fragment_sizes[i] == 0);
		else
			assert(party->fragment_sizes[i] == 2);
	}

	// Check fragments 1 and 2.
	for (i = 0; i < 12; i++)
	{
		if (i == 2)
			assert(party->fragments[1][i] == 100);
		else if (i == 3)
			assert(party->fragments[1][i] == 100);
		else
			assert(party->fragments[1][i] == UNUSED);

		if (i == 2)
			assert(party->fragments[2][i] == 100);
		else if (i == 3)
			assert(party->fragments[2][i] == 100);
		else
			assert(party->fragments[2][i] == UNUSED);
	}

	// These should not cause fragment deallocation.
	assert(delete(party, 26) == LPA_SUCCESS);
	assert(delete(party, 26) == LPA_FAILURE);
	assert(delete(party, 26) == LPA_FAILURE);
	assert(delete(party, 28) == LPA_FAILURE);
	assert(delete(party, 28) == LPA_FAILURE);
	assert(delete(party, 28) == LPA_FAILURE);

	// These should trigger fragment deallocation.
	assert(delete(party, 15) == LPA_SUCCESS);
	assert(delete(party, 14) == LPA_SUCCESS);

	// Check that the struct is still set up correctly.
	assert(party != NULL);
	assert(party->size == 1);
	assert(party->num_fragments == 3);
	assert(party->fragment_length == 12);
	assert(party->num_active_fragments == 1);
	assert(party->fragments != NULL);
	assert(party->fragment_sizes != NULL);

	for (i = 0; i < 3; i++)
	{
		// Fragment 2 should still be active.
		if (i == 2)
			assert(party->fragments[i] != NULL);
		else
			assert(party->fragments[i] == NULL);
	}

	for (i = 0; i < 3; i++)
	{
		// Fragment 2 should still have a single active element.
		if (i == 2)
			assert(party->fragment_sizes[i] == 1);
		else
			assert(party->fragment_sizes[i] == 0);
	}

	for (i = 0; i < 12; i++)
	{
		// Fragment 2's active element (100) should be at index 3.
		if (i == 3)
			assert(party->fragments[2][i] == 100);
		else
			assert(party->fragments[2][i] == UNUSED);
	}

	destroyLonelyPartyArray(party);

	return 0;
}
