#include "hash.h"

#include "badhash.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Hashtable *hash_create(void) {
    Hashtable *hashtable = (Hashtable *) malloc(sizeof(Hashtable));
    if (!hashtable) {
        return NULL;
    } //hashtable is null
    for (int i = 0; i < BUCKETS; i++) {
        hashtable->bucket[i] = list_create(); //initialize each bucket to an empty list
    }
    return hashtable;
}

bool hash_put(Hashtable *hashtable, char *key, int val) {
    if (!hashtable || !key) {
        return NULL;
    } //ensure both hashtable and key point somewhere

    size_t bucket_to_put = hash(key) % BUCKETS; // finds bucket based on hash function
    //create item to put
    item *to_put = (item *) malloc(sizeof(item));
    to_put->id = val;
    strcpy(to_put->key, key);

    return list_add(hashtable->bucket[bucket_to_put],
        to_put); // attempt to add an item to the list at selected bucket
}

int *hash_get(Hashtable *hashtable, char *key) {
    if (!hashtable || !key) {
        return NULL;
    } //ensure both hashtable and key point somewhere
    size_t bucket_to_get = hash(key) % BUCKETS; // finds bucket based on hash function

    item *temp = (item *) malloc(sizeof(item)); //list_find takes ptr to an item to find
    strcpy(temp->key, key); //set of ket of item to find to key for hash to find
    item *get_item
        = list_find(hashtable->bucket[bucket_to_get], cmp, temp); //run list find to find item
    return get_item
               ? &(get_item->id)
               : NULL; //return ptr to value of the iteam if get_item != NULL otherwise return NULL
}

void hash_destroy(Hashtable **hashtable) {
    for (int i = 0; i < BUCKETS; i++) {
        list_destroy((&(*hashtable)->bucket[i])); //iterate through buckets destroying every list
    }

    free(*hashtable); //free memory of hash table
    *hashtable = NULL; //set ptr to null
    return;
}
