#!/usr/bin/env python

"""
setup.py file for SWIG sawalk
"""

from distutils.core import setup, Extension


sawalk_module = Extension('_sawalk',
                           sources=['swig/sawalk_wrap.cxx', 'sawalk.cpp'],
                           extra_compile_args=["-I./", "-std=c++11", "-O3"],
                           )

setup (name = 'sawalk',
       version = '0.1',
       author      = "SWIG Docs",
       description = """Implementation of Self-Avoiding Walk""",
       ext_modules = [sawalk_module],
       py_modules = ["sawalk"],
       )
