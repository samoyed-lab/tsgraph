#ifndef TSGRAPH_CSRC_PY_GRAPH_IMPL_H_
#define TSGRAPH_CSRC_PY_GRAPH_IMPL_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "graph/comp_graph.h"

extern PyTypeObject GraphImplType;
extern PyMethodDef py_graph_methods[];

typedef struct {
    PyObject_HEAD

    TSGraph graph;
} PyGraphImplObject;

PyObject *py_graph_new(PyTypeObject *type, PyObject *args, PyObject *kwargs);
int py_graph_init(PyTypeObject *type, PyObject *args, PyObject *kwargs);
void py_graph_dealloc(PyGraphImplObject *obj);

PyObject *py_graph_set_trigger(PyGraphImplObject *self, PyObject *args);

#endif // TSGRAPH_CSRC_PY_GRAPH_IMPL_H_
