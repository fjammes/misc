#!/usr/bin/env python

"""
setup.py file for SWIG example
"""

from distutils.core import setup, Extension
import os


current_dir = os.path.dirname(os.path.abspath(__file__))
lib_dir = os.path.join(current_dir,"lib")

example_module = Extension('_example',
                           sources=['example.i'],
                           #sources=['example_wrap.c'],
		           include_dirs=[lib_dir],
		           library_dirs=[lib_dir],
		           libraries=['example']
                           )

setup (name = 'example',
       version = '0.1',
       author      = "SWIG Docs",
       description = """Simple swig example linking and existing *.so file""",
       ext_modules = [example_module],
       py_modules = ["example"],
       )
