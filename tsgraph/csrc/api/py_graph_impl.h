#ifndef TSGRAPH_CSRC_PY_GRAPH_IMPL_H_
#define TSGRAPH_CSRC_PY_GRAPH_IMPL_H_

#include <Python.h>

#include "graph/comp_graph.h"

extern PyTypeObject GraphImplType;

typedef struct {
    PyObject_HEAD

    TSGraph graph;
} PyGraphImplObject;

#endif // TSGRAPH_CSRC_PY_GRAPH_IMPL_H_
