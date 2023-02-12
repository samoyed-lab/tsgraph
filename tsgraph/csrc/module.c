#include <Python.h>
#include <stdio.h>

#include "api/py_graph_impl.h"
#include "api/pyobj_operators.h"

#define NODE_OP_PROP(op) \
{"_node_ref_"#op, node_ref_##op, METH_VARARGS, "The "#op" operator for variables."}

static PyObject *test(PyObject *self, PyObject *args) {
	return PyLong_FromLong(10);
}

static PyMethodDef functions[] = {
    {"test", test, METH_NOARGS, ""},

    NODE_OP_PROP(ADD),
    NODE_OP_PROP(SUB),
    NODE_OP_PROP(MUL),
    NODE_OP_PROP(DIV),
    NODE_OP_PROP(MOD),

    NODE_OP_PROP(AND),
    NODE_OP_PROP(OR),
    NODE_OP_PROP(XOR),

    NODE_OP_PROP(EQU),
    NODE_OP_PROP(NEQ),
    NODE_OP_PROP(LEQ),
    NODE_OP_PROP(GEQ),
    NODE_OP_PROP(LE),
    NODE_OP_PROP(GE),

    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef tsgraph = {
    PyModuleDef_HEAD_INIT,
    "tsgraph",
    "Event-driven computation graph for time series analysis and model optimization.",
    -1,
    functions
};

PyMODINIT_FUNC PyInit_backend() {
	PyObject *module = PyModule_Create(&tsgraph);
    if (module == NULL) return NULL;

    if (PyType_Ready(&GraphImplType) < 0) return NULL;
    Py_INCREF(&GraphImplType);

    if (PyModule_AddObject(module, "GraphImpl", (PyObject *) &GraphImplType) < 0) {
        Py_DECREF(&GraphImplType);
        Py_DECREF(module);
        return NULL;
    }

	return module;
};
