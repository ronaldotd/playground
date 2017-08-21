from distutils.core import setup, Extension

grupy_module = Extension('grupy', sources=['grupymodule.c'])

setup(name='grupy', version='0.1', description='grupy module', ext_modules=[grupy_module])
