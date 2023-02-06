#include "ts_node.h"

PyTypeObject TSVarType = {
    PyVarObject_HEAD_INIT(NULL, 0)

    .tp_name = "tsgraph.backend.TimeSeriesImpl",
    .tp_doc = PyDoc_STR("Low-level implementation of a computation node."),
    .tp_basicsize = sizeof(PyNodeRefObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE
};
