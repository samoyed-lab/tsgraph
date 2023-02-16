#ifndef TSGRAPH__CSRC_COMP_GRAPH_H_
#define TSGRAPH__CSRC_COMP_GRAPH_H_

#include <glib.h>
#include <stdbool.h>

#include "misc/types.h"

enum NodeOp {
    // Input (leaf node).
    OP_INP,

    // Constant.
    OP_CON,

    // Arithmetics.
    OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_MOD,

    // Logic.
    OP_AND, OP_OR, OP_XOR,

    // Equality.
    OP_EQU, OP_NEQ, OP_LEQ, OP_GEQ, OP_LE, OP_GE
};

typedef struct TSNode {

    /*
        An extra field indicating the index of this node in its parent's
        node array. Currently unused, but added as a precaution in case
        a node ptr to index mapping is needed (due to how nodes directly
        access their dependents/dependencies through pointers instead of
        indexing via parent graph).
    */
    tsuint_t id;

    /*
        The current length of the sequence. 0 if this node is unpopulated.
    */
    tsuint_t curr_len;

    /*
        If this node represents a scalar instead of a time-series.
    */
    bool is_scalar;

    /*
        If this node should only keep track of `max_window_len` most recent
        elements in memory. Defaults to false.
    */
    bool is_sliding_window;

    /*
        The amount of elements to keep in memory if `use_sliding_window` is
        true.
    */
    tsuint_t max_window_len;

    /*
        All nodes whose value depend on this node, i.e. ones that
        should be updated on update of this node.
    */
    GPtrArray *dependents;

    /*
        An array of dependencies for this node. Any update in a
        dependency triggers an update on this node.

        Note that this has a fixed length, as the type of the operator
        dictates how many dependents it have.
    */
    struct TSNode **dependencies;
    enum NodeOp type;

    /*
        Denotes how high up in the computation tree this node is.
        Input nodes has a `tree_level` of 0. Every intermediate
        node's `tree_level` is one plus the maximum `tree_level`
        of its dependency nodes. This ensure an partial order on
        nodes so that each node is only updated once in a complete
        graph (ensures all dependencies are reached prior to reaching
        a node).
    */
    tsuint_t tree_level;

    /*
        Whether this node's value has been changed since the last graph
        evaluation.
    */
    bool dirty;
} TSNode;

void node_free(TSNode *node);

typedef struct {
    /*
        Whether event-handler callbacks are enabled.
    */
   bool handle_trigger;

    /*
        All nodes in this calculation graph, referenced by their index.
    */
    GPtrArray *nodes;

    /*
        All variables whose value is populated by user inputs during
        graph evaluation.
    */
    GPtrArray *input_nodes;

    /*
        All (input) nodes whose value has been changed since the last
        graph evaluation. Used for partial graph updates.
    */
    GPtrArray *dirty_nodes;
} TSGraph;

void graph_init(TSGraph *graph);
void graph_clear(TSGraph *graph); // DOES NOT FREE THE GRAPH POINTER!!!
bool graph_is_valid_node(TSGraph *graph, tsuint_t id);


/*
    Creates a new node resembling a compound operation.

    May set a Python error string. Check with `PyErr_Occurred()`;
*/
tsuint_t graph_comp_node(TSGraph *graph, enum NodeOp type, int n_deps, tsuint_t deps[]);

#endif // TSGRAPH__CSRC_COMP_GRAPH_H_
