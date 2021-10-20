from setuptools import setup, Extension

# Compile *addmodule.cpp* into a shared library 
setup(
    # C++ modeule has to end in cpp
    ext_modules=[Extension('addmodule', ['addmodule.cpp'],),],
)