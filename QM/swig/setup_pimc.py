#!/usr/bin/env python

"""
setup.py file for SWIG pimc
"""

from distutils.core import setup, Extension


pimc_module = Extension('_pimc',
                           sources=['swig/pimc_wrap.cxx', 'pimc.cpp'],
                           extra_compile_args=["-I./", "-std=c++11", "-O3"],
                           )

setup (name = 'pimc',
       version = '0.1',
       author      = "SWIG Docs",
       description = """Implementation of Path integral computation""",
       ext_modules = [pimc_module],
       py_modules = ["pimc"],
       )
