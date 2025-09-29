#!/usr/bin/env python

"""
setup.py file for SWIG example
"""

from distutils.core import setup, Extension


vector2_module = Extension('_vector2',
                           sources=['swig_code/Vector2_wrap.cxx', 'swig_code/Vector2.cpp'],
                           extra_compile_args=["-std=c++11", "-I."],
                           )

setup (name = 'vector2',
       version = '0.1',
       author      = "SWIG Docs",
       description = """Simple swig point from docs""",
       ext_modules = [vector2_module],
       py_modules = ["vector2"],
       )
