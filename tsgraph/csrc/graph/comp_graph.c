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
    graph->input_nodes = g_ptr_array_new_with_free_func((GDestroyNotify) node_free);
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
/*
    Note that `n_deps` cannot rely on `type`, as in the case of custom Python-based
    propagation functions, the amount of dependency nodes is decided by the user.
*/
tsuint_t graph_comp_node(TSGraph *graph, enum NodeOp type, int n_deps, tsuint_t deps[]) {

    TSNode **dep_nodes = malloc(sizeof(TSNode *) * n_deps);
    if (dep_nodes == NULL) {
        SetErr_NoMem;
        return 0;
    }

    for (int i = 0; i < n_deps; i++) {
        if (!graph_is_valid_node(graph, deps[i])) {
            free(dep_nodes);
            PyErr_SetString(PyExc_IndexError, "Node ID out of bounds");
            return 0;
        }

        dep_nodes[i] = g_ptr_array_index(graph->nodes, i);
    }

    TSNode *node = malloc(sizeof(TSNode));
    if (node == NULL) {
        SetErr_NoMem;
        free(dep_nodes);
        return 0;
    }

    tsuint_t node_id = graph->nodes->len;
    node->id = node_id;
    node->curr_len = 0;
    node->is_scalar = false;

    node->is_sliding_window = false;
    node->max_window_len = 0;
    node->tree_level = 0;
    for (int i = 0; i < n_deps; i++) {
        node->is_sliding_window |= dep_nodes[i]->is_sliding_window;
        node->max_window_len = MAX(node->max_window_len, dep_nodes[i]->max_window_len);
        node->tree_level = MAX(node->tree_level, dep_nodes[i]->tree_level + 1);

        g_ptr_array_add(dep_nodes[i]->dependents, node);
    }

    node->dependents = g_ptr_array_new();
    node->dependencies = dep_nodes;
    node->type = type;

    node->dirty = false;

    g_ptr_array_add(graph->nodes, node);
    return node_id;
}
