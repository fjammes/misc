#!/usr/bin/env python

"""
setup.py file for SWIG example
"""

import commons
from distutils.command.build_ext import build_ext
from distutils.command.clean import clean
from distutils.core import setup, Extension
import os

commons.init_default_logger("install")

class build_scons(build_ext):
    def run(self):
	print "running scons"
	cmd = ["./lib/build.sh"]
	commons.run_command(cmd)
	#run_command("./lib/gcc-so.sh")
	#run_command("cd /home/fjammes/src/misc/distutils_swig_scons")
        # self.run_command("ls")
        build_ext.run(self)

class clean_scons(clean):
    def run(self):
	print "cleaning scons and swig"
	cmd = ["./lib/clean.sh"]
	commons.run_command(cmd)
	#run_command("./lib/gcc-so.sh")
	#run_command("cd /home/fjammes/src/misc/distutils_swig_scons")
        # self.run_command("ls")
        clean.run(self)

current_dir = os.path.dirname(os.path.abspath(__file__))
lib_dir = os.path.join(current_dir,"lib")

example_module = Extension('_example',
                           sources=['example.i'],
		           include_dirs=[lib_dir],
		           library_dirs=[lib_dir],
		           libraries=['example']
                           )
setup (name = 'example',
       version = '0.1',
       author      = "SWIG Docs",
       cmdclass={'build_ext': build_scons,'clean': clean_scons},
       description = """Simple swig example linking and existing *.so file""",
       ext_modules = [example_module],
       py_modules = ["example"]
       )

