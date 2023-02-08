from setuptools import setup, Extension

import numpy as np


setup(
    name="tsgraph",
    version="0.1.0",
    description="Event-driven computation graph for time series analysis and model optimization.",
    author="Samoyed Lab",
    packages=["tsgraph"],

    ext_modules=[
    	Extension(
            'tsgraph.backend',
            sources=[
                'tsgraph/csrc/module.c',
                'tsgraph/csrc/misc/ptr_array.c'
            ],
            include_dirs=[
                np.get_include(),
                'tsgraph/csrc'
            ]
        )
    ]
)
