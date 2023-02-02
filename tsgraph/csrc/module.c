#include <Python.h>

static PyObject *makeTensorFromList(PyObject *self, PyObject *args) {
	return PyLong_FromLong(10);
}

static PyMethodDef functions[] = {
    {"test", makeTensorFromList, METH_VARARGS, ""},
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

    PyModule_AddIntConstant(module, "TEST", 64);

	return module;
};
