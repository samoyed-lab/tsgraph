from setuptools import setup, find_packages
from setuptools.extension import Extension
from Cython.Build import cythonize

import numpy as np


backend_ext = Extension(
    'tsgraph.backend',
    sources = [
        'tsgraph/_cylibs/module.pyx'
    ],
    include_dirs = [np.get_include()],
    language='c++',
    extra_compile_args=['-std=c++17']
)

setup(
    name = "tsgraph",
    version = "0.1.0",
    description = "Event-driven computation graph for time series analysis and model optimization.",
    author = "Samoyed Lab",
    packages = find_packages(),
    package_data = {
        'tsgraph.backend': ['tsgraph/_cylibs/py.typed']
    },

    ext_modules = cythonize((backend_ext,))
)
