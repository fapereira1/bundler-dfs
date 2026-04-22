#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "graph/graph.h"

typedef enum { WHITE = 0, GRAY = 1, BLACK = 2 } VertexColor;

typedef struct {
    VertexColor color[MAX_VERTICES];
    VertexIdx order[MAX_VERTICES];
    int order_count;
    int has_cycle;
} DFSResult;

void dfs(const Graph *g, DFSResult *result);
void dfs_print_order(const Graph *g, const DFSResult *result);

#endif