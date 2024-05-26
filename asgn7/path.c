#include "path.h"

#include <assert.h>
#include <stdlib.h>

typedef struct path {
    uint32_t total_weight;
    Stack *vertices;
} Path;

Path *path_create(uint32_t capacity) {
    Path *p = (Path *) malloc(sizeof(Path));
    p->total_weight = 0;
    p->vertices = stack_create(capacity);

    return p;
}

void path_free(Path **pp) {
    if (pp != NULL && *pp != NULL) {
        //(*p)->vertices is a pointer to a stack
        //so &(*stack) == **stack?
        //stack_free(Stack **sp)
        stack_free(&((*pp)->vertices));
        //then free the path
        free(*pp);
    }
    if (pp != NULL) {
        *pp = NULL;
    }
}

uint32_t path_vertices(const Path *p) {
    assert(p != NULL);
    uint32_t *top = NULL;
    assert(stack_peek(p->vertices, top));
    return (*top);
}

uint32_t path_distance(const Path *p) {
    assert(p != NULL);
    return (p->total_weight);
}

void path_add(Path *p, uint32_t val, const Graph *g) {
    //handle empty path
    if (stack_size(p->vertices) == 0) {
        //dont change distance
        //add vertex val to top of stack
        stack_push((p->vertices), val);
    } else {
        //a vertex is already on the stack eg at least two cities in path
        //add a new one and add the distance between the new one and the one on the top of the stack to total weight
        uint32_t *prev = NULL;
        assert(stack_peek((p->vertices), prev));
        // prev should now point to one of the first city
        // add new vertex to the top of stack
        stack_push((p->vertices), val);
        //get distance betweenp prev and val
        uint32_t weight = graph_get_weight(g, *prev, val);
        //update total_weight
        p->total_weight += weight;
    }
}

uint32_t path_remove(Path *p, const Graph *g) {
    (void) p;
    (void) g;
    return (uint32_t) -1;
}

void path_copy(Path *dst, const Path *src) {
    (void) dst;
    (void) src;
}

void path_print(const Path *p, FILE *f, const Graph *g) {
    (void) p;
    (void) f;
    (void) g;
}
