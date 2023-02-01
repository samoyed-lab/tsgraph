from setuptools import setup, Extension


setup(
    name="tsgraph",
    version="0.1.0",
    description="Event-driven computation graph for time series analysis and model optimization.",
    author="Samoyed Lab",

    ext_modules=[
    	Extension(
            'tsgraph.csrc.module',
            sources=['tsgraph/csrc/module.c']
        )
    ]
)
