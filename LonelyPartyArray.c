// Joshua Frazer jo227789
// COP 3502, Spring 2020
// Using Atom & Linux Bash Shell on Windows 10.
#include <stdio.h>
#include <stdlib.h>
#include "LonelyPartyArray.h"

// Helper functions I created to reduce repetition

int checkRange();

int findIndex(LonelyPartyArray *party, int *fragment, int index);

// Function to check the range of the given LPA
int checkRange(LonelyPartyArray *party)
{
    int range;

    // Calculation that gives me the maximum bound of the LPA
    range = party->num_fragments * party->fragment_length - 1;

    return range;
}

// Function to find the index desired for the LPA
int findIndex(LonelyPartyArray *party, int *fragment, int index)
{
    int exit = 0;
    *fragment = 0;

    // if condition to check valid range to calculate the fragment and index values
    if (index >= 0)
    {
        while (exit != -1)
        {
            if (index < party->fragment_length)
                exit = -1;
            else
            {
                index -= party->fragment_length;
                *fragment += 1;
            }
        }
        return index;
    }
    // else condition to check invalid range to calculate the fragment and index values
    else
    {
        while (exit != -1)
        {
            if (index > (party->fragment_length * -1))
                exit = -1;
            else
            {
                index += party->fragment_length;
                *fragment -= 1;
            }
        }
        return index;
    }
}

// Functions required for assignment

LonelyPartyArray *createLonelyPartyArray(int num_fragments, int fragment_length)
{
    int i;

    // Checks for values of parameters being less than or equal to zero
    if (num_fragments <= 0 || fragment_length <= 0)
        return NULL;

    LonelyPartyArray *array = malloc(sizeof(LonelyPartyArray));
    // Validates dynamic allocation
    if (array == NULL)
    {
        free(array);
        return(NULL);
    }

    // Initializing struct
    array->num_fragments = num_fragments;
    array->fragment_length = fragment_length;
    array->num_active_fragments = 0;
    array->fragments = malloc(sizeof(int *) * num_fragments);
    // Validates dynamic allocation
    if (array->fragments == NULL)
    {
        free(array->fragments);
        return(NULL);
    }

    array->fragment_sizes = malloc(sizeof(int) * num_fragments);
    // Validates dynamic allocation
    if (array->fragment_sizes == NULL)
    {
        free(array->fragment_sizes);
        return(NULL);
    }

    // Creates fragments array of pointers to num_fragments
    for (i = 0; i < num_fragments; i++)
    {
        array->fragments[i] = NULL;
    }

    // Creates fragment_sizes array
    for (i = 0; i < num_fragments; i++)
    {
        array->fragment_sizes[i] = 0;
    }
    array->size = getSize(array);
    printf("-> A new LonelyPartyArray has emerged from the void. "
           "(capacity: %d, fragments: %d)\n", getCapacity(array), array->num_fragments);
    return array;
}

LonelyPartyArray *destroyLonelyPartyArray(LonelyPartyArray *party)
{
    int i;
    // if statement to validate if party is NULL
    if (party == NULL)
        return NULL;
    // for loop to free dynamically allocated cells within fragments array
    for (i = 0; i < party->num_fragments; i++)
    {
        if (party->fragment_sizes[i] > 0)
        {
            free(party->fragments[i]);
        }
    }
    // Frees the rest of the dynamically allocated structure variables
    free(party->fragments);
    free(party->fragment_sizes);
    free(party);

    printf("-> The LonelyPartyArray has returned to the void.\n");
    return NULL;
}

int set(LonelyPartyArray *party, int index, int key)
{
    int i,
        indexOrg,
        indiceHi,
        indiceLo,
        numFragments,
        *fragment = &numFragments;

    // Stores the original index before future calculations to use in future range comparison
    indexOrg = index;
    // if statement to validate if party is NULL
    if (party == NULL)
    {
        printf("-> Bloop! NULL pointer detected in set().\n");
        return LPA_FAILURE;
    }

    // Calls findIndex to store indice for specific fragment
    index = findIndex(party, fragment, index);

    // if statement to check if the index given is in bounds of LPA
    if (indexOrg < 0 || indexOrg > checkRange(party))
    {
        printf("-> Bloop! Invalid access in set(). (index: %d, "
               "fragment: %d, offset: %d)\n", indexOrg, numFragments, index);
        return LPA_FAILURE;
    }
    // else-if statement to validate if the fragment is NULL or not
    else if (party->fragments[numFragments] == NULL)
    {
        // Dynamically allocates memory for specific fragment
        party->fragments[numFragments] = malloc(sizeof(int) * party->fragment_length);
        // Validates dynamic allocation
        if (party->fragments[numFragments] == NULL)
        {
            free(party->fragments[numFragments]);
            return LPA_FAILURE;
        }
        // for loop to correctly set up fragment[numFragments] array
        for (i = 0; i < party->fragment_length; i++)
        {
            if (i == index)
                party->fragments[numFragments][i] = key;
            else
                party->fragments[numFragments][i] = UNUSED;
        }
        // Increments the value of number of active fragments, size of LPA, and size of fragment in LPA
        party->num_active_fragments++;
        party->size++;
        party->fragment_sizes[numFragments]++;
        // Calculates the lowest indice of fragment and the highest
        indiceLo = numFragments * party->fragment_length;
        indiceHi = indiceLo + party->fragment_length - 1;
        printf("-> Spawned fragment %d. (capacity: %d, "
               "indices: %d..%d)\n", numFragments, party->fragment_length, indiceLo, indiceHi);
    }
    // else-if statement to validate if the specific fragment and indice has been allocated but is UNUSED
    else if (party->fragments[numFragments][index] == UNUSED)
    {
        // Sets the UNUSED cell to the key and then increments the size of the LPA and size of fragment in LPA
        party->fragments[numFragments][index] = key;
        party->size++;
        party->fragment_sizes[numFragments]++;
    }
    // else for all other conditions
    else
    {
      // Replaces cell with the given key
      party->fragments[numFragments][index] = key;
    }

    return LPA_SUCCESS;
}

int get(LonelyPartyArray *party, int index)
{
    int numFragments,
        *fragment = &numFragments,
        indexOrg;

    // Stores the original index before future calculations to use in future range comparison
    indexOrg = index;
    // if statement to validate if party is NULL
    if (party == NULL)
    {
        printf("-> Bloop! NULL pointer detected in get().\n");
        return LPA_FAILURE;
    }

    // Calls findIndex to store indice for specific fragment
    index = findIndex(party, fragment, index);

    // if statement to check if the index given is in bounds of LPA
    if (indexOrg < 0 || indexOrg > checkRange(party))
    {
        printf("-> Bloop! Invalid access in get(). (index: %d, "
               "fragment: %d, offset: %d)\n", indexOrg, numFragments, index);
        return LPA_FAILURE;
    }
    // else-if statement to check if specific fragment is NULL
    else if (party->fragments[numFragments] == NULL)
    {
        return UNUSED;
    }
    // else-if statement to check if specific fragment is not NULL
    else if (party->fragments[numFragments] != NULL)
    {
        // if statement to validate if the specific indice is not UNUSED
        if (party->fragments[numFragments][index] != UNUSED)
            return party->fragments[numFragments][index];
        else
            return UNUSED;
    }
}

int delete(LonelyPartyArray *party, int index)
{
    int i,
        numFragments,
        *fragment = &numFragments,
        indexOrg,
        indiceLo,
        indiceHi;

    // Stores the original index before future calculations to use in future range comparison
    indexOrg = index;
    // if statement to validate if party is NULL
    if (party == NULL)
    {
        printf("-> Bloop! NULL pointer detected in delete().\n");
        return LPA_FAILURE;
    }

    // Calls findIndex to store indice for specific fragment
    index = findIndex(party, fragment, index);

    // if statement to check if the index given is in bounds of LPA
    if (indexOrg < 0 || indexOrg > checkRange(party))
    {
        printf("-> Bloop! Invalid access in delete(). (index: %d, "
               "fragment: %d, offset: %d)\n", indexOrg, numFragments, index);
        return LPA_FAILURE;
    }
    // else-if statement to validate if the specific fragment is NULL
    else if (party->fragments[numFragments] == NULL)
    {
        return LPA_FAILURE;
    }
    // else-if statement to validate if the specific fragment is not NULL
    else if (party->fragments[numFragments] != NULL)
    {
        // if statement to validate if the specific indice is not UNUSED
        if (party->fragments[numFragments][index] != UNUSED)
        {
            // Sets the specific indice to UNUSED
            party->fragments[numFragments][index] = UNUSED;
            // Decrements the size of the LPA and the size of the fragment
            party->size--;
            party->fragment_sizes[numFragments]--;
            // if statement to validate if there aren't any more elements in specific fragment
            if (party->fragment_sizes[numFragments] == 0)
            {
                // Frees dynamically allocated fragment
                free(party->fragments[numFragments]);
                // Sets specified fragment to NULL
                party->fragments[numFragments] = NULL;
                // Decrements number of active fragments
                party->num_active_fragments--;
                // Calculates the lowest indice of fragment and the highest
                indiceLo = numFragments * party->fragment_length;
                indiceHi = indiceLo + party->fragment_length - 1;
                printf("-> Deallocated fragment %d. (capacity: %d, "
                       "indices: %d..%d)\n", numFragments, party->fragment_length, indiceLo, indiceHi);
            }
            return LPA_SUCCESS;
        }
        else
        {
            return LPA_FAILURE;
        }
    }
}

int containsKey(LonelyPartyArray *party, int key)
{
    int i,
        j;

    // if statement to validate if party is NULL
    if (party == NULL)
    {
        return 0;
    }
    // for loop to run though array and find key
    for (i = 0; i < party->num_fragments; i++)
    {
        if (party->fragments[i] != NULL)
        {
            for (j = 0; j < party->fragment_length; j++)
            {
                if (party->fragments[i][j] == key)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int isSet(LonelyPartyArray *party, int index)
{
    int i,
        numFragments,
        *fragment = &numFragments,
        indexOrg;

    // Stores the original index before future calculations to use in future range comparison
    indexOrg = index;
    // if statement to validate if party is NULL
    if (party == NULL)
    {
        return 0;
    }

    // Calls findIndex to store indice for specific fragment
    index = findIndex(party, fragment, index);

    // if statement to check if the index given is in bounds of LPA
    if (indexOrg < 0 || indexOrg > checkRange(party))
        return 0;
    // else-if statement to check if specific fragment is NULL
    else if (party->fragments[numFragments] == NULL)
    {
        return 0;
    }
    // else-if statement to check if specific indice is not UNUSED and specific fragment is not NULL
    else if (party->fragments[numFragments][index] != UNUSED && party->fragments[numFragments] != NULL)
        return 1;
    else
        return 0;
}

int printIfValid(LonelyPartyArray *party, int index)
{
    int i,
        numFragments,
        *fragment = &numFragments,
        indexOrg;

    // Stores the original index before future calculations to use in future range comparison
    indexOrg = index;
    // if statement to validate if party is NULL
    if (party == NULL)
    {
        return LPA_FAILURE;
    }

    // Calls findIndex to store indice for specific fragment
    index = findIndex(party, fragment, index);

    // if statement to check if the index given is in bounds of LPA
    if (indexOrg < 0 || indexOrg > checkRange(party))
        return LPA_FAILURE;
    // else-if statement to check if fragment is NULL
    else if (party->fragments[numFragments] == NULL)
    {
        return LPA_FAILURE;
    }
    // else-if statement to check if specific indice is not UNUSED and specific fragment is not NULL
    else if (party->fragments[numFragments][index] != UNUSED && party->fragments[numFragments] != NULL)
    {
        printf("%d\n", party->fragments[numFragments][index]);
        return LPA_SUCCESS;
    }
    else
        return LPA_FAILURE;
}

LonelyPartyArray *resetLonelyPartyArray(LonelyPartyArray *party)
{
    int i,
        j;

    // if statement to validate if party is NULL
    if (party == NULL)
    {
        printf("-> Bloop! NULL pointer detected in resetLonelyPartyArray().\n");
        return party;
    }
    // else statement to reset the LPA if party is not NULL
    else
    {
        // for loop to run through LPA and reset it to its origin
        for (i = 0; i < party->num_fragments; i++)
        {
            free(party->fragments[i]);
            party->fragments[i] = NULL;
            party->fragment_sizes[i] = 0;
        }
        // Resets number of active fragments and size
        party->num_active_fragments = 0;
        party->size = 0;
        printf("-> The LonelyPartyArray has returned to its nascent state. "
               "(capacity: %d, fragments: %d)\n", getCapacity(party), party->num_fragments);
        return party;
    }
}

int getSize(LonelyPartyArray *party)
{
    int i,
        totalSize = 0;

    // if statement to validate if party is NULL
    if (party == NULL)
        return -1;
    // for loop to count up the total size of LPA
    for (i = 0; i < party->num_fragments; i++)
    {
        totalSize += party->fragment_sizes[i];
    }

    return totalSize;
}

int getCapacity(LonelyPartyArray *party)
{
    int capacity;

    // if statement to validate if party is NULL
    if (party == NULL)
        return -1;
    // Calculates the capacity of the LPA
    capacity = party->num_fragments * party->fragment_length;
    return capacity;
}

int getAllocatedCellCount(LonelyPartyArray *party)
{
    int i,
        allocatedCellCount = 0;

    // if statement to validate if party is NULL
    if (party == NULL)
        return -1;
    // for loop to calculate how many cells have been allocated in the LPA
    for (i = 0; i < party->num_fragments; i++)
    {
        if (party->fragments[i] != NULL)
        {
            allocatedCellCount += party->fragment_length;
        }
    }

    return allocatedCellCount;
}

long long unsigned int getArraySizeInBytes(LonelyPartyArray *party)
{
    long long unsigned int totalBytes;

    // if statement to validate if party is NULL
    if (party == NULL)
        return 0;
    // Calculates the total memory of a standard array
    totalBytes = getCapacity(party) * (long long unsigned int)sizeof(int);
    return totalBytes;
}

long long unsigned int getCurrentSizeInBytes(LonelyPartyArray *party)
{
    long long unsigned int totalBytes,
                           lpaPointerBytes,
                           lpaBytes,
                           fragBytes,
                           fragSizesBytes,
                           aFragBytes;

    // if statement to validate if party is NULL
    if (party == NULL)
       return 0;
    // Calculates all the allocated space individually
    lpaPointerBytes = (long long unsigned int)sizeof(int *);
    lpaBytes = ((long long unsigned int)sizeof(int *) * 2)
               + ((long long unsigned int)sizeof(int) * 4);
    fragBytes = (long long unsigned int)sizeof(int *) * party->num_fragments;
    fragSizesBytes = (long long unsigned int)sizeof(int) * party->num_fragments;
    aFragBytes = (long long unsigned int)sizeof(int) * party->num_active_fragments
                 * party->fragment_length;
    // Totals up the allocated space
    totalBytes = lpaPointerBytes + lpaBytes + fragBytes + fragSizesBytes + aFragBytes;

    return totalBytes;
}

// BONUS FUNCTION

LonelyPartyArray *cloneLonelyPartyArray(LonelyPartyArray *party)
{
    int i,
        j;

    struct LonelyPartyArray *clone;
    // if statement to validate if party is NULL
    if (party == NULL)
       return NULL;

    clone = malloc(sizeof(LonelyPartyArray));
    // Validates dynamic allocation
    if (clone == NULL)
    {
        free(clone);
        return(NULL);
    }

    // Initializing struct
    clone->num_fragments = party->num_fragments;
    clone->fragment_length = party->fragment_length;
    clone->num_active_fragments = party->num_active_fragments;
    clone->fragments = malloc(sizeof(int *) * party->num_fragments);
    // Validates dynamic allocation
    if (clone->fragments == NULL)
    {
        free(clone->fragments);
        return(NULL);
    }

    clone->fragment_sizes = malloc(sizeof(int) * party->num_fragments);
    // Validates dynamic allocation
    if (clone->fragment_sizes == NULL)
    {
        free(clone->fragment_sizes);
        return(NULL);
    }

    // Creates fragments array of pointers to num_fragments
    for (i = 0; i < party->num_fragments; i++)
    {
        if (party->fragments[i] != NULL)
        {
            clone->fragments[i] = malloc(sizeof(int) * party->fragment_length);
            // Validates dynamic allocation
            if (clone->fragments[i]== NULL)
            {
                free(clone->fragments[i]);
                return(NULL);
            }

            for (j = 0; j < party->fragment_length; j++)
            {
                clone->fragments[i][j] = party->fragments[i][j];
            }
        }
        else
            clone->fragments[i] = NULL;
    }

    // Creates fragment_sizes array
    for (i = 0; i < party->num_fragments; i++)
    {
        clone->fragment_sizes[i] = party->fragment_sizes[i];
    }
    clone->size = party->size;

    printf("-> Successfully cloned the LonelyPartyArray. "
           "(capacity: %d, fragments: %d)\n", getCapacity(clone), clone->num_fragments);

    return clone;
}

double difficultyRating(void)
{
    return 2.5;
}

double hoursSpent(void)
{
    return 13.0;
}
