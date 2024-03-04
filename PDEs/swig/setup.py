#!/usr/bin/env python

"""
setup.py file for SWIG poisson_mg
"""

from distutils.core import setup, Extension


poisson_mg_module = Extension('_poisson_mg',
                           sources=['swig/poisson_mg_wrap.cxx'],
                           extra_compile_args=["-I./", "-std=c++11", "-O3", "-Wno-psabi"],
                           )

setup (name = 'poisson_mg',
       version = '0.1',
       author      = "SWIG Docs",
       description = """Simple swig poisson_mg from docs""",
       ext_modules = [poisson_mg_module],
       py_modules = ["poisson_mg"],
       )
