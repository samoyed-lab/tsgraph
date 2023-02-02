#ifndef TSGRAPH__CSRC_TS_NODE_H_
#define TSGRAPH__CSRC_TS_NODE_H_

#include <Python.h>
#include <numpy/arrayobject.h>

extern PyTypeObject TSVarType;

typedef struct {
    PyObject_HEAD

    PyArrayObject *data;
} PyTSVarObject;

#endif // TSGRAPH__CSRC_TS_NODE_H_
