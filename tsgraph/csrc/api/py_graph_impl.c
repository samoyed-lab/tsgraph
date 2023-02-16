#include "py_graph_impl.h"

PyMethodDef py_graph_methods[] = {
    {
        "enable_handlers",
        (PyCFunction) py_graph_set_trigger,
        METH_O,
        "Sets whether graph updates should trigger event handlers "
        "attached to nodes"
    },
    {NULL}
};

PyTypeObject GraphImplType = {
    PyVarObject_HEAD_INIT(NULL, 0)

    .tp_name = "tsgraph.backend.GraphImpl",
    .tp_doc = PyDoc_STR(
        "C implementation of tsgraph's computation graph."
    ),
    .tp_basicsize = sizeof(PyGraphImplObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = py_graph_new,
    .tp_init = (initproc) py_graph_init,
    .tp_dealloc = (destructor) py_graph_dealloc,
    .tp_methods = py_graph_methods
};

PyObject *py_graph_new(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    PyGraphImplObject *obj = (PyGraphImplObject *) type->tp_alloc(type, 0);
    if (obj == NULL) return NULL;

    graph_init(&obj->graph);
    return (PyObject *) obj;
}

int py_graph_init(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    return 0;
}

void py_graph_dealloc(PyGraphImplObject *obj) {
    graph_clear(&obj->graph);
    Py_TYPE(obj)->tp_free(obj);
}

PyObject *py_graph_set_trigger(PyGraphImplObject *self, PyObject *args) {
    self->graph.handle_trigger = PyObject_IsTrue(args);
    Py_RETURN_NONE;
}
