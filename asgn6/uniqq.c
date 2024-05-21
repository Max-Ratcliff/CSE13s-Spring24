#include "badhash.h"
#include "hash.h"
#include "item.h"
#include "ll.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int counter = 0;
    Hashtable *h = hash_create();
    while (true) {
        char buffy[1024];

        if (fgets(buffy, 1024, stdin) == NULL) {
            break;
        }
        if (!hash_get(h, buffy)) {
            hash_put(h, buffy, 1);
        } else {
            count++;
        }
    }
    hash_destroy(*h);
    printf("&d", counter);

    return 0;
}
