#!/usr/bin/env python

"""
setup.py file for SWIG dmc
"""

from distutils.core import setup, Extension


dmc_module = Extension('_dmc',
                           sources=['swig/dmc_wrap.cxx', 'dmc.cpp'],
                           extra_compile_args=["-I./", "-std=c++11", "-O3"],
                           )

setup (name = 'dmc',
       version = '0.1',
       author      = "SWIG Docs",
       description = """Implementation of Diffusive Quantum MC""",
       ext_modules = [dmc_module],
       py_modules = ["dmc"],
       )
