#include "graph.h"
#include "path.h"
#include "stack.h"

#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    uint32_t cap = 10;
    Path *p = path_create(cap);

    Graph *g = graph_create(3, false);
    graph_add_vertex(g, "testv1", 0);
    graph_add_vertex(g, "testv2", 1);
    graph_add_vertex(g, "testv3", 2);

    graph_print(g);

    path_add(p, 0, g);

    assert(path_distance(p) == 0);
    printf("%u\n", path_distance(p));

    //Stack *s = stack_create(cap);

    //assert(path_vertices(p) == 0);
    printf("%u\n", path_vertices(p));

    path_add(p, 1, g);

    printf("%u\n", path_distance(p));
    printf("%u\n", path_vertices(p));
    return 0;
}
