#ifndef PARSER_H
#define PARSER_H

#include "graph/graph.h"

int parse_gemfile_lock(const char *filepath, Graph *g);

#endif