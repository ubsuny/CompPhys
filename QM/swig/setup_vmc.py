#!/usr/bin/env python

"""
setup.py file for SWIG vmc
"""

from distutils.core import setup, Extension


vmc_module = Extension('_vmc',
                           sources=['swig/vmc_wrap.cxx', 'vmc.cpp'],
                           extra_compile_args=["-I./", "-std=c++11", "-O3"],
                           )

setup (name = 'vmc',
       version = '0.1',
       author      = "SWIG Docs",
       description = """Implementation of variational MC solutions to Schroedinger Equation""",
       ext_modules = [vmc_module],
       py_modules = ["vmc"],
       )
