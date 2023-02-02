#include "ts_node.h"

PyTypeObject TSVarType = {
    PyVarObject_HEAD_INIT(NULL, 0)

    .tp_name = "tsgraph.backend.TimeSeriesImpl",
    .tp_doc = "Low-level implementation of a computation node.",
};
