#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void graph_init(Graph *g)
{
    g->num_vertices = 0;
}

VertexIdx graph_add_vertex(Graph *g, const char *name)
{
    VertexIdx idx = graph_find_vertex(g, name);
    if (idx != -1) {
        return idx;
    }

    idx = g->num_vertices;

    size_t len = strlen(name);
    if (len >= MAX_NAME_LEN) {
        len = MAX_NAME_LEN - 1;
    }

    memcpy(g->vertices[idx].name, name, len);
    g->vertices[idx].name[len] = '\0';

    g->vertices[idx].head = NULL;
    g->num_vertices++;
    return idx;
}

VertexIdx graph_find_vertex(const Graph *g, const char *name)
{
    for (int i = 0; i < g->num_vertices; i++) {
        if (strncmp(g->vertices[i].name, name, MAX_NAME_LEN) == 0) {
            return i;
        }
    }
    return -1;
}

void graph_add_edge(Graph *g, VertexIdx src, VertexIdx dest)
{
    AdjNode *node = malloc(sizeof(AdjNode));
    node->dest = dest;
    node->next = g->vertices[src].head;
    g->vertices[src].head = node;
}

void graph_print(const Graph *g)
{
    for (int i = 0; i < g->num_vertices; i++) {
        printf("%s ->", g->vertices[i].name);
        AdjNode *curr = g->vertices[i].head;
        while (curr != NULL) {
            printf(" %s", g->vertices[curr->dest].name);
            curr = curr->next;
        }
        printf("\n");
    }
}

void graph_free(Graph *g)
{
    for (int i = 0; i < g->num_vertices; i++) {
        AdjNode *curr = g->vertices[i].head;
        while (curr != NULL) {
            AdjNode *next = curr->next;
            free(curr);
            curr = next;
        }
        g->vertices[i].head = NULL;
    }
    g->num_vertices = 0;
}