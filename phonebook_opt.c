#include <stdlib.h>
#include <string.h>

#include "phonebook_opt.h"


static entry *hashTable[MAX_HASH_TABLE_SIZE];
//static entry *freePool[MAX_HASH_TABLE_SIZE];

/*
entry *initFreeEntryPool(unsigned int freeBufferSize)
{
    int i,j;
    entry *freeEntry = NULL;

    for(i=0; i < MAX_HASH_TABLE_SIZE; i++){
        for(j=0; j < freeBufferSize; j++){
            freeEntry = (entry *) malloc(sizeof(entry));
            freeEntry->pNext = freePool[i];
        }
    }
}*/

unsigned int BKDRHash(char *str)
{
    unsigned int seed = 131;
    unsigned int hash = 0;

    while (*str) {
        hash = hash * seed + (*str++);
    }

    return (hash & 0x7FFFFFFF);
}

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastName[], entry *pHead)
{
    unsigned int  hVal = BKDRHash(lastName);
    unsigned char hashTableIndex = hVal % MAX_HASH_TABLE_SIZE;

    pHead = hashTable[hashTableIndex];

    while (pHead != NULL) {
        if (pHead->hashVal == hVal &&
                strcasecmp(lastName, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    unsigned char hashTableIndex ;

    /* allocate memory for the new entry and put lastName */
    entry *hashEntry = (entry *) malloc(sizeof(entry));
    strcpy(hashEntry->lastName, lastName);
    hashEntry->hashVal = BKDRHash(lastName);
    hashTableIndex = hashEntry->hashVal % MAX_HASH_TABLE_SIZE;

    if(hashTable[hashTableIndex]) {
        hashEntry->pNext = hashTable[hashTableIndex];
    }

    hashTable[hashTableIndex] = hashEntry;

    return hashEntry;
}
