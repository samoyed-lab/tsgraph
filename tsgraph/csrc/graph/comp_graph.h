#ifndef TSGRAPH__CSRC_COMP_GRAPH_H_
#define TSGRAPH__CSRC_COMP_GRAPH_H_

#include "../misc/ptr_array.h"

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
        All nodes whose value depend on this node, i.e. ones that
        should be updated on update of this node.
    */
    PtrArray *dependents;

    /*
        An array of dependencies for this node. Any update in a
        dependency triggers an update on this node.
    */
    struct TSNode *dependencies;
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

typedef struct {
    /*
        All nodes in this calculation graph, referenced by their index.
    */
    PtrArray *nodes;

    /*
        All variables whose value is populated by user inputs during
        graph evaluation.
    */
    PtrArray *input_nodes;

    /*
        All (input) nodes whose value has been changed since the last
        graph evaluation. Used for partial graph updates.
    */
    PtrArray *dirty_nodes;
} TSGraph;

#endif // TSGRAPH__CSRC_COMP_GRAPH_H_
