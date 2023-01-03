// Sean Szumlanski
// COP 3502, Spring 2020

// =============================
// LonelyPartyArray: CloneTest.c
// =============================
// Tests the functionality of cloneLonelyPartyArray(). This is a bonus test
// case.


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "LonelyPartyArray.h"

// Check the struct contents and abort program if anything is out of sorts.
void party_check(LonelyPartyArray *party)
{
	int i;

	// Check struct setup.
	assert(party != NULL);
	assert(party->size == 6);
	assert(party->num_fragments == 11);
	assert(party->fragment_length == 10);
	assert(party->num_active_fragments == 4);
	assert(party->fragments != NULL);
	assert(party->fragment_sizes != NULL);

	// Check fragments. Only fragments 3, 8, 9, and 10 should be active.
	for (i = 0; i < 11; i++)
	{
		if (i == 3)
			assert(party->fragments[i] != NULL);
		else if (i == 8)
			assert(party->fragments[i] != NULL);
		else if (i == 9)
			assert(party->fragments[i] != NULL);
		else if (i == 10)
			assert(party->fragments[i] != NULL);
		else
			assert(party->fragments[i] == NULL);
	}
	// Check contents of fragment 3.
	for (i = 0; i < 10; i++)
	{
		if (i == 4)
			assert(party->fragments[3][i] == 1);
		else
			assert(party->fragments[3][i] == UNUSED);
	}
	// Check contents of fragment 8.
	for (i = 0; i < 10; i++)
	{
		if (i == 3)
			assert(party->fragments[8][i] == 2);
		else
			assert(party->fragments[8][i] == UNUSED);
	}
	// Check contents of fragment 9.
	for (i = 0; i < 10; i++)
	{
		if (i == 2)
			assert(party->fragments[9][i] == 5);
		else if (i == 5)
			assert(party->fragments[9][i] == 8);
		else if (i == 8)
			assert(party->fragments[9][i] == 6);
		else
			assert(party->fragments[9][i] == UNUSED);
	}
	// Check contents of fragment 10.
	for (i = 0; i < 10; i++)
	{
		if (i == 9)
			assert(party->fragments[10][i] == 3);
		else
			assert(party->fragments[10][i] == UNUSED);
	}
}

int main(void)
{
	LPA *party = createLonelyPartyArray(11, 10);
	LPA *clone;

	// Set a few elements.
	set(party, 34, 1);
	set(party, 83, 2);
	set(party, 92, 5);
	set(party, 95, 8);
	set(party, 98, 6);
	set(party, 109, 3);

	// Check structure and contents of the original lonely party array.
	party_check(party);

	// Clone the party array.
	clone = cloneLonelyPartyArray(party);

	// Check structure and contents of the clone.
	party_check(clone);

	// Check that the structure and contents of the original have survived.
	party_check(party);

	// Ensure that clone is not simply referring to the original lonely party
	// array or any of its constituent members.
	assert(clone != party);
	assert(clone->fragments != party->fragments);
	assert(clone->fragment_sizes != party->fragment_sizes);
	assert(clone->fragments[3] != party->fragments[3]);
	assert(clone->fragments[8] != party->fragments[8]);
	assert(clone->fragments[9] != party->fragments[9]);
	assert(clone->fragments[10] != party->fragments[10]);

	destroyLonelyPartyArray(party);
	destroyLonelyPartyArray(clone);

	return 0;
}
