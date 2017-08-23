from distutils.core import setup, Extension

module = Extension('grupy', sources=['module2.c'])

setup(
    name='grupy',
    version='0.1',
    description='grupy module',
    ext_modules=[
        Extension('grupy1', sources=['module1.c']),
        Extension('grupy2', sources=['module2.c'])
    ])

