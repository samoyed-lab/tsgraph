from numpy cimport ndarray
cimport numpy as cnp

from libcpp.vector cimport vector


cnp.import_array()


cdef class TSGraphBackend:

    def __init__(self, ndarray values):
        pass
