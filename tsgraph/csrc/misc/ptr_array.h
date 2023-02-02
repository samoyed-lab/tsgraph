#ifndef TSGRAPH__CSRC_PTR_ARRAY_H_
#define TSGRAPH__CSRC_PTR_ARRAY_H_

#include <stdint.h>

/*
    A consumer that is either called on an element during its
    removal from the list, or called on every element during
    destruction of an array.
*/
typedef void (*PtrDestructor)(void *);

/*
    A short implementation for variable-length pointer arrays
    similar to the one in glib (as this is the only container
    used in this package we decided against packing additioal
    libraries).

    Used solely for storing the nodes in a TSGraph, and the
    dependents of a node in the computation graph (i.e. all nodes
    to forward-propagate changes to).

    Field names are taken from glib's GRealPtrArray.
*/
typedef struct {
    void *data;
    uint32_t len;
    uint32_t alloc;
    PtrDestructor element_free_func;
} PtrArray;

#endif // TSGRAPH__CSRC_PTR_ARRAY_H_
