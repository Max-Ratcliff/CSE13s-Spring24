#include "ll.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

LL *list_create(void) {
    LL *l = (LL *) malloc(sizeof(LL));
    if (l == NULL) {
        return NULL;
    }
    l->head = NULL;
    return l;
}

bool list_add(LL *l, item *i) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n == NULL) {
        return false;
    }
    n->data = *i;
    n->next = NULL;
    if (l->head == NULL) {
        l->head = n;
        return true;
    } else {
        Node *tail = l->head;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = n;
        return true;
    }
}

item *list_find(LL *l, bool (*cmpfn)(item *, item *), item *i) {
    Node *n = l->head;
    while (n != NULL) {
        if (cmpfn(&n->data, i)) {
            return &n->data;
        }
        n = n->next;
    }
    return NULL;
}

void list_destroy(LL **ll) {
    if (ll == NULL || *ll == NULL) {
        return;
    }
    Node *curr = (*ll)->head;
    Node *next_node = NULL;
    while (curr != NULL) {
        next_node = curr->next;
        free(curr);
        curr = next_node;
    }
    (*ll)->head = NULL;
    free(*ll);
    *ll = NULL;

    return;
}
void list_remove(LL *ll, bool (*cmpfn)(item *, item *), item *iptr) {
    if (ll->head == NULL) { // handles no head
        return;
    }

    Node *curr = ll->head; //sets current pointer to the start of the linked list
    Node *prev = NULL;
    if (cmpfn(&curr->data, iptr)) { //handles head being deleted
        ll->head = curr->next; //sets new head to 2nd item of list
        free(curr);
        return;
    }

    while (curr != NULL) {
        if (cmpfn(&curr->data, iptr)) { // finds target item in list
            prev->next = curr->next; //deletes item
            free(curr); //free memory
            return;
        }
        prev = curr; //increment to look at the next item in the list
        curr = curr->next;
    }
    return;
}
