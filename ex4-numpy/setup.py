from setuptools import setup, Extension

import numpy as np

demo_module = Extension(
    'demo',
    sources=["demomodule.c", "algorithm.c"],
    include_dirs=[np.get_include()],
)

setup(
    name="demo",
    description="Demo C module",
    ext_modules=[demo_module])

