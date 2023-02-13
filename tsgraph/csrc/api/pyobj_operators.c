#include "pyobj_operators.h"

#include "api/py_graph_impl.h"
#include "graph/comp_graph.h"
#include "misc/types.h"

static PyObject *make_compound_node(PyObject *args, enum NodeOp op) {
    PyObject *graph;
    tsuint_t a, b;
    if (!PyArg_ParseTuple(args, "OII", &graph, &a, &b)) return NULL;
    
    if (!PyObject_IsInstance(graph, (PyObject *) &GraphImplType)) {
        PyErr_SetString(
            PyExc_TypeError,
            "Expecting argument 1 to be of type GraphImpl"
        );
        return NULL;
    }
    /*
    PyGraphImplObject *graph_impl = (PyGraphImplObject *) graph;
    tsuint_t new_node = graph_compound_node(&(graph_impl->graph), a, b, op);*/

    return PyLong_FromUnsignedLong(1);//new_node);
}

#define NODE_OPERATOR_DEF(op) \
PyObject *node_ref_##op(PyObject *self, PyObject *args) { \
    return make_compound_node(args, OP_##op); \
}

NODE_OPERATOR_DEF(ADD)
NODE_OPERATOR_DEF(SUB)
NODE_OPERATOR_DEF(MUL)
NODE_OPERATOR_DEF(DIV)
NODE_OPERATOR_DEF(MOD)

NODE_OPERATOR_DEF(AND)
NODE_OPERATOR_DEF(OR)
NODE_OPERATOR_DEF(XOR)

NODE_OPERATOR_DEF(EQU)
NODE_OPERATOR_DEF(NEQ)
NODE_OPERATOR_DEF(LEQ)
NODE_OPERATOR_DEF(GEQ)
NODE_OPERATOR_DEF(LE)
NODE_OPERATOR_DEF(GE)