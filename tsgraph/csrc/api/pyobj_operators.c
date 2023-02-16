#include "pyobj_operators.h"

#include "api/py_graph_impl.h"
#include "graph/comp_graph.h"
#include "misc/types.h"

static PyObject *make_bin_op_node(PyObject *args, enum NodeOp op) {
    PyObject *graph = NULL;
    tsuint_t a, b;
    PyObject *ret = NULL;

    do {
        if (!PyArg_ParseTuple(args, "OII", &graph, &a, &b)) break;
        Py_INCREF(graph);

        if (!PyObject_IsInstance(graph, (PyObject *) &GraphImplType)) {
            PyErr_SetString(
                PyExc_TypeError,
                "Expecting argument 1 to be of type GraphImpl"
            );
            break;
        }

        PyGraphImplObject *graph_impl = (PyGraphImplObject *) graph;
        tsuint_t new_node = graph_comp_node(
            &(graph_impl->graph),
            op,
            2,
            (tsuint_t[]) {a, b}
        );
        if (PyErr_Occurred()) break;

        ret = PyLong_FromUnsignedLong(new_node);
    } while (false);

    Py_XDECREF(graph);
    return ret;
}

#define NODE_BINARY_OPERATOR_DEF(op) \
PyObject *node_ref_##op(PyObject *self, PyObject *args) { \
    return make_bin_op_node(args, OP_##op); \
}

NODE_BINARY_OPERATOR_DEF(ADD)
NODE_BINARY_OPERATOR_DEF(SUB)
NODE_BINARY_OPERATOR_DEF(MUL)
NODE_BINARY_OPERATOR_DEF(DIV)
NODE_BINARY_OPERATOR_DEF(MOD)

NODE_BINARY_OPERATOR_DEF(AND)
NODE_BINARY_OPERATOR_DEF(OR)
NODE_BINARY_OPERATOR_DEF(XOR)

NODE_BINARY_OPERATOR_DEF(EQU)
NODE_BINARY_OPERATOR_DEF(NEQ)
NODE_BINARY_OPERATOR_DEF(LEQ)
NODE_BINARY_OPERATOR_DEF(GEQ)
NODE_BINARY_OPERATOR_DEF(LE)
NODE_BINARY_OPERATOR_DEF(GE)
