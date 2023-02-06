#ifndef TSGRAPH__CSRC_TS_NODE_H_
#define TSGRAPH__CSRC_TS_NODE_H_

#include <Python.h>
#include <numpy/arrayobject.h>

#include "../misc/types.h"
#include "../graph/comp_graph.h"

typedef tsuint_t node_ref_t;

extern PyTypeObject TSVarType;

typedef struct {
    PyObject_HEAD
    
    PyObject *graph_obj;
    node_ref_t ref_id;
} PyNodeRefObject;

#endif // TSGRAPH__CSRC_TS_NODE_H_
