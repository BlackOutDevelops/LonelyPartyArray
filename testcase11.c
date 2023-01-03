// Sean Szumlanski
// COP 3502, Spring 2020

// ==============================
// LonelyPartyArray: testcase11.c
// ==============================
// A small test of various stat-related functions. This sets up the LPA from
// pg. 3 of the PDF.


#include <stdio.h>
#include <stdlib.h>
#include "LonelyPartyArray.h"

int main(void)
{
	LPA *examScores = createLonelyPartyArray(11, 10);

	// Set a few elements.
	set(examScores, 34, 1);
	set(examScores, 83, 2);
	set(examScores, 92, 5);
	set(examScores, 95, 8);
	set(examScores, 98, 6);
	set(examScores, 109, 3);

	// Print some stats.
	printf("Size: %d\n", getSize(examScores));
	printf("Capacity: %d\n", getCapacity(examScores));
	printf("Allocated Cells: %d\n", getAllocatedCellCount(examScores));
	printf("Traditional Array Size: %llu bytes\n", getArraySizeInBytes(examScores));
	printf("Lonely Party Array Size: %llu bytes\n", getCurrentSizeInBytes(examScores));

	destroyLonelyPartyArray(examScores);

	return 0;
}
