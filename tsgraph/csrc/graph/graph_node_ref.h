#ifndef TSGRAPH__CSRC_GRAPH_NODE_REF_H_
#define TSGRAPH__CSRC_GRAPH_NODE_REF_H_

#include "comp_graph.h"

typedef tsuint_t node_ref_t;

typedef struct {
    TSGraph *graph;
    node_ref_t ref_id;
} TSNodeRef;

TSNodeRef node_ref_new(TSGraph *graph, node_ref_t ref_id);

#endif // TSGRAPH__CSRC_GRAPH_NODE_REF_H_
