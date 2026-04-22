#ifndef GRAPH_H
#define GRAPH_H

#define MAX_VERTICES 256
#define MAX_NAME_LEN 64

typedef int VertexIdx;

typedef struct AdjNode {
    VertexIdx dest;
    struct AdjNode *next;
} AdjNode;

typedef struct Vertex {
    char name[MAX_NAME_LEN];
    AdjNode *head;
} Vertex;

typedef struct Graph {
    int num_vertices;
    Vertex vertices[MAX_VERTICES];
} Graph;

void graph_init(Graph *g);
VertexIdx graph_add_vertex(Graph *g, const char *name);
VertexIdx graph_find_vertex(const Graph *g, const char *name);
void graph_add_edge(Graph *g, VertexIdx src, VertexIdx dest);
void graph_print(const Graph *g);
void graph_free(Graph *g);

#endif