#!/usr/bin/env python

"""
setup.py file for SWIG example
"""

from distutils.core import setup, Extension


our_fft = Extension('_our_fft',
                           sources=['our_fft_wrap.cxx', 'our_fft.cpp'],
                           extra_compile_args=["-std=c++11"],
                           )

setup (name = 'our_fft',
       version = '0.1',
       author      = "Salvatore Rappoccio",
       description = """FFT implemented in C++ to be used in python""",
       ext_modules = [our_fft],
       py_modules = ["our_fft"],
       )
