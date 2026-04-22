#include "algorithms/algorithms.h"
#include "graph/graph.h"
#include "parser/parser.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    int exit_code = 0;

    if (argc < 2) {
        (void)fprintf(stderr, "Uso: %s <Gemfile.lock>\n", argv[0]);
        return 1;
    }

    Graph g = {0};
    graph_init(&g);

    if (parse_gemfile_lock(argv[1], &g) != 0) {
        exit_code = 1;
        goto cleanup;
    }

    printf("Gems encontradas: %d\n\n", g.num_vertices);

    DFSResult result = {0};
    dfs(&g, &result);

    if (result.has_cycle) {
        printf("Ciclo detectado — Gemfile.lock inválido\n");
        goto cleanup;
    }

    printf("Ordem de instalação:\n");
    for (int i = 0; i < result.order_count; i++) {
        printf("  %d. %s\n", i + 1, g.vertices[result.order[i]].name);
    }

cleanup:
    graph_free(&g);
    return exit_code;
}
