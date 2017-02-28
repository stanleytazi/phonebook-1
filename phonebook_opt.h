#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16
#define MAX_HASH_TABLE_SIZE 1024
#define MAX_MEMORY_POOL_SIZE 1000000
//#define MEMORY_POOL_FOR_EACH_HASH_TABLE_ENTRY 1
/* TODO: After modifying the original version, uncomment the following
 * line to set OPT properly */
#define OPT 1

typedef struct {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
} entry_detail;

typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    unsigned int hashVal;
    entry_detail *info;
    struct __PHONE_BOOK_ENTRY *pNext;
} entry;

typedef struct __PHONE_BOOK_HASH_ELEMENT {
    unsigned int hashVal;
    entry *phoneInfo;
    struct __PHONE_BOOK_HASH_ELEMENT *pNext;
} hash_node;

entry *findName(char lastName[], entry *pHead);
entry *append(char lastName[], entry *e);

void initFreeEntryPool(unsigned int freeBufferNum);
void createFreeEntryPool(unsigned int freeBufferNum);

#endif
