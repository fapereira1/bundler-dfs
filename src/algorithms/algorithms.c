#include "algorithms.h"
#include <stdio.h>

static void dfs_visit(const Graph *g, VertexIdx v, DFSResult *result)
{
    result->color[v] = GRAY;

    AdjNode *curr = g->vertices[v].head;
    while (curr != NULL) {
        VertexIdx neighbor = curr->dest;

        if (result->color[neighbor] == WHITE) {
            dfs_visit(g, neighbor, result);
        } else if (result->color[neighbor] == GRAY) {
            result->has_cycle = 1;
        }

        curr = curr->next;
    }

    result->color[v] = BLACK;
    result->order[result->order_count++] = v;
}

void dfs(const Graph *g, DFSResult *result)
{
    for (int i = 0; i < MAX_VERTICES; i++) {
        result->color[i] = WHITE;
    }
    result->order_count = 0;
    result->has_cycle = 0;

    for (int i = 0; i < g->num_vertices; i++) {
        if (result->color[i] == WHITE) {
            dfs_visit(g, i, result);
        }
    }
}

void dfs_print_order(const Graph *g, const DFSResult *result)
{
    if (result->has_cycle) {
        printf("Ciclo detectado — ordenação topológica impossível\n");
        return;
    }

    printf("Ordem de instalação:\n");
    for (int i = 0; i < result->order_count; i++) {
        printf("  %d. %s\n", i + 1,
               g->vertices[result->order[i]].name);
    }
}