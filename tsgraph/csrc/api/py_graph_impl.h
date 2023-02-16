#ifndef TSGRAPH_CSRC_PY_GRAPH_IMPL_H_
#define TSGRAPH_CSRC_PY_GRAPH_IMPL_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "graph/comp_graph.h"

extern PyTypeObject GraphImplType;

typedef struct {
    PyObject_HEAD

    TSGraph graph;
} PyGraphImplObject;

static PyObject *py_graph_new(PyTypeObject *type, PyObject *args, PyObject *kwargs);
static int py_graph_init(PyTypeObject *type, PyObject *args, PyObject *kwargs);
static void py_graph_dealloc(PyGraphImplObject *obj);

#endif // TSGRAPH_CSRC_PY_GRAPH_IMPL_H_
