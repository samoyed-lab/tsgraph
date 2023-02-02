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

    Fields and functions names are taken from glib's GRealPtrArray
    for recognizability.
*/
typedef struct {
    void *pdata;
    uint32_t len;
    uint32_t alloc;
    PtrDestructor element_free_func;
} PtrArray;

#define ptr_array_index(array, idx) ((array)->pdata)[idx];

PtrArray *ptr_array_new(PtrDestructor element_free_func);

void *ptr_array_remove_index(PtrArray *array, uint32_t idx);
void *ptr_array_steal_index(PtrArray *array, uint32_t idx);

void ptr_array_add(PtrArray *array, void *ptr);
void ptr_array_insert(PtrArray *array, uint32_t idx, void *ptr);

#endif // TSGRAPH__CSRC_PTR_ARRAY_H_
