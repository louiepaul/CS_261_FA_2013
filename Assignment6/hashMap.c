/****************************************
 *
 * hashMap.c
 *
 * @AUTHOR: Ian Paul
 *
 * @DATE: 11/26/2013
 *
 *
 *
 ****************************************/



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hashMap.h"

/******************************************
 *
 * struct hashLink {
  * KeyType key; //the key is what you use to look up a hashLink
  ValueType value; //the value stored with the hashLink, a pointer to int in the case of concordance
   struct hashLink * next; //*notice how these are like linked list nodes
};
typedef struct hashLink hashLink;

struct hashMap {
    hashLink ** table; //array of pointers to hashLinks
    int tableSize; //number of buckets in the table
    int count; /number of hashLinks in the table
};
typedef struct hashMap hashMap;
*****************************************/

int compare(KeyType left, KeyType right)
{
	int returnVal = strcmp(left, right);
	return returnVal;
}



/*the first hashing function you can use*/
int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

/*the second hashing function you can use*/
int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between stringHash1 and stringHash2 is on this line*/
	return r;
}

/* initialize the supplied hashMap struct*/
void _initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

/* allocate memory and initialize a hash map*/
hashMap *createMap(int tableSize) {
	assert(tableSize > 0);
	hashMap *ht;
	ht = malloc(sizeof(hashMap));
	assert(ht != 0);
	_initMap(ht, tableSize);
	return ht;
}

/*
 Free all memory used by the buckets.
 Note: Before freeing up a hashLink, free the memory occupied by key and value
 */
void _freeMap (struct hashMap * ht)
{  
	/*write this*/		
	int i;
	for (i=0; i<ht->tableSize; i++)
	{
		hashLink * currentLink = ht->table[i];

		while(currentLink != NULL)
		{
			hashLink * temp = currentLink->next;
			free(currentLink);
			currentLink = temp;
		}
	}
}

/* Deallocate buckets and the hash map.*/
void deleteMap(hashMap *ht) {
	assert(ht!= 0);
	/* Free all memory used by the buckets */
	_freeMap(ht);
	/* free the hashMap struct */
	free(ht);
}

/* 
Resizes the hash table to be the size newTableSize 
*/
void _setTableSize(struct hashMap * ht, int newTableSize)
{
	/*write this*/
	hashLink **tempTable = ht->table;
	int tempSize = ht->tableSize;

	_initMap(ht, newTableSize);


	int i;
	for(i=0; i<tempSize; i++)
	{
		hashLink * currentLink = tempTable[i];
		while (currentLink != NULL)
		{
			insertMap(ht, currentLink->key, currentLink->value);
			hashLink * temp = currentLink->next;
			currentLink = temp;
		}
	}
}

/*
 insert the following values into a hashLink, you must create this hashLink but
 only after you confirm that this key does not already exist in the table. For example, you
 cannot have two hashLinks for the word "taco".
 
 if a hashLink already exists in the table for the key provided you should
 replace that hashLink--this requires freeing up the old memory pointed by hashLink->value
 and then pointing hashLink->value to value v.
 
 also, you must monitor the load factor and resize when the load factor is greater than
 or equal LOAD_FACTOR_THRESHOLD (defined in hashMap.h).
 */
void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{  
	/*write this*/	
	if((ht->count / (double)ht->tableSize) > 0.75)
	{
		_setTableSize(ht, ht->tableSize * 2);
	}
	ht->count++;

	int index = stringHash2(k) % ht->tableSize;

	hashLink ** currentLink = &ht->table[index];

	while(*currentLink != NULL)
	{
		currentLink = &(*currentLink)->next;
	}

	struct hashLink * newLink = (struct hashLink *) malloc(sizeof(struct hashLink));
	assert(newLink !=0);
	newLink->key = k;
	newLink->value = v;
	newLink->next = NULL;
	*currentLink = newLink;

}

/*
 this returns the value (which is void*) stored in a hashLink specified by the key k.
 
 if the user supplies the key "taco" you should find taco in the hashTable, then
 return the value member of the hashLink that represents taco.
 
 if the supplied key is not in the hashtable return NULL.
 */
ValueType* atMap (struct hashMap * ht, KeyType k)
{ 
	/*write this*/
	int index = stringHash2(k) % ht->tableSize;
	hashLink * currentLink = ht -> table[index];
	while(currentLink != NULL)
	{
		if(compare(k, currentLink->key) == 0)
		{
			return &currentLink->value;
		}
		currentLink = currentLink->next;
	}
	return NULL;
}

/*
 a simple yes/no if the key is in the hashtable. 
 0 is no, all other values are yes.
 */
int containsKey (struct hashMap * ht, KeyType k)
{  
	/*write this*/
	if (atMap(ht, k) == NULL)
	return 0;

	else
		return 1;
}

/*
 find the hashlink for the supplied key and remove it, also freeing the memory
 for that hashlink. it is not an error to be unable to find the hashlink, if it
 cannot be found do nothing (or print a message) but do not use an assert which
 will end your program.
 */
void removeKey (struct hashMap * ht, KeyType k)
{  
	/*write this*/	
	if(containsKey(ht, k) == 1)
	{
		int index = stringHash2(k) % ht->tableSize;
		hashLink * currentLink = ht->table[index];
		hashLink * tempLink = ht->table[index];

		if(strcmp(currentLink->key, k) == 0 )
		{
			ht->table[index] = currentLink->next;
			free(currentLink);
			return;
		}
		while(strcmp(currentLink->key, k) != 0)
		{
			tempLink = currentLink;
			currentLink = currentLink->next;
		}
		tempLink->next = currentLink->next;

		free(currentLink);
	}
	else
	{
		printf("The Key %d cannot be found! \n", k);
	}
}

/*
 returns the number of hashLinks in the table
 */
int size (struct hashMap *ht)
{  
	/*write this*/
	return ht->count;
	
}

/*
 returns the number of buckets in the table
 */
int capacity(struct hashMap *ht)
{  
	/*write this*/
	return ht->tableSize;
}

/*
 returns the number of empty buckets in the table, these are buckets which have
 no hashlinks hanging off of them.
 */
int emptyBuckets(struct hashMap *ht)
{  
	/*write this*/
	int index;
	int count = 0;
	for(index = 0; index < ht->tableSize; index++)
	{
		if(ht->table[index] == NULL)
		{
			count++;
		}
	}
	return count;
}

/*
 returns the ratio of: (number of hashlinks) / (number of buckets)
 
 this value can range anywhere from zero (an empty table) to more then 1, which
 would mean that there are more hashlinks then buckets (but remember hashlinks
 are like linked list nodes so they can hang from each other)
 */
float tableLoad(struct hashMap *ht)
{  
	/*write this*/
	float load = (float)ht->count / ht->tableSize;

	return load;

}
void printMap (struct hashMap * ht)
{
	int i;
	struct hashLink *temp;	
	for(i = 0;i < capacity(ht); i++){
		temp = ht->table[i];
		if(temp != 0) {		
			printf("\nBucket Index %d -> ", i);		
		}
		while(temp != 0){			
			printf("Key:%s|", temp->key);
			printValue(temp->value);
			printf(" -> ");
			temp=temp->next;			
		}		
	}
}


