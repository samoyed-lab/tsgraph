#ifndef TSGRAPH__CSRC_MACROS_H_
#define TSGRAPH__CSRC_MACROS_H_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#define SetErr_NoMem PyErr_SetString(PyExc_MemoryError, "malloc failed")

#endif // TSGRAPH__CSRC_MACROS_H_
