#include <ptr_array.h>

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define PTR_ARRAY_INIT_SIZE 10

static void ptr_array_maybe_expand(PtrArray *array, tsuint_t len) {
    tsuint_t max_len = TSUINT_MAX / sizeof(void *);

    // Overflows due to requesting more space than max_len.
    if (max_len - array->len <= len) {
        // TODO: overflow
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
    if (array == NULL) return NULL;

    array->pdata = NULL;
    array->len = 0;
    array->alloc = 0;
    array->element_free_func = element_free_func;

    ptr_array_maybe_expand(array, PTR_ARRAY_INIT_SIZE);
    if (array->pdata == NULL) {
        free(array);
        return NULL;
    }

    return array;
}

static void *ptr_array_remove_maybe_free(
    PtrArray *array, tsuint_t idx, bool free_element
) {
    if (array->len == 0 || array->len <= idx) {
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
