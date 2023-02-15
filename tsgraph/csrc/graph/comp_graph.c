#include "comp_graph.h"

#include <glib.h>

#include "misc/types.h"

void node_free(TSNode *node) {
    g_ptr_array_free(node->dependencies, false);
    g_ptr_array_free(node->dependents, false);
    free(node);
}

void graph_init(TSGraph *graph) {
    graph->input_nodes = g_ptr_array_new_with_free_func(node_free);
    graph->dirty_nodes = g_ptr_array_new();
    graph->input_nodes = g_ptr_array_new();
}

void graph_clear(TSGraph *graph) {
    g_ptr_array_free(graph->input_nodes, false);
    g_ptr_array_free(graph->dirty_nodes, false);
    g_ptr_array_free(graph->nodes, true);
}

tsuint_t graph_compound_node(TSGraph *graph, tsuint_t a, tsuint_t b, enum NodeOp type) {
    return 0;
}
