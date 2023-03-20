from libcpp.vector cimport vector


cdef class TSGraphBackend:
    cdef:
        vector[int] _nodes
