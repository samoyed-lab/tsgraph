#include "py_graph_impl.h"

PyTypeObject GraphImplType = {
    PyVarObject_HEAD_INIT(NULL, 0)

    .tp_name = "tsgraph.backend.GraphImpl",
    .tp_doc = PyDoc_STR(
        "C implementation of tsgraph's computation graph."
    ),
    .tp_basicsize = sizeof(PyGraphImplObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = PyType_GenericNew,
};
