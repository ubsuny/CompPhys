#!/usr/bin/env python

"""
setup.py file for SWIG metropolis
"""

from distutils.core import setup, Extension


metropolis_module = Extension('_metropolis',
                           sources=['swig/metropolis_wrap.cxx'],
                           extra_compile_args=["-I./", "-std=c++11", "-O3"],
                           )

setup (name = 'metropolis',
       version = '0.1',
       author      = "SWIG Docs",
       description = """Implementation of 1-d Metropolis algorithm for random walkers""",
       ext_modules = [metropolis_module],
       py_modules = ["metropolis"],
       )
