#include "parser.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LEN 256

static int count_leading_spaces(const char *line)
{
    int count = 0;
    while (line[count] == ' ') {
        count++;
    }
    return count;
}

static void extract_gem_name(const char *line, char *name, int max_len)
{
    int i = 0;
    while (isspace((unsigned char)line[i])) {
        i++;
    }

    int j = 0;
    while (line[i] && line[i] != ' ' && line[i] != '(' && j < max_len - 1) {
        name[j++] = line[i++];
    }
    name[j] = '\0';
}

static void strip_newline(char *line, int *len)
{
    while (*len > 0 && (line[*len - 1] == '\n' || line[*len - 1] == '\r')) {
        line[--(*len)] = '\0';
    }
}

static void process_line(const char *line, Graph *g, int *in_gem_section,
                         int *in_specs, VertexIdx *current)
{
    if (strcmp(line, "GEM") == 0) {
        *in_gem_section = 1;
        *in_specs = 0;
        return;
    }

    if (*in_gem_section && strcmp(line, "  specs:") == 0) {
        *in_specs = 1;
        return;
    }

    if (*in_gem_section && *in_specs && line[0] != ' ') {
        *in_gem_section = 0;
        *in_specs = 0;
        return;
    }

    if (!(*in_specs)) {
        return;
    }

    int spaces = count_leading_spaces(line);
    char name[MAX_NAME_LEN];

    if (spaces == 4) {
        extract_gem_name(line, name, MAX_NAME_LEN);
        *current = graph_add_vertex(g, name);
    } else if (spaces == 6 && *current != -1) {
        extract_gem_name(line, name, MAX_NAME_LEN);
        VertexIdx dep = graph_add_vertex(g, name);
        graph_add_edge(g, *current, dep);
    }
}

int parse_gemfile_lock(const char *filepath, Graph *g)
{
    FILE *f = fopen(filepath, "r");
    if (!f) {
        (void)fprintf(stderr, "Erro ao abrir arquivo: %s\n", filepath);
        return -1;
    }

    char line[MAX_LINE_LEN];
    int in_gem_section = 0;
    int in_specs = 0;
    VertexIdx current = -1;

    while (fgets(line, sizeof(line), f)) {
        int len = (int)strlen(line);
        strip_newline(line, &len);
        process_line(line, g, &in_gem_section, &in_specs, &current);
    }

    (void)fclose(f);
    return 0;
}