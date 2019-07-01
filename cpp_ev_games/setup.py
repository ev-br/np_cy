from distutils.core import setup
from Cython.Build import cythonize
from distutils.extension import Extension
import numpy as np

# Cython docs: https://media.readthedocs.org/pdf/cython/stable/cython.pdf

extensions = [
      Extension('game', ['game.pyx'], include_dirs = [np.get_include(), ], language="c++"),
      Extension('game', ['evolve.cc'], include_dirs = [np.get_include(), ], language="c++"),      
      ]


setup(name = "game",
      ext_modules = cythonize(
           extensions,                           # our Cython source
           #include_path = [np.get_include()],   # does not work!!! -> https://github.com/cython/cython/issues/1480
           #language="c++",                      # generate C++ code
      )
)