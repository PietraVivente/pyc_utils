from setuptools import setup, Extension, find_packages

ext_modules = [
    Extension("pyc_utils._one", sources=["src/cutil/_one.c"]),
    Extension("pyc_utils._thereAre", sources=["src/cutil/_thereAre.c"])
]

setup(
    name="pyc_utils",
    version="0.1.0",
    description="Fast utilities for Python, with optional C extensions",
    packages=find_packages(where="src"),
    package_dir={"": "src"},
    ext_modules=ext_modules,
)
