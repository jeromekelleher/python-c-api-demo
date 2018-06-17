from setuptools import setup, Extension

demo_module = Extension(
    'demo',
    sources=["demomodule.c", "algorithm.c"]
)

consumer_module = Extension(
    'consumer',
    sources=["consumermodule.c"]
)

setup(
    name="demo",
    description="Demo C module",
    ext_modules=[demo_module, consumer_module])

