#include <Python.h>
#include <stdio.h>

static PyMethodDef functions[] = {
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef mod_tsgraph = {
    PyModuleDef_HEAD_INIT,
    "tsgraph",
    "Event-driven computation graph for time series analysis and model optimization.",
    -1,
    functions
};

PyMODINIT_FUNC PyInit_minitorch_functions() {
	PyObject *module = PyModule_Create(&functions);

	return module;
};
