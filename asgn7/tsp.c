#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "i:o:dh"
#define USAGE                                                                                      \
    "Usage: tsp [options]\n\n"                                                                     \
    "-i infile    Specify the input file path containing the cities and edges\n"                   \
    "             of a graph. If not specified, the default input should be\n"                     \
    "             set as stdin.\n\n"                                                               \
    "-o outfile   Specify the output file path to print to. If not specified,\n"                   \
    "             the default output should be set as stdout.\n\n"                                 \
    "-d           Specifies the graph to be directed.\n\n"                                         \
    "-h           Prints out a help message describing the purpose of the\n"                       \
    "             graph and the command-line options it accepts, exiting the\n"                    \
    "             program afterwards.\n"

void dfs(Graph *g, uint32_t start, Path *curr, Path *best) {
    //printf("best len %u\n", path_distance(best));
    graph_visit_vertex(g, start);
    path_add(curr, start, g);
    ///printf("path added\n");
    //printf("new path length: %u\n", path_distance(curr));
    if (path_vertices(curr) == graph_vertices(g)) { //check if we traverse every path
        //printf("every path traversed\n");
        //printf("weight between 'start' and 0 is: %u\n", graph_get_weight(g, start, START_VERTEX));
        if (graph_get_weight(g, start, START_VERTEX) != 0) {
            path_add(curr, START_VERTEX, g);
            //printf("path added\n");
            //printf("new path length: %u\n", path_distance(curr));

            if (path_distance(best) || path_distance(curr) > path_distance(best)) {
                path_copy(best, curr);
                //printf("path coppied\n");
            }
            path_remove(curr, g);
        }
    }
    for (uint32_t node = 0; node < graph_vertices(g); node++) {
        if (graph_get_weight(g, start, node) > 0) {
            if (!graph_visited(g, node)) {
                dfs(g, node, curr, best);
            }
        }
    }
    graph_unvisit_vertex(g, start);
    path_remove(curr, g);
}

int main(int argc, char *argv[]) {
    int opt;

    bool directed = false;

    FILE *outfile = stdout;

    FILE *infile = stdin;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            infile = fopen(optarg, "r");
            if (infile == NULL) {
                infile = stdin;
                fprintf(stderr, USAGE);
            }
            break;
        case 'o':
            outfile = fopen(optarg, "w");
            if (outfile == NULL) {
                outfile = stdout;
                fprintf(stderr, USAGE);
            }
            break;
        case 'd': directed = true; break;
        case 'h': fprintf(stdout, USAGE); break;
        }
    }

    //start building graph
    uint32_t vertices;
    if (fscanf(infile, "%u", &vertices) != 1) {
        fprintf(stderr, "tsp: error reading number of vertices\n");
        fclose(infile);
        exit(1);
    }
    //capture newline
    char cap[10];
    fgets(cap, 10, infile);
    Graph *g = graph_create(vertices, directed);
    char *name = (char *) malloc(1024);
    for (uint32_t i = 0; i < vertices; i++) {
        if (!fgets(name, 1024, infile)) {
            fprintf(stderr, "tsp: error reading vertex %u's name read %s\n", i, name);
            fclose(infile);
            exit(1);
        }
        //capture newline
        name[strcspn(name, "\n")] = '\0';
        graph_add_vertex(g, name, i);
    }
    uint32_t edges;
    if (fscanf(infile, "%u", &edges) != 1) {
        fprintf(stderr, "tsp: error reading number of edges, read: %u\n", edges);
        fclose(infile);
        exit(1);
    }
    for (uint32_t i = 0; i < edges; i++) {
        uint32_t start, end, weight;
        if (fscanf(infile, "%u %u %u", &start, &end, &weight) != 3) {
            fprintf(stderr, "tsp: error reading edge %u\n", i);
            fclose(infile);
            exit(1);
        }
        graph_add_edge(g, start, end, weight);
    }

    //initialize paths
    Path *curr = path_create(vertices);
    Path *best = path_create(vertices);
    dfs(g, START_VERTEX, curr, best);
    //best should now contain the best path

    if (path_distance(best) == 0) {
        printf("No path found! Alissa is lost!\n");
    } else {
        //print path
        printf("Alissa starts at:\n");
        path_print(best, outfile, g);
    }

    free(name);
    path_free(&curr);
    path_free(&best);
    graph_free(&g);
    if (infile != stdin) {
        fclose(infile);
    }
    if (outfile != stdout) {
        fclose(outfile);
    }

    return 0;
}
