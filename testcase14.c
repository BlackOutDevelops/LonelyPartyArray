// Sean Szumlanski
// COP 3502, Spring 2020

// ==============================
// LonelyPartyArray: testcase14.c
// ==============================
// Tests the functionality of resetLonelyPartyArray().


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "LonelyPartyArray.h"

// Check the struct contents and abort program if anything is out of sorts.
void party_check_nonempty(LonelyPartyArray *party)
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
		if (i == 3 || i == 8 || i == 9 || i == 10)
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

// Check the struct contents and abort program if anything is out of sorts.
void party_check_empty(LonelyPartyArray *party)
{
	int i;

	// Check struct setup.
	assert(party != NULL);
	assert(party->size == 0);
	assert(party->num_fragments == 11);
	assert(party->fragment_length == 10);
	assert(party->num_active_fragments == 0);
	assert(party->fragments != NULL);
	assert(party->fragment_sizes != NULL);

	// Check that all fragments are inactive.
	for (i = 0; i < 11; i++)
		assert(party->fragments[i] == NULL);
}

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

	// Check structure and contents of this non-empty lonely party array.
	party_check_nonempty(party);

	// Hold on to these pointers to make sure they're not lost or reset when
	// resetLonelyPartyArray() is called.
	ptr1 = party->fragments;
	ptr2 = party->fragment_sizes;

	// Now for the main event: Reset the lonely party array.
	resetLonelyPartyArray(party);

	// Check structure and contents of this empty lonely party array.
	party_check_empty(party);

	assert(party->fragments == ptr1);
	assert(party->fragment_sizes == ptr2);

	destroyLonelyPartyArray(party);

	return 0;
}
