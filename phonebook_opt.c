#include <stdlib.h>
#include <string.h>

#include "phonebook_opt.h"


static entry *hashTable[MAX_HASH_TABLE_SIZE];
entry *freePoolHead = NULL;

#ifdef MEMORY_POOL_FOR_EACH_HASH_TABLE_ENTRY
entry *freePool[MAX_HASH_TABLE_SIZE];
void initFreeEntryPool(unsigned int freeBufferNum)
{
    int i,j;
    entry *freeEntry = NULL;

    for(i=0; i < MAX_HASH_TABLE_SIZE; i++) {
        freeEntry = (entry *) malloc(sizeof(entry));
        freePool[i] = freeEntry;
        for(j=1; j < freeBufferNum; j++) {
            if(freeEntry) {
                freeEntry->pNext = (entry *) malloc(sizeof(entry));
                freeEntry = freeEntry->pNext;
                freeEntry->pNext = NULL;
            }
        }
    }
}

entry *allocEmptyEntry(unsigned int tableIndex)
{
    entry *output = NULL;
    if(tableIndex < MAX_HASH_TABLE_SIZE) {
        output = freePool[tableIndex];
        if(output)
            freePool[tableIndex] = output->pNext;
    }

    return output;
}
#endif

void createFreeEntryPool(unsigned int freeBufferNum)
{
    entry *newEntry = NULL;
    while(freeBufferNum--) {
        newEntry = (entry *) malloc(sizeof(entry));
        newEntry->pNext = freePoolHead;
        freePoolHead = newEntry;
    }
}

entry *getEmptyEntry(void)
{
    entry *output = NULL;

    output = freePoolHead;
    freePoolHead = freePoolHead->pNext;
    return output;
}



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
    unsigned int  hashTableIndex = hVal % MAX_HASH_TABLE_SIZE;

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
    unsigned int hVal = BKDRHash(lastName);
    unsigned int hashTableIndex = hVal % MAX_HASH_TABLE_SIZE;
    /* allocate memory for the new entry and put lastName */
    //entry *hashEntry = (entry *) malloc(sizeof(entry));
#ifdef MEMORY_POOL_FOR_EACH_HASH_TABLE_ENTRY
    entry *hashEntry = allocEmptyEntry(hashTableIndex);
#else
    entry *hashEntry = getEmptyEntry();
#endif
    if(!hashEntry)
        hashEntry = (entry *) malloc(sizeof(entry));

    strcpy(hashEntry->lastName, lastName);
    hashEntry->hashVal = hVal;

    if(hashTable[hashTableIndex]) {
        hashEntry->pNext = hashTable[hashTableIndex];
    }

    hashTable[hashTableIndex] = hashEntry;

    return hashEntry;
}
