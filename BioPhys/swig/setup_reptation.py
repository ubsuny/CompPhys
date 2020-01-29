#!/usr/bin/env python

"""
setup.py file for SWIG reptation
"""

from distutils.core import setup, Extension


reptation_module = Extension('_reptation',
                           sources=['swig/reptation_wrap.cxx', 'reptation.cpp'],
                           extra_compile_args=["-I./", "-std=c++11", "-O3"],
                           )

setup (name = 'reptation',
       version = '0.1',
       author      = "SWIG Docs",
       description = """Implementation of Reptation""",
       ext_modules = [reptation_module],
       py_modules = ["reptation"],
       )
