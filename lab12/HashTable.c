// HashTable.c ... implementation of HashTable ADT
// Written by John Shepherd, May 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "HashTable.h"
#include "List.h"

// Types and functions local to HashTable ADT

typedef struct HashTabRep {
	List *lists;  // either use this
	int   nslots; // # elements in array
	int   nitems; // # items stored in HashTable
} HashTabRep;

// convert key into index (from Sedgewick)
unsigned int hash(Key k, int tableSize)
{
	unsigned int h = 0;
	//int tSizeMinus1 = (tableSize-1);
	int a = 31415, b = 27183;
	for (k = k; *k != '\0'; k++) {
		a = a*b ;
		h = (a*h + *k) % tableSize;
	}
	return (h % tableSize);
}


// Interface functions for HashTable ADT

// create an empty HashTable
HashTable newHashTable(int N)
{
		HashTabRep *new = malloc(sizeof(HashTabRep));
		assert(new != NULL);
		new->lists = malloc(N*sizeof(List));
		assert(new->lists != NULL);
		int i;
		for (i = 0; i < N; i++)
			new->lists[i] = newList();
		new->nslots = N; new->nitems = 0;
		return new;
}

// free memory associated with HashTable
void dropHashTable(HashTable ht)
{
	assert(ht != NULL);
	int i;
    for (i = 0; i < ht->nslots; i++) 
		dropList(ht->lists[i]);
	free(ht);
}

// display HashTable stats
void HashTableStats(HashTable ht)
{
    int countSize = (int)((float)0.05627462*ht->nslots);
	assert(ht != NULL);
	printf("Hash Table Stats:\n");
	printf("Number of slots = %d\n",ht->nslots);   
	printf("Number of items = %d\n",ht->nitems);   
	printf("Chains\n");
	printf("%7s %7s\n","Length","Freq");
	int count[countSize];
	//go through the lists
	int i;
	for(i = 0;i<countSize;i++) {
	   count[i] = 0;
	}

	for(i = 0;i<ht->nslots;i++) {
	    count[ListLength(ht->lists[i])] ++;
	}
	for(i = 0;i<countSize;i++) {
	    printf("%2d %4d\n", i,count[i]);
	}
	
}

// insert a new value into a HashTable
void HashTableInsert(HashTable ht, Item it)
{
	assert(ht != NULL);
	int i = hash(key(it), ht->nslots);
	ListInsert(ht->lists[i], it);
	ht->nitems++;
}

// delete a value from a HashTable
void HashTableDelete(HashTable ht, Key k)
{
	assert(ht != NULL);
	int h = hash(k, ht->nslots);
	ListDelete(ht->lists[h], k);
}

// get Item from HashTable using Key
Item *HashTableSearch(HashTable ht, Key k)
{
	assert(ht != NULL);
	int i = hash(k, ht->nslots);
	return ListSearch(ht->lists[i], k);
}

