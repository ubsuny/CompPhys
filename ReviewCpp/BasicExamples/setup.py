from setuptools import setup, Extension

# Compile *addmodule.c++* into a shared library 
setup(
    # C++ modeule has to end in cpp or specify the `language` parameter for other ends (eg c++)
    ext_modules=[Extension('addmodule', ['addmodule.c++'],
                          language="C++",),], 
)