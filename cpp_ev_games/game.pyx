# distutils: language=c++
import numpy as np

from libcpp.vector cimport vector
from numpy cimport import_array, PyArray_SimpleNewFromData, NPY_INT, npy_intp

cdef extern from "evolve.cc":
    void evolveT(vector[int]&, double, int) nogil
    void evolveQ(vector[int]&, double, int) nogil

cdef class GameField:
    cdef vector[int] _field
    cdef int _L
    cdef double _b

    def __init__(self, L, b):
        """Python-level ctor."""
        pass

    def __cinit__(self, int L, double b, *arg, **kw):
        self._L = L
        self._b = b
        self._field.resize(L*L)

        for i in range(L*L):
            self._field[i] = 0

    @property
    def field(self):
        """Return the field as a numpy array."""
        cdef npy_intp dims[2]
        dims[0] = self._L 
        dims[1] = self._L   
        return PyArray_SimpleNewFromData(2, dims, NPY_INT, &self._field[0])

    @property
    def L(self):
        """Return field size."""
        return self._L

    @field.setter
    def field(self, arr):
        """Set the game field."""
        arr = np.asarray(arr)
        if len(arr.shape) != 2:
            raise ValueError("Expected a 2D array, got %s-d." % len(arr.shape))
        if arr.size != self._L*self._L:
            raise ValueError("Size mismatch: expected %s, got %s." % (self._L*self._L, arr.size))

        arr = arr.ravel()
        for j in range(arr.size):
            self._field[j] = arr[j]

    def evolveT(self, int num_steps=1):
        """Evovle triangular grid game."""
        with nogil:
            evolveT(self._field, self._b, num_steps)

    def evolveQ(self, int num_steps=1):
        """Evovle classic grid game."""
        with nogil:
            evolveQ(self._field, self._b, num_steps)

#### init the numpy C API
import_array()
