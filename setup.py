from setuptools import setup, find_packages
from setuptools.extension import Extension


setup(
    name = "tsgraph",
    version = "0.1.0",
    description = "Event-driven computation graph for time series analysis and model optimization.",
    author = "Samoyed Lab",
    packages = find_packages(),
    package_data = {
        'tsgraph.backend': ['tsgraph/csrc/py.typed']
    },

    ext_modules=[
    	Extension(
            'tsgraph.backend',
            libraries = ['glib-2.0'],
            sources = [
                'tsgraph/csrc/misc/ptr_array.c',

                'tsgraph/csrc/graph/comp_graph.c',
                'tsgraph/csrc/api/py_graph_impl.c',
                'tsgraph/csrc/api/pyobj_operators.c',

                'tsgraph/csrc/module.c'
            ],
            include_dirs = [
                'tsgraph/csrc',
                # TODO: automatic this library searching thing...
                '/usr/local/Cellar/glib/2.74.5/include/glib-2.0',
                '/usr/local/lib/glib-2.0/include'
            ]
        )
    ]
)
