#include "comp_graph.h"

#include <glib.h>

#include "misc/types.h"

void graph_init(TSGraph *graph) {
    // TODO: init graph
}

void graph_clear(TSGraph *graph) {
    g_ptr_array_free(graph->input_nodes, false);
    g_ptr_array_free(graph->dirty_nodes, false);
    g_ptr_array_free(graph->nodes, true);
}

tsuint_t graph_compound_node(TSGraph *graph, tsuint_t a, tsuint_t b, enum NodeOp type) {
    return 0;
}
