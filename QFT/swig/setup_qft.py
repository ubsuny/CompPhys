#!/usr/bin/env python

"""
setup.py file for SWIG qft
"""

from distutils.core import setup, Extension


qft_module = Extension('_qft',
                           sources=['swig/qft_wrap.cxx', 'LorentzVector.cpp', 'Particle.cpp', 'CrossSection.cpp', 'mstwpdf.cpp'],
                           extra_compile_args=["-I./", "-std=c++11", "-O3"],
                           )

setup (name = 'qft',
       version = '0.1',
       author      = "SWIG Docs",
       description = """Implementation of QFT calculations of cross sections""",
       ext_modules = [qft_module],
       py_modules = ["qft"],
       )
