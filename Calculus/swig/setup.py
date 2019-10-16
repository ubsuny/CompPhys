#!/usr/bin/env python

"""
setup.py file for SWIG scattering
"""

from distutils.core import setup, Extension


scattering_module = Extension('_scattering',
                           sources=['swig/scattering_wrap.cxx'],
                           extra_compile_args=["-I./", "-std=c++11", "-O3"],
                           )

setup (name = 'scattering',
       version = '0.1',
       author      = "SWIG Docs",
       description = """Simple swig scattering from docs""",
       ext_modules = [scattering_module],
       py_modules = ["scattering"],
       )
