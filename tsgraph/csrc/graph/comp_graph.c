#include "comp_graph.h"

#include <glib.h>

#include "misc/macros.h"
#include "misc/types.h"

void node_free(TSNode *node) {
    g_ptr_array_free(node->dependents, false);
    free(node->dependencies);
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

bool graph_is_valid_node(TSGraph *graph, tsuint_t id) {
    return id < graph->nodes->len;
}

// TODO: support NodeOp with variable number of dependency nodes.
tsuint_t graph_binary_node(TSGraph *graph, tsuint_t a, tsuint_t b, enum NodeOp type) {
    if (!(graph_is_valid_node(graph, a) && graph_is_valid_node(graph, b))) {
        PyErr_SetString(PyExc_IndexError, "Node ID out of bounds");
        return 0;
    }

    TSNode *node = malloc(sizeof(TSNode));
    if (node == NULL) {
        SetErr_NoMem;
        return 0;
    }

    tsuint_t node_id = graph->nodes->len;
    node->id = node_id;
    node->curr_len = 0;
    node->is_scalar = false;
    // TODO: make this respect children nodes settings.
    node->use_sliding_window = false;
    node->max_window_len = 0;

    // TODO: finish initialization.

    node->dirty = false;

    g_ptr_array_add(graph->nodes, node);
    return node_id;
}
