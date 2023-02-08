#include <Python.h>
#include <stdio.h>

#include "api/py_graph_impl.h"

static PyObject *test(PyObject *self, PyObject *args) {
    
    

	return PyLong_FromLong(10);
}

static PyMethodDef functions[] = {
    {"test", test, METH_NOARGS, ""},
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

	return module;
};
