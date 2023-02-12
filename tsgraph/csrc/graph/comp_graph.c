#include "comp_graph.h"

#include "misc/ptr_array.h"

void graph_init(TSGraph *graph) {
    // TODO: init graph
}

void graph_clear(TSGraph *graph) {
    ptr_array_free(graph->input_nodes, false);
    ptr_array_free(graph->dirty_nodes, false);
    ptr_array_free(graph->nodes, true);
}

tsuint_t graph_compound_node(TSGraph *graph, tsuint_t a, tsuint_t b, enum NodeOp type) {
    return 0;
}
