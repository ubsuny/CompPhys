#!/usr/bin/env python

"""
setup.py file for SWIG ising
"""

from distutils.core import setup, Extension


ising_module = Extension('_ising',
                           sources=['swig/ising_wrap.cxx', 'ising.cpp'],
                           extra_compile_args=["-I./", "-std=c++11", "-O3"],
                           )

setup (name = 'ising',
       version = '0.1',
       author      = "SWIG Docs",
       description = """Implementation of the 2-d Ising model""",
       ext_modules = [ising_module],
       py_modules = ["ising"],
       )
