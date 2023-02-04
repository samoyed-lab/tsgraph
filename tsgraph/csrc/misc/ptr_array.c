#include "ptr_array.h"

#include <Python.h>
#include <stdlib.h>
#include <string.h>

#include "misc/macros.h"

#define PTR_ARRAY_INIT_SIZE 64
#define PTR_ARRAY_EXPAND_SIZE 64

static void ptr_array_maybe_expand(PtrArray *array, tsuint_t len) {
    tsuint_t max_len = TSUINT_MAX / sizeof(void *);

    // Overflows due to requesting more space than max_len.
    if (max_len - array->len <= len) {
        PyErr_Format(
            PyExc_MemoryError,
            "Extending PtrArray over its maximum length of %d.",
            max_len
        );
        return;
    }

    // Expand if requesting more length that current.
    if (array->len + len > array->alloc) {
        tsuint_t target_alloc = sizeof(void *) * (array->len + len);
        array->alloc = array->len + len;
        array->pdata = realloc(array->pdata, target_alloc);
    }
}

PtrArray *ptr_array_new(PtrDestructor element_free_func) {
    return ptr_array_new_with_free_func(NULL);
}

PtrArray *ptr_array_new_with_free_func(PtrDestructor element_free_func) {
    PtrArray *array = malloc(sizeof(PtrArray));
    if (array == NULL) {
        SetErr_NoMem;
        return NULL;
    }

    array->pdata = NULL;
    array->len = 0;
    array->alloc = 0;
    array->element_free_func = element_free_func;

    ptr_array_maybe_expand(array, PTR_ARRAY_INIT_SIZE);
    if (array->pdata == NULL) {
        free(array);
        SetErr_NoMem;
        return NULL;
    }

    return array;
}

static void *ptr_array_remove_maybe_free(
    PtrArray *array, tsuint_t idx, bool free_element
) {
    if (array->len == 0 || array->len <= idx) {
        PyErr_SetFormat(
            PyExc_IndexError,
            "Accesing index %d of PtrArray of length %d",
            idx, array->len
        );
        return NULL;
    }

    void *result = ptr_array_index(array, idx);
    if (free_element && array->element_free_func != NULL) {
        array->element_free_func(result);
    }

    // Shift all elements to the left.
    if (idx != array->len - 1) {
        memmove(
            array->pdata + idx,
            array->pdata + idx + 1,
            sizeof(void *) * (array->len - idx - 1)
        );
    }

    array->len--;
    return result;
}

void *ptr_array_remove_index(PtrArray *array, tsuint_t idx) {
    return ptr_array_remove_maybe_free(array, idx, true);
}

void *ptr_array_steal_index(PtrArray *array, tsuint_t idx) {
    return ptr_array_remove_maybe_free(array, idx, false);
}

void ptr_array_add(PtrArray *array, void *ptr) {
    if (array->len >= array->alloc) {
        ptr_array_maybe_expand(array, PTR_ARRAY_EXPAND_SIZE);
    }

    ptr_array_index(array, array->len++) = ptr;
}

void ptr_array_insert(PtrArray *array, tsuint_t idx, void *ptr) {
    if (idx > array->len) {
        PyErr_SetFormat(
            PyExc_IndexError,
            "Inserting at index %d of PtrArray of length %d",
            idx, array->len
        );
        return;
    }

    if (array->len >= array->alloc) {
        ptr_array_maybe_expand(array, PTR_ARRAY_EXPAND_SIZE);
    }

    if (idx < array->len) {
        memmove(
            &(array->pdata[idx + 1]),
            &(array->pdata[idx]),
            (array->len - idx) * sizeof (void *)
        );
    }

    array->len++;
    ptr_array_index(array, idx) = ptr;
}

void ptr_array_free(PtrArray *array, bool free_elements) {
    if (free_elements && array->element_free_func != NULL) {
        for (tsuint_t i = 0; i < array->len; i++) {
            array->element_free_func(ptr_array_index(array, i));
        }
    }

    free(array);
}
